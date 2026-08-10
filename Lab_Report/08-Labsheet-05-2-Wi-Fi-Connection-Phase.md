# ใบงานที่ 5.2: การยืนยันตัวตน การสถาปนาการเชื่อมต่อ และการรับหมายเลข IP Address (Wi-Fi Connection & IP Assignment)

## 0. กล่าวนำ (Introduction)
ใบงานนี้เป็นการทดลองต่อเนื่องจากใบงานที่ 5.1 (Scan Phase) เพื่อศึกษาและสังเกตกระบวนการสถาปนาการเชื่อมต่อแบบครบวงจรในเฟสที่ 2 (Authentication), เฟสที่ 3 (Association), เฟสที่ 4 (4-Way Handshake) และเฟสที่ 5 (IP Assignment / DHCP) ผ่านเฟรมเวิร์ก ESP-IDF 

นักศึกษาจะได้วิเคราะห์พฤติกรรมของระบบและอ่านค่า Log สไตล์ Forensic เมื่อเกิดเหตุการณ์เชื่อมต่อสำเร็จ (`WIFI_EVENT_STA_CONNECTED`, `IP_EVENT_STA_GOT_IP`) รวมถึงการตรวจสอบและถอดรหัส Disconnect Reason Code (`WIFI_EVENT_STA_DISCONNECTED`) เมื่อเกิดเหตุการณ์เชื่อมต่อล้มเหลว (เช่น SSID ผิด หรือ Password ผิด)

---

## 1. วัตถุประสงค์ (Objectives)
1. เรียนรู้กระบวนการเชื่อมต่อ Wi-Fi และการจัดสรรหมายเลข IP Address (DHCP Client) ในโหมด Station (`WIFI_STA`) บน ESP-IDF
2. เรียนรู้การใช้ Event Loop (`esp_event_handler_instance_register`) และ FreeRTOS Event Group ในการดักจับ Event ของระบบ Wi-Fi และ IP
3. อ่านและวิเคราะห์โครงสร้างข้อมูล Event ได้แก่ `wifi_event_sta_connected_t`, `wifi_event_sta_disconnected_t` และ `ip_event_got_ip_t`
4. ตรวจสอบและระบุสาเหตุของความล้มเหลวในการเชื่อมต่อ Wi-Fi จากค่า Disconnect Reason Code (เช่น `WIFI_REASON_NO_AP_FOUND` และ `WIFI_REASON_HANDSHAKE_TIMEOUT` / `AUTH_FAIL`)

---

## 2. อุปกรณ์และซอฟต์แวร์ที่ใช้ในการทดลอง (Equipment & Tools)
1. บอร์ดไมโครคอนโทรลเลอร์ ESP32 (เช่น ESP32 DevKit V1) จำนวน 1 บอร์ด
2. สายเชื่อมต่อ Micro-USB หรือ USB-C จำนวน 1 เส้น
3. คอมพิวเตอร์ที่ติดตั้งโปรแกรม IDE เช่น VS Code พร้อมทั้ง ESP-IDF (อาจจะติดตั้งบนเครื่องหรือบน Docker ก็ได้)

---

## 3. ความรู้พื้นฐานที่เกี่ยวข้อง (Theoretical Background - ESP-IDF Framework)

### 3.1 สถาปัตยกรรม Event Loop และ Event Handling ใน ESP-IDF
ใน ESP-IDF การทำงานของ Wi-Fi เป็นแบบ Asynchronous (ทำงานเบื้องหลัง) โดย Driver จะส่ง Event ผ่านระบบ **Default Event Loop** เพื่อแจ้งเตือนให้โปรแกรมทราบความคืบหน้า

```mermaid
sequenceDiagram
    autonumber
    participant App as Application Code
    participant Evt as ESP Event Loop
    participant Drv as Wi-Fi Driver / IP Stack

    App->>Evt: esp_event_handler_instance_register()
    App->>Drv: esp_wifi_connect()
    Drv->>Evt: Post WIFI_EVENT_STA_CONNECTED
    Evt->>App: Callback: wifi_event_handler()
    Drv->>Evt: Post IP_EVENT_STA_GOT_IP
    Evt->>App: Callback: wifi_event_handler()
```

### 3.2 โครงสร้างข้อมูล Event สำคัญ (Class Diagrams)

#### 1) โครงสร้างข้อมูล `wifi_event_sta_connected_t`
ส่งมาพร้อมกับ Event `WIFI_EVENT_STA_CONNECTED` เพื่อระบุรายละเอียดของ AP ที่เชื่อมต่อสำเร็จ:

```mermaid
classDiagram
    class wifi_event_sta_connected_t {
        +uint8_t[33] ssid
        +uint8_t ssid_len
        +uint8_t[6] bssid
        +uint8_t channel
        +wifi_auth_mode_t authmode
        +uint16_t aid
    }
```

#### 2) โครงสร้างข้อมูล `wifi_event_sta_disconnected_t`
ส่งมาพร้อมกับ Event `WIFI_EVENT_STA_DISCONNECTED` เพื่อระบุสาเหตุของการหลุดการเชื่อมต่อ:

```mermaid
classDiagram
    class wifi_event_sta_disconnected_t {
        +uint8_t[33] ssid
        +uint8_t ssid_len
        +uint8_t[6] bssid
        +uint8_t reason
        +int8_t rssi
    }
```

#### 3) โครงสร้างข้อมูล `ip_event_got_ip_t`
ส่งมาพร้อมกับ Event `IP_EVENT_STA_GOT_IP` เมื่อ ESP32 ได้รับหมายเลข IP จาก DHCP Server:

```mermaid
classDiagram
    class ip_event_got_ip_t {
        +esp_ip4_addr_t ip
        +esp_ip4_addr_t netmask
        +esp_ip4_addr_t gw
        +bool ip_changed
    }
```

---

## 4. ขั้นตอนและโปรแกรมทดสอบการทดลอง (Experimental Procedures)

ในใบงานนี้ จะทำการทดสอบการเชื่อมต่อ Wi-Fi ใน 3 สถานการณ์ย่อย เพื่อเปรียบเทียบ Forensic Log และ Disconnect Reason Code:

### 5.2.1 การเชื่อมต่อด้วย SSID และ Password ที่ถูกต้อง (Success Case)
กำหนดค่า SSID และ Password ที่ถูกต้องตามสภาพแวดล้อมจริง สังเกต Event `WIFI_EVENT_STA_CONNECTED` และ `IP_EVENT_STA_GOT_IP` พร้อมอ่านหมายเลข IP Address, Subnet Mask และ Gateway

### 5.2.2 การเชื่อมต่อด้วย SSID ที่ไม่มีอยู่จริง (Wrong SSID / No AP Found)
กำหนดค่า SSID สมมุติที่ไม่มีอยู่จริง (`"NON_EXISTENT_SSID_9999"`) สังเกต Event `WIFI_EVENT_STA_DISCONNECTED` และวิเคราะห์ค่า Reason Code ซึ่งต้องได้ `WIFI_REASON_NO_AP_FOUND` (Decimal 201 / Hex `0xC9`)

### 5.2.3 การเชื่อมต่อด้วย SSID ที่ถูกต้องแต่ Password ผิด (Wrong Password / Handshake Fail)
กำหนดค่า SSID ถูกต้องแต่ป้อน Password ผิด (`"WRONG_PASS_9999"`) สังเกต Event `WIFI_EVENT_STA_DISCONNECTED` ในขั้นตอน 4-Way Handshake และวิเคราะห์ค่า Reason Code ซึ่งต้องได้ `WIFI_REASON_HANDSHAKE_TIMEOUT` (15) หรือ `WIFI_REASON_AUTH_FAIL` (202 / 204)

---

## 5. ซอร์สโค้ดการทดลอง (Complete ESP-IDF Source Code - `main.c`)

ให้นักศึกษานำซอร์สโค้ด C ต่อไปนี้ไปวางในไฟล์ `main/main.c` ของโปรเจกต์ ESP-IDF ทำการ Build และ Flash ลงบอร์ด ESP32 จากนั้นเปิด ESP-IDF Monitor (Baud Rate `115200`) เพื่อสังเกตผลการทำงาน

==**หมายเหตุ** ใน source code ด้านล่าง  แนะนำให้ใช้ MY_SSID และ  MY_PASSWORD จาก mobile hotspot และต้องลบออกก่อน push ขึ้น git== 

```c
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"

static const char *TAG = "LAB_WIFI_CONN";

/* FreeRTOS event group to signal when we are connected or failed */
static EventGroupHandle_t s_wifi_event_group;

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

// Configurable target Wi-Fi credentials for successful test
#define EXAMPLE_ESP_WIFI_SSID      "MY_SSID"
#define EXAMPLE_ESP_WIFI_PASS      "MY_PASSWORD"

// Convert wifi_reason_code_t to readable string
static const char *get_disconnect_reason_name(uint8_t reason) {
  switch (reason) {
  case WIFI_REASON_UNSPECIFIED:
    return "WIFI_REASON_UNSPECIFIED (1)";
  case WIFI_REASON_AUTH_EXPIRE:
    return "WIFI_REASON_AUTH_EXPIRE (2)";
  case WIFI_REASON_AUTH_LEAVE:
    return "WIFI_REASON_AUTH_LEAVE (3)";
  case WIFI_REASON_ASSOC_EXPIRE:
    return "WIFI_REASON_ASSOC_EXPIRE (4)";
  case WIFI_REASON_ASSOC_FAIL:
    return "WIFI_REASON_ASSOC_FAIL (203)";
  case WIFI_REASON_NOT_AUTHED:
    return "WIFI_REASON_NOT_AUTHED (6)";
  case WIFI_REASON_HANDSHAKE_TIMEOUT:
    return "WIFI_REASON_HANDSHAKE_TIMEOUT (15)";
  case WIFI_REASON_NO_AP_FOUND:
    return "WIFI_REASON_NO_AP_FOUND (201)";
  case WIFI_REASON_AUTH_FAIL:
    return "WIFI_REASON_AUTH_FAIL (202)";
  case WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT:
    return "WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT (204)";
  case WIFI_REASON_CONNECTION_FAIL:
    return "WIFI_REASON_CONNECTION_FAIL (208)";
  case WIFI_REASON_BEACON_TIMEOUT:
    return "WIFI_REASON_BEACON_TIMEOUT (200)";
  default:
    return "OTHER_DISCONNECT_REASON";
  }
}

// Wi-Fi and IP Event Handler with Forensic Logging
static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data) {
  if (event_base == WIFI_EVENT) {
    switch (event_id) {
    case WIFI_EVENT_STA_START:
      ESP_LOGI(TAG, "[EVENT FORENSIC]: WIFI_EVENT_STA_START received");
      ESP_LOGI(TAG, "[FORENSIC]: Call esp_wifi_connect()");
      esp_err_t err_conn = esp_wifi_connect();
      ESP_LOGI(TAG, "[FORENSIC]: esp_wifi_connect() returned %s (0x%x)",
               esp_err_to_name(err_conn), err_conn);
      break;

    case WIFI_EVENT_STA_CONNECTED: {
      wifi_event_sta_connected_t *event =
          (wifi_event_sta_connected_t *)event_data;
      ESP_LOGI(TAG, "=======================================================");
      ESP_LOGI(TAG, "[EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!");
      ESP_LOGI(TAG, "  -> Connected to SSID : %s", event->ssid);
      ESP_LOGI(TAG, "  -> BSSID            : %02X:%02X:%02X:%02X:%02X:%02X",
               event->bssid[0], event->bssid[1], event->bssid[2],
               event->bssid[3], event->bssid[4], event->bssid[5]);
      ESP_LOGI(TAG, "  -> Channel          : %d", event->channel);
      ESP_LOGI(TAG, "  -> Auth Mode        : %d", event->authmode);
      ESP_LOGI(TAG, "=======================================================");
      break;
    }

    case WIFI_EVENT_STA_DISCONNECTED: {
      wifi_event_sta_disconnected_t *event =
          (wifi_event_sta_disconnected_t *)event_data;
      ESP_LOGW(TAG, "=======================================================");
      ESP_LOGW(TAG, "[EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!");
      ESP_LOGW(TAG, "  -> Target SSID          : %s", event->ssid);
      ESP_LOGW(TAG, "  -> Reason Code (Decimal): %d", event->reason);
      ESP_LOGW(TAG, "  -> Reason Code (Hex)    : 0x%02X", event->reason);
      ESP_LOGW(TAG, "  -> Reason Description   : %s",
               get_disconnect_reason_name(event->reason));
      ESP_LOGW(TAG, "=======================================================");
      xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
      break;
    }

    default:
      ESP_LOGI(TAG, "[EVENT FORENSIC]: WIFI_EVENT ID %ld received", event_id);
      break;
    }
  } else if (event_base == IP_EVENT) {
    if (event_id == IP_EVENT_STA_GOT_IP) {
      ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
      ESP_LOGI(TAG, "=======================================================");
      ESP_LOGI(TAG, "[EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!");
      ESP_LOGI(TAG, "  -> IP Address : " IPSTR, IP2STR(&event->ip_info.ip));
      ESP_LOGI(TAG, "  -> Netmask    : " IPSTR, IP2STR(&event->ip_info.netmask));
      ESP_LOGI(TAG, "  -> Gateway    : " IPSTR, IP2STR(&event->ip_info.gw));
      ESP_LOGI(TAG, "=======================================================");
      xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
  }
}

// Function to test Wi-Fi connection with specific config
static void test_wifi_connection(const char *test_title, const char *ssid,
                                  const char *password) {
  ESP_LOGI(TAG, "\n");
  ESP_LOGI(TAG, "------------------------------------------------------------------");
  ESP_LOGI(TAG, ">>> %s", test_title);
  ESP_LOGI(TAG, "------------------------------------------------------------------");
  ESP_LOGI(TAG, "  Target SSID: \"%s\"", ssid);
  ESP_LOGI(TAG, "  Target Password: \"%s\"", password);

  // Clear event bits
  xEventGroupClearBits(s_wifi_event_group, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT);

  wifi_config_t wifi_config = {
      .sta = {
          .threshold.authmode = WIFI_AUTH_WPA2_PSK,
      },
  };
  strncpy((char *)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid));
  strncpy((char *)wifi_config.sta.password, password,
          sizeof(wifi_config.sta.password));

  ESP_LOGI(TAG, "[FORENSIC]: Call esp_wifi_stop()");
  esp_wifi_stop();

  ESP_LOGI(TAG, "[FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)");
  esp_err_t err_cfg = esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
  ESP_LOGI(TAG, "[FORENSIC]: esp_wifi_set_config() returned %s (0x%x)",
           esp_err_to_name(err_cfg), err_cfg);

  ESP_LOGI(TAG, "[FORENSIC]: Call esp_wifi_start()");
  esp_err_t err_start = esp_wifi_start();
  ESP_LOGI(TAG, "[FORENSIC]: esp_wifi_start() returned %s (0x%x)",
           esp_err_to_name(err_start), err_start);

  /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or failed (WIFI_FAIL_BIT) */
  EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                         WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                         pdFALSE, pdFALSE, pdMS_TO_TICKS(10000));

  if (bits & WIFI_CONNECTED_BIT) {
    ESP_LOGI(TAG, "[RESULT]: TEST PASSED - Connected to AP successfully!");
  } else if (bits & WIFI_FAIL_BIT) {
    ESP_LOGW(TAG, "[RESULT]: TEST FAILED - Disconnected event captured.");
  } else {
    ESP_LOGE(TAG, "[RESULT]: TEST TIMEOUT - Neither connected nor disconnected event received.");
  }
}

void app_main(void) {
  s_wifi_event_group = xEventGroupCreate();

  // 1. Initialize NVS Flash
  ESP_LOGI(TAG, "[FORENSIC]: Call nvs_flash_init()");
  esp_err_t ret = nvs_flash_init();
  ESP_LOGI(TAG, "[FORENSIC]: nvs_flash_init() returned %s (0x%x)",
           esp_err_to_name(ret), ret);
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
      ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_LOGI(TAG, "[FORENSIC]: Call nvs_flash_erase()");
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
    ESP_LOGI(TAG, "[FORENSIC]: nvs_flash_init() retry returned %s (0x%x)",
             esp_err_to_name(ret), ret);
  }
  ESP_ERROR_CHECK(ret);

  // 2. Initialize Network Interface and Event Loop
  ESP_LOGI(TAG, "[FORENSIC]: Call esp_netif_init()");
  ESP_ERROR_CHECK(esp_netif_init());

  ESP_LOGI(TAG, "[FORENSIC]: Call esp_event_loop_create_default()");
  ESP_ERROR_CHECK(esp_event_loop_create_default());

  ESP_LOGI(TAG, "[FORENSIC]: Call esp_netif_create_default_wifi_sta()");
  esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
  ESP_LOGI(TAG, "[FORENSIC]: esp_netif_create_default_wifi_sta() returned %p", sta_netif);

  // 3. Initialize Wi-Fi Driver
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_LOGI(TAG, "[FORENSIC]: Call esp_wifi_init(&cfg)");
  ESP_ERROR_CHECK(esp_wifi_init(&cfg));

  // 4. Register Event Handlers
  esp_event_handler_instance_t instance_any_id;
  esp_event_handler_instance_t instance_got_ip;
  ESP_LOGI(TAG, "[FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)");
  ESP_ERROR_CHECK(esp_event_handler_instance_register(
      WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL,
      &instance_any_id));

  ESP_LOGI(TAG, "[FORENSIC]: Call esp_event_handler_instance_register(IP_EVENT)");
  ESP_ERROR_CHECK(esp_event_handler_instance_register(
      IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL,
      &instance_got_ip));

  ESP_LOGI(TAG, "[FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)");
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

  ESP_LOGI(TAG, "==================================================================");
  ESP_LOGI(TAG, "  Lab 5.2: Wi-Fi Connection & IP Assignment (ESP-IDF Forensic)");
  ESP_LOGI(TAG, "==================================================================");

  // ------------------------------------------------------------------
  // 5.2.1 Connecting with Correct SSID & Password (Success Case)
  // ------------------------------------------------------------------
  test_wifi_connection("Experiment 5.2.1: Connection Test - Correct Credentials",
                       EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);

  vTaskDelay(pdMS_TO_TICKS(2000));

  // ------------------------------------------------------------------
  // 5.2.2 Connecting with Wrong SSID (Non-existent AP Case)
  // ------------------------------------------------------------------
  test_wifi_connection("Experiment 5.2.2: Connection Test - Wrong SSID (No AP Found)",
                       "NON_EXISTENT_SSID_9999", "12345678");

  vTaskDelay(pdMS_TO_TICKS(2000));

  // ------------------------------------------------------------------
  // 5.2.3 Connecting with Correct SSID but Wrong Password (Handshake Fail Case)
  // ------------------------------------------------------------------
  test_wifi_connection("Experiment 5.2.3: Connection Test - Wrong Password (Auth/Handshake Fail)",
                       EXAMPLE_ESP_WIFI_SSID, "WRONG_PASS_9999");

  ESP_LOGI(TAG, "==================================================================");
  ESP_LOGI(TAG, "  [Phase 2/3/4/5 Completed: Wi-Fi Connection Lab Finished]");
  ESP_LOGI(TAG, "==================================================================");
}
```

---

## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองทั้ง 3 สถานการณ์

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event สุดท้ายที่ได้รับ | ผลลัพธ์ (Passed/Failed) | Reason Code (Decimal / Hex) | คำอธิบาย Reason Code |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.2.1** | SSID และ Password ถูกต้อง | | | | |
| **5.2.2** | ระบุ SSID ผิด (ไม่มีในระบบ) | | | | |
| **5.2.3** | ระบุ SSID ถูกต้อง แต่ Password ผิด | | | | |

### 6.2 บันทึกข้อมูลเครือข่ายจากการเชื่อมต่อสำเร็จ (ข้อ 5.2.1)

| พารามิเตอร์เครือข่าย | ค่าที่ได้รับจริงจาก DHCP |
| :--- | :--- |
| **SSID** |Cs.WiFi|
| **BSSID (MAC Address)** |4E:9D:3A:DC:4C:B6|
| **Channel** |11|
| **IP Address** |10.79.236.35|
| **Subnet Mask** |255.255.255.0|
| **Default Gateway** |10.79.236.197|

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการระบุ SSID ผิด (ข้อ 5.2.2) จึงส่งผลให้เกิด Disconnect Event ด้วย Reason Code `201` (`WIFI_REASON_NO_AP_FOUND`) ตั้งแต่เฟส Scan?
--เพราะ disconnect event ที่เห็นเกิดจาก esp_wifi_stop() ตัดการเชื่อมต่อ SSID เดิม (Cs.WiFi จาก 5.2.1) ไม่ใช่จากการหา SSID ใหม่ไม่เจอ — เทสจบเร็วเกินไป (~160ms) แสดงว่ายังไม่ทันสแกนหา NON_EXISTENT_SSID_9999 เลยด้วยซ้ำ เป็นบั๊กของลำดับโค้ด ไม่ใช่พฤติกรรม NO_AP_FOUND จริง

2. เหตุใดการพิมพ์ Password ผิด (ข้อ 5.2.3) จึงผ่านเฟส Auth และ Assoc มาได้ แต่มาล้มเหลวในเฟส 4-Way Handshake (Reason Code `15` หรือ `204`)?
--ราะ AP ใช้ WPA3-SAE (ไม่ใช่ WPA2-PSK) ซึ่งตรวจรหัสผ่านตั้งแต่ขั้น Authentication เลย รหัสผิดจึงล้มที่ auth ทันที (state: auth→init) ไม่ทันได้ไปถึง assoc/4-way handshake

3. ลำดับการเกิด Event ระหว่าง **`WIFI_EVENT_STA_CONNECTED`** กับ **`IP_EVENT_STA_GOT_IP`** Event ใดเกิดขึ้นก่อนกัน และมีความหมายทางกายภาพของ Layer Network ต่างกันอย่างไร?
--WIFI_EVENT_STA_CONNECTED (Layer 2 — เชื่อมกับ AP สำเร็จ) เกิดก่อน แล้วตามด้วย IP_EVENT_STA_GOT_IP (Layer 3 — ได้ IP จาก DHCP) ห่างกัน ~1.3 วินาทีคือเวลา DHCP

4. สมาชิกตัวแปร `reason` ในโครงสร้าง `wifi_event_sta_disconnected_t` มีประโยชน์อย่างไรต่อการออกแบบระบบค้นหาสาเหตุและกู้คืนการเชื่อมต่อ (Auto-Reconnection Mechanism) ในแอปพลิเคชัน IoT?
--ใช้แยกกลยุทธ์ retry: สัญญาณอ่อน/timeout → retry ได้เลย, รหัสผ่านผิด → ไม่ควร retry ซ้ำทันที (เสี่ยงโดนบล็อก) ควรแจ้งผู้ใช้แทน, หาไม่เจอ → รอนานขึ้นก่อน retry — ช่วยประหยัดพลังงานและลดความเสี่ยงถูก AP ล็อก

--log--
I (27) boot: ESP-IDF v6.0.2 2nd stage bootloader
I (27) boot: compile time Aug  4 2026 10:56:22
I (27) boot: Multicore bootloader
I (29) boot: chip revision: v3.1
I (32) boot.esp32: SPI Speed      : 40MHz
I (35) boot.esp32: SPI Mode       : DIO
I (39) boot.esp32: SPI Flash Size : 2MB
I (42) boot: Enabling RNG early entropy source...
I (47) boot: Partition Table:
I (49) boot: ## Label            Usage          Type ST Offset   Length
I (56) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (62) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (69) boot:  2 factory          factory app      00 00 00010000 00100000
I (75) boot: End of partition table
I (79) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1a638h (108088) map
I (125) esp_image: segment 1: paddr=0002a660 vaddr=3ffb0000 size=04528h ( 17704) load
I (132) esp_image: segment 2: paddr=0002eb90 vaddr=40080000 size=01488h (  5256) load
I (134) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=8633ch (549692) map
I (332) esp_image: segment 4: paddr=000b6364 vaddr=40081488 size=14180h ( 82304) load
I (366) esp_image: segment 5: paddr=000ca4ec vaddr=50000000 size=00028h (    40) load
I (377) boot: Loaded app from partition at offset 0x10000
I (377) boot: Disabling RNG early entropy source...
I (388) cpu_start: Multicore app
I (396) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (396) cpu_start: Pro cpu start user code
I (396) cpu_start: cpu freq: 160000000 Hz
I (398) app_init: Application information:
I (402) app_init: Project name:     wifi_connection_phase
I (407) app_init: App version:      37de524-dirty
I (411) app_init: Compile time:     Aug  4 2026 10:55:53
I (416) app_init: ELF file SHA256:  07a847e27...
I (421) app_init: ESP-IDF:          v6.0.2
I (424) efuse_init: Min chip rev:     v0.0
I (428) efuse_init: Max chip rev:     v3.99 
I (432) efuse_init: Chip rev:         v3.1
I (436) heap_init: Initializing. RAM available for dynamic allocation:
I (443) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (448) heap_init: At 3FFB8A40 len 000275C0 (157 KiB): DRAM
I (453) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (458) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (464) heap_init: At 40095608 len 0000A9F8 (42 KiB): IRAM
I (470) spi_flash: detected chip: generic
I (473) spi_flash: flash io: dio
W (476) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (490) main_task: Started on CPU0
I (490) main_task: Calling app_main()
I (490) LAB_WIFI_CONN: [FORENSIC]: Call nvs_flash_init()
I (520) LAB_WIFI_CONN: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (520) LAB_WIFI_CONN: [FORENSIC]: Call esp_netif_init()
I (520) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_loop_create_default()
I (530) LAB_WIFI_CONN: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (530) LAB_WIFI_CONN: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbdd38
I (540) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_init(&cfg)
I (560) wifi:wifi driver task: 3ffc0424, prio:23, stack:6656, core=0
I (570) wifi:wifi firmware version: 00ad238
I (570) wifi:wifi certification version: v7.0
I (570) wifi:config NVS flash: enabled
I (570) wifi:config nano formatting: disabled
I (580) wifi:Init data frame dynamic rx buffer num: 32
I (580) wifi:Init static rx mgmt buffer num: 5
I (580) wifi:Init management short buffer num: 32
I (590) wifi:Init dynamic tx buffer num: 32
I (590) wifi:Init static rx buffer size: 1600
I (600) wifi:Init static rx buffer num: 10
I (600) wifi:Init dynamic rx buffer num: 32
I (610) wifi_init: rx ba win: 6
I (610) wifi_init: accept mbox: 6
I (610) wifi_init: tcpip mbox: 32
I (610) wifi_init: udp mbox: 6
I (620) wifi_init: tcp mbox: 6
I (620) wifi_init: tcp tx win: 5760
I (620) wifi_init: tcp rx win: 5760
I (630) wifi_init: tcp mss: 1440
I (630) wifi_init: WiFi IRAM OP enabled
I (630) wifi_init: WiFi RX IRAM OP enabled
I (640) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (640) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_handler_instance_register(IP_EVENT)
I (650) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (660) LAB_WIFI_CONN: ==================================================================
I (670) LAB_WIFI_CONN:   Lab 5.2: Wi-Fi Connection & IP Assignment (ESP-IDF Forensic)
I (670) LAB_WIFI_CONN: ==================================================================
I (680) LAB_WIFI_CONN: 

I (680) LAB_WIFI_CONN: ------------------------------------------------------------------
I (690) LAB_WIFI_CONN: >>> Experiment 5.2.1: Connection Test - Correct Credentials
I (700) LAB_WIFI_CONN: ------------------------------------------------------------------
I (710) LAB_WIFI_CONN:   Target SSID: "Cs.WiFi"
I (710) LAB_WIFI_CONN:   Target Password: "13112548"
I (720) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (720) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (750) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (750) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (760) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06
I (840) wifi:mode : sta (14:33:5c:0f:55:1c)
I (840) wifi:enable tsf
I (840) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (850) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (850) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (860) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (860) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (2090) wifi:new:<11,0>, old:<1,0>, ap:<255,255>, sta:<11,0>, prof:1, snd_ch_cfg:0x0
I (2090) wifi:state: init -> auth (0xb0)
I (2470) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (2760) wifi:state: auth -> assoc (0x0)
I (2790) wifi:state: assoc -> run (0x10)
I (2830) wifi:connected with Cs.WiFi, aid = 1, channel 11, BW20, bssid = 4e:9d:3a:dc:4c:b6
I (2830) wifi:security: WPA3-SAE H2E, phy: bgn, rssi: -39, cipher(pairwise:0x3, group:0x3), pmf:1
I (2850) wifi:pm start, type: 1

I (2850) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (2850) LAB_WIFI_CONN: =======================================================
I (2860) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (2860) LAB_WIFI_CONN:   -> Connected to SSID : Cs.WiFi
I (2870) LAB_WIFI_CONN:   -> BSSID            : 4E:9D:3A:DC:4C:B6
I (2870) LAB_WIFI_CONN:   -> Channel          : 11
I (2880) LAB_WIFI_CONN:   -> Auth Mode        : 6
I (2880) LAB_WIFI_CONN: =======================================================
I (2860) wifi:dp: 2, bi: 102400, li: 4, scale listen interval from 307200 us to 409600 us
I (2900) wifi:AP's beacon interval = 102400 us, DTIM period = 2
I (2910) wifi:<ba-add>idx:0 (ifx:0, 4e:9d:3a:dc:4c:b6), tid:0, ssn:0, winSize:64
I (4180) esp_netif_handlers: sta ip: 10.79.236.35, mask: 255.255.255.0, gw: 10.79.236.197
I (4180) LAB_WIFI_CONN: =======================================================
I (4180) LAB_WIFI_CONN: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!
I (4190) LAB_WIFI_CONN:   -> IP Address : 10.79.236.35
I (4190) LAB_WIFI_CONN:   -> Netmask    : 255.255.255.0
I (4200) LAB_WIFI_CONN:   -> Gateway    : 10.79.236.197
I (4200) LAB_WIFI_CONN: =======================================================
I (4210) LAB_WIFI_CONN: [RESULT]: TEST PASSED - Connected to AP successfully!
I (6220) LAB_WIFI_CONN: 

I (6220) LAB_WIFI_CONN: ------------------------------------------------------------------
I (6220) LAB_WIFI_CONN: >>> Experiment 5.2.2: Connection Test - Wrong SSID (No AP Found)
I (6220) LAB_WIFI_CONN: ------------------------------------------------------------------
I (6230) LAB_WIFI_CONN:   Target SSID: "NON_EXISTENT_SSID_9999"
I (6240) LAB_WIFI_CONN:   Target Password: "12345678"
I (6240) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (6250) wifi:state: run -> init (0x0)
I (6260) wifi:pm stop, total sleep time: 1845978 us / 3410235 us

I (6260) wifi:<ba-del>idx:0, tid:0
W (6260) LAB_WIFI_CONN: =======================================================
W (6270) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (6270) LAB_WIFI_CONN:   -> Target SSID          : Cs.WiFi
W (6280) LAB_WIFI_CONN:   -> Reason Code (Decimal): 8
W (6280) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0x08
W (6290) LAB_WIFI_CONN:   -> Reason Description   : OTHER_DISCONNECT_REASON
W (6290) LAB_WIFI_CONN: =======================================================
I (6300) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (6310) wifi:flush txq
I (6310) wifi:stop sw txq
I (6310) wifi:lmac stop hw txq
I (6320) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (6360) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (6360) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (6360) wifi:mode : sta (14:33:5c:0f:55:1c)
I (6360) wifi:enable tsf
I (6370) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (6370) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (6370) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (6380) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (6390) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (6400) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (8400) LAB_WIFI_CONN: 

I (8400) LAB_WIFI_CONN: ------------------------------------------------------------------
I (8400) LAB_WIFI_CONN: >>> Experiment 5.2.3: Connection Test - Wrong Password (Auth/Handshake Fail)
I (8400) LAB_WIFI_CONN: ------------------------------------------------------------------
I (8410) LAB_WIFI_CONN:   Target SSID: "Cs.WiFi"
I (8420) LAB_WIFI_CONN:   Target Password: "WRONG_PASS_9999"
I (8420) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (8430) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (8430) wifi:flush txq
I (8430) wifi:stop sw txq
I (8440) wifi:lmac stop hw txq
I (8440) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (8470) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (8480) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (8480) wifi:mode : sta (14:33:5c:0f:55:1c)
I (8480) wifi:enable tsf
I (8480) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (8490) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (8500) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (8480) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (8510) wifi:new:<11,0>, old:<1,0>, ap:<255,255>, sta:<11,0>, prof:1, snd_ch_cfg:0x0
I (8520) wifi:state: init -> auth (0xb0)
I (8520) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (9220) wifi:state: auth -> init (0x600)
W (9230) LAB_WIFI_CONN: =======================================================
W (9230) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (9240) LAB_WIFI_CONN:   -> Target SSID          : Cs.WiFi
W (9240) LAB_WIFI_CONN:   -> Reason Code (Decimal): 202
W (9250) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0xCA
W (9250) LAB_WIFI_CONN:   -> Reason Description   : WIFI_REASON_AUTH_FAIL (202)
W (9260) LAB_WIFI_CONN: =======================================================
W (9270) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (9270) LAB_WIFI_CONN: ==================================================================
I (9280) LAB_WIFI_CONN:   [Phase 2/3/4/5 Completed: Wi-Fi Connection Lab Finished]
I (9290) LAB_WIFI_CONN: ==================================================================
I (9300) main_task: Returned from app_main()