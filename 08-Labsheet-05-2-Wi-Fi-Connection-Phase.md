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
| **5.2.1** | SSID และ Password ถูกต้อง | WIFI_EVENT_STA_DISCONNECTED | **Failed** (ผิดปกติ — ดูหมายเหตุด้านล่าง) | 201 / 0xC9 | WIFI_REASON_NO_AP_FOUND |
| **5.2.2** | ระบุ SSID ผิด (ไม่มีในระบบ) | WIFI_EVENT_STA_DISCONNECTED | Failed (ตามที่คาดไว้) | 201 / 0xC9 | WIFI_REASON_NO_AP_FOUND |
| **5.2.3** | ระบุ SSID ถูกต้อง แต่ Password ผิด | WIFI_EVENT_STA_DISCONNECTED | Failed (ผิดปกติ — ดูหมายเหตุด้านล่าง) | 201 / 0xC9 | WIFI_REASON_NO_AP_FOUND |

> **หมายเหตุจากผลการทดลองจริง:** ข้อ 5.2.1 และ 5.2.3 ควรจะผ่านเฟส Scan ได้ (เพราะ SSID "Bismarck ." มีอยู่จริง) แต่ผลจริงกลับได้ Reason Code 201 เหมือนข้อ 5.2.2 ทั้งหมด แสดงว่า ESP32 **มองไม่เห็น AP "Bismarck ." เลยในขณะทดสอบ** สาเหตุที่เป็นไปได้มากที่สุดคือ Hotspot กระจายสัญญาณเป็น **5 GHz** (ESP32 รับได้เฉพาะ 2.4 GHz เท่านั้น) หรือ Hotspot ปิดอยู่ขณะทดสอบ ไม่ใช่ความผิดพลาดของโค้ด — ต้องแก้ที่การตั้งค่า Hotspot แล้วรันซ้ำ

### 6.2 บันทึกข้อมูลเครือข่ายจากการเชื่อมต่อสำเร็จ (ข้อ 5.2.1)

**ยังไม่มีข้อมูล** — การเชื่อมต่อในข้อ 5.2.1 ไม่สำเร็จในการรันครั้งนี้ (ได้ Reason Code 201 แทนที่จะเชื่อมต่อสำเร็จ) จึงไม่มี Event `IP_EVENT_STA_GOT_IP` เกิดขึ้น ทำให้ไม่มีค่า SSID/BSSID/Channel/IP ให้บันทึก ต้องแก้ปัญหา Hotspot ให้กระจายสัญญาณ 2.4 GHz แล้วรันโปรแกรมใหม่อีกครั้งเพื่อเก็บค่าตารางนี้

| พารามิเตอร์เครือข่าย | ค่าที่ได้รับจริงจาก DHCP |
| :--- | :--- |
| **SSID** | *(รอผลการรันซ้ำ)* |
| **BSSID (MAC Address)** | *(รอผลการรันซ้ำ)* |
| **Channel** | *(รอผลการรันซ้ำ)* |
| **IP Address** | *(รอผลการรันซ้ำ)* |
| **Subnet Mask** | *(รอผลการรันซ้ำ)* |
| **Default Gateway** | *(รอผลการรันซ้ำ)* |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการระบุ SSID ผิด (ข้อ 5.2.2) จึงส่งผลให้เกิด Disconnect Event ด้วย Reason Code `201` (`WIFI_REASON_NO_AP_FOUND`) ตั้งแต่เฟส Scan?

   **คำตอบ:** ก่อนที่ ESP32 จะเริ่มกระบวนการ Authentication ได้ ระบบ Wi-Fi Driver จะทำการ **Scan** หา AP ที่มี SSID ตรงกับที่ระบุไว้ใน `wifi_config_t.sta.ssid` ก่อนเสมอ (`esp_wifi_connect()` จะสั่งสแกนภายในให้อัตโนมัติ) เมื่อ SSID ที่ระบุไม่มีอยู่จริงในสภาพแวดล้อม (เช่น `"NON_EXISTENT_SSID_9999"`) การสแกนจะไม่พบ AP เป้าหมายเลย ทำให้กระบวนการเชื่อมต่อไม่สามารถดำเนินต่อไปยังเฟส Authentication ได้ ระบบจึงยกเลิกและส่ง Event `WIFI_EVENT_STA_DISCONNECTED` พร้อม Reason Code `201` (`WIFI_REASON_NO_AP_FOUND`) ทันที ซึ่งบ่งบอกว่าความล้มเหลวเกิดขึ้น **ตั้งแต่เฟสที่ 1 (Scan Phase)** ก่อนที่จะมีการแลกเปลี่ยนเฟรม 802.11 ใด ๆ กับ AP เลย จากผลการทดลองจริงในข้อ 5.2.2 ก็ยืนยันสิ่งนี้ตรงตามทฤษฎี

2. เหตุใดการพิมพ์ Password ผิด (ข้อ 5.2.3) จึงผ่านเฟส Auth และ Assoc มาได้ แต่มาล้มเหลวในเฟส 4-Way Handshake (Reason Code `15` หรือ `204`)?

   **คำตอบ (ตามทฤษฎี):** เฟส Authentication (Open System) และ Association ใน WPA2-PSK **ไม่ได้ใช้รหัสผ่านในการตรวจสอบเลย** สองเฟสนี้เป็นเพียงการแลกเปลี่ยนสถานะระดับ Link Layer เพื่อขอ Association ID (AID) จาก AP เท่านั้น รหัสผ่าน (Pre-Shared Key) จะถูกนำมาใช้ครั้งแรกในเฟสที่ 4 คือ **4-Way Handshake** ซึ่งทั้งสองฝ่ายจะคำนวณ PMK จากรหัสผ่านแล้วนำไปคำนวณ PTK พร้อม MIC เพื่อยืนยันว่ารหัสผ่านตรงกันหรือไม่ หากรหัสผ่านผิด ค่า MIC ที่ ESP32 คำนวณได้จะไม่ตรงกับที่ AP คาดหวัง ทำให้ Handshake ล้มเหลวและเกิด Reason Code `15` (`WIFI_REASON_HANDSHAKE_TIMEOUT`) หรือ `204` (`WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT`)

   **หมายเหตุจากผลการทดลองจริง:** ในการรันจริงข้อ 5.2.3 ได้ Reason Code `201` (NO_AP_FOUND) แทนที่จะเป็น `15`/`204` ตามที่คาดไว้ เนื่องจาก ESP32 หา AP "Bismarck ." ไม่เจอตั้งแต่เฟส Scan (ดูหมายเหตุในตาราง 6.1) ทำให้ไม่มีโอกาสได้ทดสอบพฤติกรรมของเฟส 4-Way Handshake จริง ๆ เลย — ต้องแก้ปัญหาความครอบคลุมสัญญาณ (เช่น เปิด Hotspot เป็น 2.4 GHz) แล้วรันซ้ำ จึงจะเห็นพฤติกรรมตามทฤษฎีข้างต้น

3. ลำดับการเกิด Event ระหว่าง **`WIFI_EVENT_STA_CONNECTED`** กับ **`IP_EVENT_STA_GOT_IP`** Event ใดเกิดขึ้นก่อนกัน และมีความหมายทางกายภาพของ Layer Network ต่างกันอย่างไร?

   **คำตอบ:** `WIFI_EVENT_STA_CONNECTED` เกิดขึ้น**ก่อนเสมอ** ตามด้วย `IP_EVENT_STA_GOT_IP` ทีหลัง เพราะทั้งสอง Event แทนความสำเร็จคนละ Layer ใน Network Stack: `WIFI_EVENT_STA_CONNECTED` หมายถึงความสำเร็จใน **Layer 2 (Data Link Layer)** คือ ESP32 ผ่านเฟส Authentication, Association และ 4-Way Handshake เรียบร้อย มีการเชื่อมต่อทางกายภาพ/ทางวิทยุกับ AP แล้ว แต่ยังไม่มีหมายเลขระบุตัวตนใน Network เลย ส่วน `IP_EVENT_STA_GOT_IP` หมายถึงความสำเร็จใน **Layer 3 (Network Layer)** คือ ESP32 ได้ทำการขอหมายเลข IP Address ผ่าน DHCP Client สำเร็จแล้ว (ได้ IP, Netmask, Gateway) ซึ่งจำเป็นต้องมีการเชื่อมต่อ Layer 2 ที่สมบูรณ์ก่อนเท่านั้นจึงจะเริ่มกระบวนการ DHCP ได้ ลำดับนี้จึงเป็นไปตามธรรมชาติของ Network Stack เสมอ (Layer ล่างสำเร็จก่อน Layer บน)

4. สมาชิกตัวแปร `reason` ในโครงสร้าง `wifi_event_sta_disconnected_t` มีประโยชน์อย่างไรต่อการออกแบบระบบค้นหาสาเหตุและกู้คืนการเชื่อมต่อ (Auto-Reconnection Mechanism) ในแอปพลิเคชัน IoT?

   **คำตอบ:** ค่า `reason` ทำให้แอปพลิเคชันสามารถแยกแยะ **สาเหตุที่แท้จริง** ของการหลุดการเชื่อมต่อได้ แทนที่จะรู้แค่ว่า "หลุดแล้ว" เฉย ๆ ซึ่งมีความสำคัญมากต่อการออกแบบ Auto-Reconnection Mechanism ที่ฉลาด เช่น จากผลการทดลองจริงในเอกสารนี้ที่ได้ Reason Code `201` (NO_AP_FOUND) ทั้ง 3 กรณี ระบบสามารถตีความได้ทันทีว่าปัญหาคือ **"หา AP ไม่เจอ"** ไม่ใช่ปัญหารหัสผ่านผิด จึงควรออกแบบให้ retry แบบมีช่วงเวลารอ (เช่น scan ใหม่ทุก 5 วินาที) แทนที่จะ retry ถี่ ๆ ด้วย credential เดิมซึ่งไม่มีทางสำเร็จ ในทางกลับกัน หากได้ Reason Code `204` (Wrong Password) ระบบควรหยุด retry ทันทีและแจ้งเตือนผู้ใช้ให้แก้ไขรหัสผ่านแทนที่จะ retry วนไปเรื่อย ๆ โดยเปล่าประโยชน์ การแยกแยะ Reason Code จึงช่วยประหยัดพลังงานแบตเตอรี่ ลดภาระเครือข่าย และทำให้ระบบ IoT ตอบสนองต่อปัญหาได้อย่างเหมาะสมตรงจุด
