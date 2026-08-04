# ใบงานที่ 5.4: กระบวนการแลกเปลี่ยนคีย์ความปลอดภัยและการจัดสรรหมายเลข IP Address (4-Way Handshake & IP Assignment Phase)

## 0. กล่าวนำ (Introduction)
ใบงานนี้มุ่งเน้นศึกษาขั้นตอนสุดท้ายของการเชื่อมต่อ Wi-Fi นั่นคือ **เฟสที่ 4: Four-way Handshake Phase (การตกลงคีย์ความปลอดภัย WPA2/WPA3)** และ **เฟสที่ 5: IP Assignment Phase (การขอรับหมายเลข IP Address ผ่าน DHCP)** บนเฟรมเวิร์ก ESP-IDF

นักศึกษาจะได้ศึกษาถึงกลไกการแลกเปลี่ยนเฟรม **EAPOL-Key Frames (1/4 ถึง 4/4)** เพื่อพิสูจน์ทราบความถูกต้องของรหัสผ่าน (Pre-Shared Key - PSK) โดยไม่มีการส่งรหัสผ่านจริงผ่านคลื่นวิทยุ รวมถึงสังเกตการณ์ทำงานเมื่อพิมพ์รหัสผ่านผิด ซึ่งจะนำไปสู่ความล้มเหลวในการตรวจสอบค่า MIC (Message Integrity Code) และเกิด Disconnect Event ด้วย Reason Code `15` (`WIFI_REASON_HANDSHAKE_TIMEOUT`) หรือ `204` (`WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT`)

---

## 1. วัตถุประสงค์ (Objectives)
1. เรียนรู้กลไกการแลกเปลี่ยนคีย์ความปลอดภัย WPA2 Personal (4-Way Handshake) ผ่านโปรโตคอล EAPOL
2. เข้าใจบทบาทของ PMK (Pairwise Master Key), ANonce, SNonce, PTK (Pairwise Transient Key) และ MIC (Message Integrity Code)
3. สังเกตและวิเคราะห์ลำดับการเกิด Event ระหว่าง **`WIFI_EVENT_STA_CONNECTED`** (สำเร็จในเฟส 3 Link-Layer) และ **`IP_EVENT_STA_GOT_IP`** (สำเร็จในเฟส 5 Network Layer)
4. อ่านโครงสร้างข้อมูล `ip_event_got_ip_t` เพื่อดึงค่า IP Address, Subnet Mask และ Gateway
5. ตรวจสอบความผิดปกติเมื่อพิมพ์รหัสผ่าน Wi-Fi ผิดผ่าน Disconnect Reason Code ในเฟสที่ 4

---

## 2. อุปกรณ์และซอฟต์แวร์ที่ใช้ในการทดลอง (Equipment & Tools)
1. บอร์ดไมโครคอนโทรลเลอร์ ESP32 (เช่น ESP32 DevKit V1) จำนวน 1 บอร์ด
2. สายเชื่อมต่อ Micro-USB หรือ USB-C จำนวน 1 เส้น
3. คอมพิวเตอร์ที่ติดตั้งโปรแกรม IDE เช่น VS Code พร้อมทั้ง ESP-IDF (อาจจะติดตั้งบนเครื่องหรือบน Docker ก็ได้)

---

## 3. ความรู้พื้นฐานที่เกี่ยวข้อง (Theoretical Background - ESP-IDF Framework)

### 3.1 ลำดับขั้นการแลกเปลี่ยนแพ็กเกจ 4-Way Handshake และ DHCP (Sequence Diagram)

```mermaid
sequenceDiagram
    autonumber
    participant STA as ESP32 (Station)
    participant AP as Access Point (Router)

    note over STA, AP: Phase 3 สิ้นสุด (เกิด WIFI_EVENT_STA_CONNECTED)

    rect rgb(255, 248, 220)
        note over STA, AP: Phase 4: WPA2 4-Way Handshake (EAPOL Keys)
        AP->>STA: 1/4 EAPOL-Key Frame (ส่ง ANonce)
        note over STA: คำนวณ PTK จาก PMK + ANonce + SNonce
        STA->>AP: 2/4 EAPOL-Key Frame (ส่ง SNonce + MIC)
        note over AP: ตรวจสอบ MIC (ถ้ารหัสผ่านผิด จะล้มเหลวที่จุดนี้)
        AP->>STA: 3/4 EAPOL-Key Frame (ส่ง GTK + Confirm MIC)
        STA->>AP: 4/4 EAPOL-Key Frame (ACK ยืนยันติดตั้ง Key ใน Hardware)
    end

    rect rgb(230, 230, 250)
        note over STA, AP: Phase 5: IP Assignment (DHCP Client)
        STA->>AP: DHCP Discover / Request
        AP-->>STA: DHCP Offer / ACK (มอบหมาย IP Address, Netmask, GW)
    end

    note over STA: Wi-Fi Stack ปล่อย Event: IP_EVENT_STA_GOT_IP<br/>(พร้อมสื่อสารระดับ IP Network!)
```

### 3.2 โครงสร้างข้อมูล `ip_event_got_ip_t` (Class Diagram)

```mermaid
classDiagram
    class ip_event_got_ip_t {
        +esp_ip4_addr_t ip
        +esp_ip4_addr_t netmask
        +esp_ip4_addr_t gw
        +bool ip_changed
    }
    class esp_ip4_addr_t {
        +uint32_t addr
    }

    ip_event_got_ip_t "1" *-- "3" esp_ip4_addr_t : contains
```

---

## 4. ขั้นตอนและโปรแกรมทดสอบการทดลอง (Experimental Procedures)

ในใบงานนี้ จะทำการทดสอบสถาปนาการเชื่อมต่อจนถึงขั้นตกลงคีย์เข้ารหัสและรับ IP Address ใน 2 สถานการณ์:

### 5.4.1 การเชื่อมต่อสำเร็จด้วย Password ที่ถูกต้อง (Success Case)
กำหนดค่า SSID และ Password ที่ถูกต้องตามความเป็นจริง สังเกต Forensic Log จากเฟส 3 (`WIFI_EVENT_STA_CONNECTED`) ไปสู่เฟส 4 (4-Way Handshake) และสิ้นสุดที่เฟส 5 (`IP_EVENT_STA_GOT_IP`) พร้อมบันทึกหมายเลข IP Address, Subnet Mask และ Gateway

### 5.4.2 การจำลองความล้มเหลวใน 4-Way Handshake เมื่อพิมพ์ Password ผิด (Handshake Failure Case)
กำหนดค่า SSID ถูกต้องแต่ระบุ Password ผิด (`"WRONG_PASSWORD_1234"`) สังเกต Forensic Log เพื่อยืนยันว่า ESP32 สามารถผ่านเฟส 2 และ 3 ได้ (`WIFI_EVENT_STA_CONNECTED`) แต่จะถูกตัดการเชื่อมต่อในเฟส 4 เนื่องจาก MIC ไม่ตรงกัน ส่งผลให้เกิด Disconnect Event ด้วย Reason Code `15` (`WIFI_REASON_HANDSHAKE_TIMEOUT`) หรือ `204` (`WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT`)

---

## 5. ซอร์สโค้ดการทดลอง (Complete ESP-IDF Source Code - `main.c`)

ให้นักศึกษานำซอร์สโค้ด C ต่อไปนี้ไปวางในไฟล์ `main/main.c` ของโปรเจกต์ ESP-IDF ทำการ Build และ Flash ลงบอร์ด ESP32 จากนั้นเปิด ESP-IDF Monitor (Baud Rate `115200`) เพื่อสังเกตผลการทำงาน

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

static const char *TAG = "LAB_HANDSHAKE_IP";

static EventGroupHandle_t s_wifi_event_group;

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

#define TARGET_WIFI_SSID   "MY_SSID"
#define TARGET_WIFI_PASS   "MY_PASSWORD"

static const char *get_disconnect_reason_info(uint8_t reason) {
  switch (reason) {
  case WIFI_REASON_UNSPECIFIED:
    return "WIFI_REASON_UNSPECIFIED (1)";
  case WIFI_REASON_AUTH_EXPIRE:
    return "WIFI_REASON_AUTH_EXPIRE (2)";
  case WIFI_REASON_AUTH_FAIL:
    return "WIFI_REASON_AUTH_FAIL (1/202)";
  case WIFI_REASON_ASSOC_EXPIRE:
    return "WIFI_REASON_ASSOC_EXPIRE (4)";
  case WIFI_REASON_ASSOC_FAIL:
    return "WIFI_REASON_ASSOC_FAIL (3/203)";
  case WIFI_REASON_HANDSHAKE_TIMEOUT:
    return "WIFI_REASON_HANDSHAKE_TIMEOUT (15) [Phase 4: MIC mismatch / EAPOL timeout]";
  case WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT:
    return "WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT (204) [Phase 4: Wrong Password]";
  case WIFI_REASON_NO_AP_FOUND:
    return "WIFI_REASON_NO_AP_FOUND (201) [Phase 1: SSID Not Found]";
  case WIFI_REASON_BEACON_TIMEOUT:
    return "WIFI_REASON_BEACON_TIMEOUT (200)";
  default:
    return "OTHER_DISCONNECT_REASON";
  }
}

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
      ESP_LOGI(TAG, "  -> Phase 2 (Auth) & Phase 3 (Assoc) PASSED");
      ESP_LOGI(TAG, "  -> Connected SSID  : %s", event->ssid);
      ESP_LOGI(TAG, "  -> BSSID           : %02X:%02X:%02X:%02X:%02X:%02X",
               event->bssid[0], event->bssid[1], event->bssid[2],
               event->bssid[3], event->bssid[4], event->bssid[5]);
      ESP_LOGI(TAG, "  -> Channel         : %d", event->channel);
      ESP_LOGI(TAG, "  -> Association ID  : %d", event->aid);
      ESP_LOGI(TAG, "[FORENSIC]: Entering Phase 4: 4-Way EAPOL Key Exchange...");
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
      ESP_LOGW(TAG, "  -> Reason Diagnosis     : %s",
               get_disconnect_reason_info(event->reason));
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
      ESP_LOGI(TAG, "  [SUCCESS]: Phase 4 (4-Way Handshake) & Phase 5 (DHCP IP) COMPLETED!");
      ESP_LOGI(TAG, "  -> Allocated IP Address : " IPSTR, IP2STR(&event->ip_info.ip));
      ESP_LOGI(TAG, "  -> Subnet Mask          : " IPSTR, IP2STR(&event->ip_info.netmask));
      ESP_LOGI(TAG, "  -> Default Gateway      : " IPSTR, IP2STR(&event->ip_info.gw));
      ESP_LOGI(TAG, "=======================================================");
      xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
  }
}

static void test_handshake_ip_phase(const char *test_title, const char *ssid,
                                     const char *password) {
  ESP_LOGI(TAG, "\n");
  ESP_LOGI(TAG, "------------------------------------------------------------------");
  ESP_LOGI(TAG, ">>> %s", test_title);
  ESP_LOGI(TAG, "------------------------------------------------------------------");
  ESP_LOGI(TAG, "  Target SSID    : \"%s\"", ssid);
  ESP_LOGI(TAG, "  Target Password: \"%s\"", password);

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

  EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                         WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                         pdFALSE, pdFALSE, pdMS_TO_TICKS(10000));

  if (bits & WIFI_CONNECTED_BIT) {
    ESP_LOGI(TAG, "[RESULT]: TEST PASSED - 4-Way Handshake & DHCP IP Assignment Successful!");
  } else if (bits & WIFI_FAIL_BIT) {
    ESP_LOGW(TAG, "[RESULT]: TEST FAILED - Disconnected during Handshake or Auth.");
  } else {
    ESP_LOGE(TAG, "[RESULT]: TEST TIMEOUT - Response timeout from AP/DHCP Server.");
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

  // 4. Register Event Handlers (WIFI_EVENT & IP_EVENT)
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
  ESP_LOGI(TAG, "  Lab 5.4: 4-Way Handshake & IP Assignment Phase (ESP-IDF Forensic)");
  ESP_LOGI(TAG, "==================================================================");

  // ------------------------------------------------------------------
  // 5.4.1 Successful 4-Way Handshake & DHCP IP Assignment Case
  // ------------------------------------------------------------------
  test_handshake_ip_phase("Experiment 5.4.1: Handshake & IP Test - Correct Password",
                          TARGET_WIFI_SSID, TARGET_WIFI_PASS);

  vTaskDelay(pdMS_TO_TICKS(2000));

  // ------------------------------------------------------------------
  // 5.4.2 Simulated Handshake Failure Case: Wrong Password
  // ------------------------------------------------------------------
  test_handshake_ip_phase("Experiment 5.4.2: Handshake Test - Incorrect Password",
                          TARGET_WIFI_SSID, "WRONG_PASSWORD_1234");

  ESP_LOGI(TAG, "==================================================================");
  ESP_LOGI(TAG, "  [Phase 4 & Phase 5 Completed: Wi-Fi Handshake & IP Lab Finished]");
  ESP_LOGI(TAG, "==================================================================");
}
```

---

## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองใน Handshake & IP Phase

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event `WIFI_EVENT_STA_CONNECTED` (เกิด/ไม่เกิด) | Event `IP_EVENT_STA_GOT_IP` (เกิด/ไม่เกิด) | ผลการทดลอง | Disconnect Reason Code (ถ้ามี) |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.4.1** | Password ถูกต้อง | **เกิด** | **ไม่เกิด** | Failed (ผิดปกติ — ไม่ใช่เพราะรหัสผ่านผิด ดูหมายเหตุ) | 5 / 0x05 — WIFI_REASON_ASSOC_TOOMANY |
| **5.4.2** | Password ผิด | **ไม่เกิด** | ไม่เกิด | **Failed (ตรงตามทฤษฎีที่คาดไว้)** | 15 / 0x0F — WIFI_REASON_HANDSHAKE_TIMEOUT |

> **หมายเหตุจากผลการทดลองจริง:**
> - **ข้อ 5.4.1**: ESP32 ผ่าน Phase 2/3 สำเร็จ (เห็น Event `WIFI_EVENT_STA_CONNECTED`) แต่ถูก AP (Hotspot มือถือ) ตัดการเชื่อมต่อทันทีด้วย Reason Code `5` (`ASSOC_TOOMANY` — อุปกรณ์เชื่อมต่อเต็มจำนวนที่ Hotspot อนุญาต) จึงไม่ทันได้เข้าสู่เฟส 4-Way Handshake จริง ไม่ใช่ความผิดพลาดของโค้ดหรือรหัสผ่าน (โค้ดใน `get_disconnect_reason_info()` ของ Lab 5.4 ยังไม่มี case สำหรับ Reason Code 5 จึงแสดงเป็น "OTHER_DISCONNECT_REASON" — ควรเพิ่ม case นี้เพื่อการวินิจฉัยที่ครบถ้วนขึ้น)
> - **ข้อ 5.4.2**: ทำงานได้ตรงตามทฤษฎีเป๊ะ — สังเกตจาก log internal driver `wifi:state: assoc -> run` (เวลา 3540ms) ตามด้วย `wifi:state: run -> init` (เวลา 6550ms) แสดงว่าระบบพยายามทำ 4-Way Handshake อยู่ประมาณ 3 วินาทีก่อน Timeout และได้ Reason Code `15` (`WIFI_REASON_HANDSHAKE_TIMEOUT`) ตรงตามที่ใบงานออกแบบไว้ทุกประการ — **ถือเป็นผลการทดลองที่สมบูรณ์และถูกต้อง**
> - **ข้อสังเกตเพิ่มเติมสำคัญ**: ในข้อ 5.4.2 (รหัสผ่านผิด) **ไม่มี** Event `WIFI_EVENT_STA_CONNECTED` เกิดขึ้นเลย ต่างจากที่คำถามข้อ 3 ด้านล่างสันนิษฐานไว้ (ดูคำอธิบายในคำตอบข้อ 3)

### 6.2 บันทึกข้อมูล IP Network จาก Event `IP_EVENT_STA_GOT_IP` (ข้อ 5.4.1)

**ยังไม่มีข้อมูล** — เนื่องจากข้อ 5.4.1 ถูกตัดการเชื่อมต่อด้วย Reason Code 5 (ASSOC_TOOMANY) ก่อนถึงเฟส DHCP จึงไม่มี Event `IP_EVENT_STA_GOT_IP` เกิดขึ้น ต้องลดจำนวนอุปกรณ์ที่เชื่อมต่อกับ Hotspot "Bismarck ." ให้เหลือน้อยที่สุด (ไม่มีอุปกรณ์อื่นแย่งใช้) แล้วรันโปรแกรมใหม่เพื่อเก็บค่าตารางนี้

| พารามิเตอร์ Network Layer | ค่าที่จัดสรรได้จริงจาก DHCP Server |
| :--- | :--- |
| **IP Address** | *(รอผลการรันซ้ำ)* |
| **Subnet Mask** | *(รอผลการรันซ้ำ)* |
| **Default Gateway** | *(รอผลการรันซ้ำ)* |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดกระบวนการ **4-Way Handshake** จึงพิสูจน์ทราบรหัสผ่าน Wi-Fi ได้โดยไม่ต้องส่งรหัสผ่าน (Passphrase) ลอยไปในอากาศเลยแม้แต่แพ็กเกจเดียว?

   **คำตอบ:** ทั้ง STA และ AP ต่างคำนวณ PMK จากรหัสผ่าน (Passphrase) ที่ตนเองมีอยู่แล้วภายในเครื่อง (ไม่ต้องส่งผ่านอากาศ) จากนั้นแลกเปลี่ยนเฉพาะค่าสุ่ม ANonce (จาก AP) และ SNonce (จาก STA) ผ่านเฟรม EAPOL-Key 2 เฟรมแรก แล้วทั้งสองฝ่ายนำ PMK + ANonce + SNonce + MAC Address มาคำนวณ PTK ภายในเครื่องของตัวเองแยกกัน จากนั้นแต่ละฝ่ายคำนวณค่า **MIC (Message Integrity Code)** จาก PTK ที่ตนคำนวณได้ แล้วส่ง MIC นี้แนบไปกับเฟรมที่ 2 และ 3 เพื่อให้อีกฝ่ายตรวจสอบ หากรหัสผ่านที่ทั้งสองฝ่ายใช้ตรงกัน ค่า PMK และ PTK ที่คำนวณได้จะตรงกันโดยอัตโนมัติ ทำให้ MIC ตรงกัน — กระบวนการนี้จึง **พิสูจน์ทราบว่ารหัสผ่านตรงกันหรือไม่ โดยไม่ต้องส่งรหัสผ่านจริงออกไปในอากาศเลยแม้แต่ไบต์เดียว** เป็นหลักการเดียวกับ Challenge-Response Authentication

2. อธิบายบทบาทและที่มาของคีย์ **PMK (Pairwise Master Key)** และ **PTK (Pairwise Transient Key)** ว่ามีความสัมพันธ์กันอย่างไรในการเข้ารหัสเฟรมข้อมูล?

   **คำตอบ:** **PMK** เป็นคีย์หลักที่ได้จากการนำ Passphrase (PSK) ผ่านฟังก์ชัน PBKDF2 ร่วมกับ SSID เป็น Salt (คำนวณครั้งเดียว ใช้ได้ตลอดจนกว่าจะเปลี่ยนรหัสผ่าน) ส่วน **PTK** เป็นคีย์ที่สร้างขึ้นใหม่ทุกครั้งที่มีการเชื่อมต่อ (Session-based) โดยคำนวณจาก PMK ร่วมกับค่าสุ่ม ANonce, SNonce และ MAC Address ของทั้งสองฝ่าย ผ่านฟังก์ชัน PRF ทำให้ PTK ไม่ซ้ำกันในแต่ละ Session แม้จะใช้ PMK เดิม จากนั้น PTK จะถูกแบ่งออกเป็นคีย์ย่อยอีก 3 ส่วน ได้แก่ KCK (ใช้ยืนยัน MIC), KEK (ใช้เข้ารหัส GTK ตอนส่งในเฟรมที่ 3) และ TK (ใช้เข้ารหัส/ถอดรหัสข้อมูล Unicast จริงระหว่างการสื่อสาร) กล่าวโดยสรุป PMK คือรากฐานที่มาจากรหัสผ่าน ส่วน PTK คือคีย์ปฏิบัติการจริงที่ใช้เข้ารหัสเฟรมข้อมูลในแต่ละ Session ซึ่งได้มาจาก PMK อีกที

3. เหตุใดเมื่อเราพิมพ์ Password ผิด (ข้อ 5.4.2) ESP32 จึงยังคงได้รับ Event **`WIFI_EVENT_STA_CONNECTED`** ก่อนที่จะเกิด Event **`WIFI_EVENT_STA_DISCONNECTED`** ตามมาในภายหลัง?

   **คำตอบ (ตามทฤษฎีดั้งเดิม):** ในทฤษฎีคลาสสิก Event `WIFI_EVENT_STA_CONNECTED` จะถูกโพสต์ทันทีที่ Phase 3 (Association) สำเร็จ ซึ่งเกิดขึ้น**ก่อน**ที่ 4-Way Handshake (Phase 4) จะเริ่มต้นด้วยซ้ำ เนื่องจาก Association ไม่เกี่ยวข้องกับการตรวจสอบรหัสผ่านเลย ดังนั้นไม่ว่ารหัสผ่านจะถูกหรือผิด Event นี้ควรเกิดขึ้นก่อนเสมอ แล้วค่อยตามด้วย `WIFI_EVENT_STA_DISCONNECTED` ทีหลังหากรหัสผ่านผิดและ Handshake ล้มเหลว

   **หมายเหตุสำคัญจากผลการทดลองจริง:** ผลการรันจริงในข้อ 5.4.2 **ขัดแย้งกับสมมติฐานของคำถามข้อนี้** — จาก Forensic Log ไม่ปรากฏ Event `WIFI_EVENT_STA_CONNECTED` เลยแม้แต่ครั้งเดียว มีเพียง Event `WIFI_EVENT_STA_DISCONNECTED` พร้อม Reason Code `15` เท่านั้น (สังเกตจาก internal driver log: `wifi:state: assoc -> run` ที่ 3540ms แล้วรอจนถึง `wifi:state: run -> init` ที่ 6550ms คือ Timeout ของ Handshake โดยไม่มีการ post Event STA_CONNECTED ระหว่างทางเลย) ซึ่งต่างจากพฤติกรรมที่ Lab 5.4.1 (รหัสผ่านถูก) แสดงให้เห็นชัดเจนว่า Event CONNECTED เกิดขึ้นจริง สาเหตุที่เป็นไปได้คือ ESP-IDF เวอร์ชันที่ใช้ในการทดลองนี้ (**v6.0.2**) ได้ปรับพฤติกรรมของ Driver ให้โพสต์ Event `WIFI_EVENT_STA_CONNECTED` **หลังจากที่การเชื่อมต่อสมบูรณ์ทั้ง Layer 2 และผ่าน Handshake แล้วเท่านั้น** (ต่างจาก ESP-IDF เวอร์ชันเก่าที่ Event นี้จะโพสต์ทันทีหลัง Association โดยไม่รอผล Handshake) ทำให้พฤติกรรมจริงบน Hardware นี้แตกต่างจากสมมติฐานดั้งเดิมของคำถาม — เป็นตัวอย่างที่ดีว่าทำไมการทำ Forensic Logging และสังเกตผลจริงบนฮาร์ดแวร์จึงสำคัญกว่าการท่องจำทฤษฎีเพียงอย่างเดียว

4. หากเครือข่าย Wi-Fi ไม่มี DHCP Server (ไม่มีการแจก IP อัตโนมัติ) ผลการทดลองในข้อ 5.4.1 จะหยุดอยู่ที่ขั้นตอนใด และจะไม่เกิด Event ใดขึ้น?

   **คำตอบ:** หากรหัสผ่านถูกต้องแต่เครือข่ายไม่มี DHCP Server ESP32 จะยังคงผ่าน Phase 2, 3 และ 4 (4-Way Handshake) ได้สำเร็จตามปกติ เพราะขั้นตอนเหล่านี้ไม่เกี่ยวข้องกับ DHCP เลย ดังนั้น Event `WIFI_EVENT_STA_CONNECTED` จะยังคงเกิดขึ้น (เมื่อการเชื่อมต่อ Layer 2 สมบูรณ์) แต่หลังจากนั้น ESP32 จะเข้าสู่กระบวนการ DHCP Client (ส่ง DHCP Discover) และรอ DHCP Offer จาก Server ซึ่งจะไม่มีวันได้รับตอบกลับเพราะไม่มี DHCP Server อยู่ในเครือข่าย ทำให้กระบวนการ **ค้างอยู่ที่ Phase 5 (IP Assignment)** และ Event `IP_EVENT_STA_GOT_IP` **จะไม่เกิดขึ้นเลย** ESP32 จะยังคงเชื่อมต่อในระดับ Link Layer (Layer 2) อยู่ได้เรื่อย ๆ โดยไม่มีหมายเลข IP Address ใด ๆ จึงไม่สามารถสื่อสารผ่าน TCP/IP กับอุปกรณ์อื่นได้เลย จนกว่าจะได้รับการตั้งค่า Static IP Address ด้วยตนเอง หรือ DHCP Client ทำการ timeout (ในบางการตั้งค่าอาจใช้ Auto-IP/APIPA (169.254.x.x) แทนได้หากเปิดใช้งาน Feature นี้ไว้)
