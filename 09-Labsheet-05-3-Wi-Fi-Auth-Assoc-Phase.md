# ใบงานที่ 5.3: การยืนยันตัวตนและการผูกสัมพันธ์ในระดับ Link Layer (Authentication & Association Phase)

## 0. กล่าวนำ (Introduction)
ใบงานนี้มุ่งเน้นศึกษาลงลึกเฉพาะ **เฟสที่ 2: Authentication Phase (การยืนยันตัวตนระดับ Link Layer)** และ **เฟสที่ 3: Association Phase (การผูกสัมพันธ์และการตกลงคุณสมบัติ)** บนเฟรมเวิร์ก ESP-IDF 

เมื่อ ESP32 สแกนพบ AP เป้าหมายแล้ว ขั้นตอนต่อไปคือการเข้าสู่กระบวนการแลกเปลี่ยนเฟรม 802.11 Authentication Request/Response และ 802.11 Association Request/Response เพื่อตกลงคุณสมบัติและรับหมายเลขประจำตัว **Association ID (AID)** จาก AP ก่อนที่จะก้าวเข้าสู่กระบวนการแลกเปลี่ยนคีย์ความปลอดภัย WPA2/WPA3 (4-Way Handshake) ในเฟสถัดไป

---

## 1. วัตถุประสงค์ (Objectives)
1. เรียนรู้กระบวนการทำงานในระดับ Link Layer (Phase 2: Authentication & Phase 3: Association) ตามมาตรฐาน IEEE 802.11
2. ดักจับและสังเกต Event **`WIFI_EVENT_STA_CONNECTED`** ซึ่งเป็นด่านแรกที่ยืนยันว่าการผูกสัมพันธ์ระดับ Link Layer สำเร็จสมบูรณ์
3. อ่านและวิเคราะห์พารามิเตอร์ที่ได้รับจากโครงสร้างข้อมูล `wifi_event_sta_connected_t` ได้แก่ SSID, BSSID (MAC Address), Channel, Authmode และ **Association ID (AID)**
4. จำแนกและวิเคราะห์ความแตกต่างของ Disconnect Reason Code ที่เกิดขึ้นใน Auth Phase (`WIFI_REASON_AUTH_EXPIRE`, `WIFI_REASON_AUTH_FAIL`) และ Assoc Phase (`WIFI_REASON_ASSOC_EXPIRE`, `WIFI_REASON_ASSOC_FAIL`, `WIFI_REASON_ASSOC_TOOMANY`)

---

## 2. อุปกรณ์และซอฟต์แวร์ที่ใช้ในการทดลอง (Equipment & Tools)
1. บอร์ดไมโครคอนโทรลเลอร์ ESP32 (เช่น ESP32 DevKit V1) จำนวน 1 บอร์ด
2. สายเชื่อมต่อ Micro-USB หรือ USB-C จำนวน 1 เส้น
3. คอมพิวเตอร์ที่ติดตั้งโปรแกรม IDE เช่น VS Code พร้อมทั้ง ESP-IDF (อาจจะติดตั้งบนเครื่องหรือบน Docker ก็ได้)

---

## 3. ความรู้พื้นฐานที่เกี่ยวข้อง (Theoretical Background - ESP-IDF Framework)

### 3.1 ลำดับขั้นการทำงานในระดับ Link Layer (Sequence Diagram)

```mermaid
sequenceDiagram
    autonumber
    participant STA as ESP32 (Station)
    participant AP as Access Point (Router)

    rect rgb(240, 248, 255)
        note over STA, AP: Phase 2: 802.11 Open System Authentication
        STA->>AP: 802.11 Auth Request (Algorithm: Open System)
        AP-->>STA: 802.11 Auth Response (Status: Success)
    end

    rect rgb(255, 245, 238)
        note over STA, AP: Phase 3: 802.11 Association
        STA->>AP: 802.11 Assoc Request (Capabilities, Supported Rates)
        AP-->>STA: 802.11 Assoc Response (Status: Success, Assigned AID)
    end

    note over STA: Wi-Fi Driver ปล่อย Event: WIFI_EVENT_STA_CONNECTED<br/>(Link Layer Association Complete!)
```

### 3.2 โครงสร้างข้อมูล `wifi_event_sta_connected_t` (Class Diagram)

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
    class wifi_auth_mode_t {
        <<enumeration>>
        WIFI_AUTH_OPEN
        WIFI_AUTH_WEP
        WIFI_AUTH_WPA_PSK
        WIFI_AUTH_WPA2_PSK
        WIFI_AUTH_WPA3_PSK
    }

    wifi_event_sta_connected_t "1" *-- "1" wifi_auth_mode_t : specifies
```

---

## 4. ขั้นตอนและโปรแกรมทดสอบการทดลอง (Experimental Procedures)

ในใบงานนี้ จะทดสอบสถาปนาความสัมพันธ์ในระดับ Link Layer (Phase 2 & Phase 3) เพื่อสังเกตการณ์ทำงานจนถึง Event `WIFI_EVENT_STA_CONNECTED`

### 5.3.1 การทดสอบสถาปนา Link-Layer (Phase 2 & Phase 3 Success Case)
กำหนดค่า SSID และ Password ของ AP ในพื้นที่จริง สังเกต Forensic Log เมื่อเกิด Event `WIFI_EVENT_STA_CONNECTED` อ่านค่า BSSID, Channel, Authmode และ **Association ID (AID)** ที่ AP มอบหมายให้ ESP32

### 5.3.2 การทดสอบจำลองเหตุการณ์ล้มเหลวในระดับ Link Layer (No AP Found Case)
กำหนดค่า SSID สมมุติที่ไม่มีอยู่จริง (`"NON_EXISTENT_AP_9999"`) สังเกต Forensic Log เพื่อยืนยันว่าการล้มเหลวเกิดขึ้นตั้งแต่ก่อนเข้าสู่ Auth/Assoc Phase (ส่งผลให้ได้ Disconnect Reason `201` / `WIFI_REASON_NO_AP_FOUND`)

---

## 5. ซอร์สโค้ดการทดลอง (Complete ESP-IDF Source Code - `main.c`)

ให้นักศึกษานำซอร์สโค้ด C ต่อไปนี้ไปวางในไฟล์ `main/main.c` ของโปรเจกต์ ESP-IDF ทำการ Build และ Flash ลงบอร์ด ESP32 จากนั้นเปิด ESP-IDF Monitor (Baud Rate `115200`) เพื่อสังเกตผลการทำงาน

==**คำเตือน** SSID และ PASSWORD เป็นข้อมูลส่วนบุคคล ให้ลบออกก่อน push ขึ้น origin repository==

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

static const char *TAG = "LAB_AUTH_ASSOC";

static EventGroupHandle_t s_wifi_event_group;

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

#define TARGET_WIFI_SSID   "MY_SSID"
#define TARGET_WIFI_PASS   "MY_PASSWORD"

// Convert wifi_reason_code_t to readable string with phase diagnosis
static const char *get_disconnect_reason_info(uint8_t reason) {
  switch (reason) {
  case WIFI_REASON_UNSPECIFIED:
    return "WIFI_REASON_UNSPECIFIED (1) [Phase 2/3]";
  case WIFI_REASON_AUTH_EXPIRE:
    return "WIFI_REASON_AUTH_EXPIRE (2) [Phase 2: Auth Timeout / Weak Signal]";
  case WIFI_REASON_AUTH_FAIL:
    return "WIFI_REASON_AUTH_FAIL (1/202) [Phase 2: Auth Rejected / MAC Filter]";
  case WIFI_REASON_ASSOC_EXPIRE:
    return "WIFI_REASON_ASSOC_EXPIRE (4) [Phase 3: Assoc Timeout / Packet Loss]";
  case WIFI_REASON_ASSOC_FAIL:
    return "WIFI_REASON_ASSOC_FAIL (3/203) [Phase 3: Assoc Rejected / Mismatch]";
  case WIFI_REASON_ASSOC_TOOMANY:
    return "WIFI_REASON_ASSOC_TOOMANY (5/17) [Phase 3: AP Max Clients Exceeded]";
  case WIFI_REASON_NOT_AUTHED:
    return "WIFI_REASON_NOT_AUTHED (6) [Phase 3: Assoc Sent Before Auth]";
  case WIFI_REASON_NO_AP_FOUND:
    return "WIFI_REASON_NO_AP_FOUND (201) [Phase 1: SSID Not Found]";
  case WIFI_REASON_HANDSHAKE_TIMEOUT:
    return "WIFI_REASON_HANDSHAKE_TIMEOUT (15) [Phase 4: 4-Way Handshake Timeout]";
  case WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT:
    return "WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT (204) [Phase 4: Wrong Password]";
  default:
    return "OTHER_DISCONNECT_REASON";
  }
}

// Event handler focusing on Link-Layer (Auth & Assoc Phase)
static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data) {
  if (event_base == WIFI_EVENT) {
    switch (event_id) {
    case WIFI_EVENT_STA_START:
      ESP_LOGI(TAG, "[EVENT FORENSIC]: WIFI_EVENT_STA_START received");
      ESP_LOGI(TAG, "[FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...");
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
      ESP_LOGI(TAG, "  [SUCCESS]: Phase 2 (Auth) & Phase 3 (Assoc) COMPLETED!");
      ESP_LOGI(TAG, "  -> Connected SSID        : %s", event->ssid);
      ESP_LOGI(TAG, "  -> BSSID (MAC Address)   : %02X:%02X:%02X:%02X:%02X:%02X",
               event->bssid[0], event->bssid[1], event->bssid[2],
               event->bssid[3], event->bssid[4], event->bssid[5]);
      ESP_LOGI(TAG, "  -> Channel               : %d", event->channel);
      ESP_LOGI(TAG, "  -> Auth Mode             : %d", event->authmode);
      ESP_LOGI(TAG, "  -> Association ID (AID)  : %d", event->aid);
      ESP_LOGI(TAG, "=======================================================");
      xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
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
  }
}

static void test_auth_assoc_phase(const char *test_title, const char *ssid,
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
          .threshold.authmode = WIFI_AUTH_OPEN, // Allow open auth in Link-Layer
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
                                         pdFALSE, pdFALSE, pdMS_TO_TICKS(8000));

  if (bits & WIFI_CONNECTED_BIT) {
    ESP_LOGI(TAG, "[RESULT]: TEST PASSED - Phase 2 (Auth) & Phase 3 (Assoc) Successful!");
  } else if (bits & WIFI_FAIL_BIT) {
    ESP_LOGW(TAG, "[RESULT]: TEST FAILED - Disconnected event captured in Link-Layer.");
  } else {
    ESP_LOGE(TAG, "[RESULT]: TEST TIMEOUT - Response timeout from AP.");
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

  // 4. Register Wi-Fi Event Handler
  esp_event_handler_instance_t instance_any_id;
  ESP_LOGI(TAG, "[FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)");
  ESP_ERROR_CHECK(esp_event_handler_instance_register(
      WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL,
      &instance_any_id));

  ESP_LOGI(TAG, "[FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)");
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

  ESP_LOGI(TAG, "==================================================================");
  ESP_LOGI(TAG, "  Lab 5.3: Wi-Fi Authentication & Association Phase (ESP-IDF Forensic)");
  ESP_LOGI(TAG, "==================================================================");

  // ------------------------------------------------------------------
  // 5.3.1 Auth & Assoc Test with Target AP (Link-Layer Success Case)
  // ------------------------------------------------------------------
  test_auth_assoc_phase("Experiment 5.3.1: Link-Layer Auth & Assoc Phase Test",
                        TARGET_WIFI_SSID, TARGET_WIFI_PASS);

  vTaskDelay(pdMS_TO_TICKS(2000));

  // ------------------------------------------------------------------
  // 5.3.2 Simulated Failure Case: Wrong SSID (Fails at Scan Phase)
  // ------------------------------------------------------------------
  test_auth_assoc_phase("Experiment 5.3.2: Link-Layer Test - Non-Existent AP",
                        "NON_EXISTENT_AP_9999", "12345678");

  ESP_LOGI(TAG, "==================================================================");
  ESP_LOGI(TAG, "  [Phase 2 & Phase 3 Completed: Link-Layer Auth & Assoc Finished]");
  ESP_LOGI(TAG, "==================================================================");
}
```

---

## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองในระดับ Link Layer

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event ที่ได้รับ | ผลการผูกสัมพันธ์ Link Layer | ค่า Association ID (AID) ที่ได้ | Reason Code (ถ้ามี) |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.3.1** | ร้องขอ Auth & Assoc กับ AP มีอยู่จริง | WIFI_EVENT_STA_CONNECTED ตามด้วย WIFI_EVENT_STA_DISCONNECTED ทันที | **สำเร็จชั่วขณะ** — ผ่าน Phase 2 (Auth) และ Phase 3 (Assoc) ได้ แต่ถูกตัดการเชื่อมต่อทันทีหลังจากนั้น | 34680 | 5 / 0x05 — WIFI_REASON_ASSOC_TOOMANY (AP มีจำนวนอุปกรณ์เชื่อมต่อเต็มแล้ว) |
| **5.3.2** | ร้องขอ Auth & Assoc กับ AP ไม่มีอยู่จริง | WIFI_EVENT_STA_DISCONNECTED (ไม่มี CONNECTED เลย) | Failed (ตามที่คาดไว้) | ไม่มี (ไม่เคย Associate) | 201 / 0xC9 — WIFI_REASON_NO_AP_FOUND |

> **หมายเหตุ:** ผลข้อ 5.3.1 เป็นข้อมูลจริงที่มีคุณค่าทางการเรียนรู้ — ESP32 **ผ่าน Phase 2 และ 3 ได้สำเร็จจริง** (พิสูจน์จาก Event `WIFI_EVENT_STA_CONNECTED` ที่เกิดขึ้นก่อน) แต่ AP (Hotspot มือถือ) ปฏิเสธด้วย Reason Code `5` (`ASSOC_TOOMANY`) ทันทีหลังจากนั้น ซึ่งเป็นพฤติกรรมทั่วไปของ Hotspot มือถือที่มักจำกัดจำนวนอุปกรณ์ที่เชื่อมต่อพร้อมกันได้ (เช่น จำกัดไว้ที่ 1-3 เครื่อง) กรณีนี้แสดงให้เห็นความแตกต่างจาก 5.3.2 อย่างชัดเจน — 5.3.1 ผ่านเฟส Auth/Assoc มาได้ (เห็นได้จากการมี Event CONNECTED เกิดขึ้น) ในขณะที่ 5.3.2 ล้มเหลวตั้งแต่เฟส Scan (ไม่มี Event CONNECTED เกิดขึ้นเลย)

### 6.2 บันทึกข้อมูล Link Layer จาก Event `WIFI_EVENT_STA_CONNECTED` (ข้อ 5.3.1)

| พารามิเตอร์ Link Layer | ค่าที่อ่านได้จริงจาก Forensic Log |
| :--- | :--- |
| **SSID** | Bismarck . |
| **BSSID (MAC Address)** | 6A:F4:0B:53:B6:82 |
| **Channel** | 1 |
| **Auth Mode Enum** | 3 (WIFI_AUTH_WPA2_PSK) |
| **Association ID (AID)** | 34680 |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. **Association ID (AID)** คืออะไร มีบทบาทอย่างไรใน Phase 3 และส่งคืนมาในโครงสร้างข้อมูลตัวแปรใด?

   **คำตอบ:** AID คือหมายเลขประจำตัวที่ AP มอบหมายให้กับ Station แต่ละเครื่องที่ Associate สำเร็จ เพื่อใช้ระบุตัวตนของ Client ภายในเครือข่ายนั้น ๆ ในการจัดการ Traffic เช่น การ buffer ข้อมูลระหว่างโหมด Power-Save (TIM/DTIM ใน Beacon Frame จะระบุ AID ที่มีข้อมูลรอส่งอยู่) AID จะถูกกำหนดในขั้นตอน **Association Response Frame** ซึ่งเป็นจุดสิ้นสุดของ Phase 3 และถูกส่งคืนมาในตัวแปรสมาชิก `aid` ของโครงสร้าง **`wifi_event_sta_connected_t`** จากผลการทดลองจริงข้อ 5.3.1 ได้ค่า AID = 34680 ซึ่งมากกว่าช่วงค่ามาตรฐานตามสเปก IEEE 802.11 (1-2007, ใช้ 14 บิต) อยู่มาก แสดงให้เห็นว่า Hotspot มือถือหลายรุ่นไม่ได้ยึดตามช่วงค่ามาตรฐานอย่างเคร่งครัด แต่กำหนดค่าตามอัลกอริทึมภายในของตัวเอง

2. เหตุใดการเชื่อมต่อ Wi-Fi ความปลอดภัยแบบ WPA2-PSK จึงสามารถผ่าน Phase 2 (Authentication) และ Phase 3 (Association) จนเกิด Event `WIFI_EVENT_STA_CONNECTED` ได้สำเร็จ แม้ผู้ใช้จะป้อนรหัสผ่าน (Password) ผิด?

   **คำตอบ:** เพราะ Phase 2 (Open System Authentication) และ Phase 3 (Association) ใน WPA2-PSK **ไม่มีการตรวจสอบรหัสผ่านเลย** ทั้งสองเฟสนี้เป็นเพียงกระบวนการระดับ Link Layer ที่ตกลงคุณสมบัติพื้นฐาน (Supported Rates, Capabilities) และขอ AID เท่านั้น การตรวจสอบว่ารหัสผ่านถูกต้องหรือไม่จะเกิดขึ้น**หลังจาก** `WIFI_EVENT_STA_CONNECTED` แล้ว คือในเฟสที่ 4 (4-Way EAPOL Handshake) ซึ่งเป็นจุดแรกที่ทั้งสองฝ่ายนำ PSK มาคำนวณ MIC เพื่อยืนยันตัวตนกัน ดังนั้นไม่ว่ารหัสผ่านจะถูกหรือผิด Event `WIFI_EVENT_STA_CONNECTED` จะเกิดขึ้นเสมอก่อน แล้วค่อยแยกผลลัพธ์กันในเฟสถัดไป — จากผลการทดลองจริงในโค้ดนี้ยังสังเกตเห็นพฤติกรรมที่สอดคล้องกัน คือแม้ระบบจะตั้งค่า `threshold.authmode = WIFI_AUTH_OPEN` ไว้ตอนแรก แต่เมื่อ Driver ตรวจพบว่าความยาว Password ตรงตามมาตรฐาน WPA2 ก็ปรับ threshold เป็น WPA2 อัตโนมัติ (เห็นได้จาก log บรรทัด "Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2") แต่การปรับนี้ก็ยังไม่ใช่การตรวจสอบความถูกต้องของรหัสผ่านแต่อย่างใด

3. หาก Router มีการตั้งค่า **MAC Address Filtering** (อนุญาตเฉพาะ MAC ที่ลงทะเบียน) ESP32 จะล้มเหลวในเฟสใด และจะส่ง Disconnect Reason Code ใดออกมา?

   **คำตอบ:** ESP32 จะล้มเหลวใน **Phase 2 (Authentication)** เนื่องจาก MAC Address Filtering เป็นกลไกที่ AP ตรวจสอบตั้งแต่ขั้นตอนแรกสุดของการเชื่อมต่อ (ก่อนที่จะพิจารณาเรื่อง Association หรือ Encryption Key ใด ๆ เลย) หาก MAC Address ของ ESP32 ไม่อยู่ใน Whitelist ที่ AP ตั้งค่าไว้ AP จะปฏิเสธคำขอ Authentication ทันที ส่งผลให้เกิด Disconnect Reason Code **`202` (`WIFI_REASON_AUTH_FAIL`)** หรือในบาง Router/Firmware อาจแสดงเป็น `WIFI_REASON_UNSPECIFIED (1)` แทน ขึ้นอยู่กับการ implement ของแต่ละยี่ห้อ แต่จะไม่มีทางไปถึง Phase 3 (Association) หรือ Phase 4 (4-Way Handshake) ได้เลย เพราะ MAC Filtering ตัดตั้งแต่ต้นทาง

4. สรุปความแตกต่างสำคัญระหว่างจุดสิ้นสุดของ **Phase 3 (Link-Layer Connected)** กับจุดสิ้นสุดของ **Phase 5 (IP Address Assigned)**

   **คำตอบ:** จุดสิ้นสุดของ Phase 3 (`WIFI_EVENT_STA_CONNECTED`) หมายถึงความสำเร็จใน **ระดับ Layer 2 (Data Link Layer)** เท่านั้น คือ ESP32 มีการผูกสัมพันธ์ทางกายภาพ/วิทยุกับ AP แล้ว ได้รับ AID แล้ว แต่ **ยังไม่มีการเข้ารหัสข้อมูลที่ใช้งานได้จริง** (คีย์ยังไม่ถูกแลกเปลี่ยน) และยังไม่มีหมายเลขระบุตัวตนใน Network เลย จากผลการทดลองจริงข้อ 5.3.1 จะเห็นว่าแม้ผ่าน Phase 3 ได้ แต่ก็ยังถูกตัดการเชื่อมต่อได้จากสาเหตุอื่น (เช่น ASSOC_TOOMANY) ซึ่งพิสูจน์ว่า Phase 3 สำเร็จไม่ได้แปลว่าการเชื่อมต่อ "ใช้งานได้จริง" แล้ว ในทางกลับกัน จุดสิ้นสุดของ Phase 5 (`IP_EVENT_STA_GOT_IP`) หมายถึงความสำเร็จใน **ระดับ Layer 3 (Network Layer)** คือผ่าน Phase 4 (4-Way Handshake, มีการเข้ารหัสข้อมูลแล้ว) และได้รับ IP Address จาก DHCP Server เรียบร้อย พร้อมสื่อสารกับอุปกรณ์อื่นในเครือข่ายหรืออินเทอร์เน็ตได้จริงแล้ว
