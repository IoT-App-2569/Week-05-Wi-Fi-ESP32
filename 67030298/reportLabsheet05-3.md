# ใบงานที่ 5.3: การยืนยันตัวตนและการผูกสัมพันธ์ในระดับ Link Layer (Authentication & Association Phase)
## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองในระดับ Link Layer

| ข้อการทดลอง | สถานการณ์ทดสอบ                           | Event ที่ได้รับ | ผลการผูกสัมพันธ์ Link Layer | ค่า Association ID (AID) ที่ได้ | Reason Code (ถ้ามี) |
| :---------: | :--------------------------------------- | :-------------: | :-------------------------: | :-----------------------------: | :------------------ |
|  **5.3.1**  | ร้องขอ Auth & Assoc กับ AP มีอยู่จริง    | `WIFI_EVENT_STA_CONNECTED` | สำเร็จ (Success) | 34680 | - |
|  **5.3.2**  | ร้องขอ Auth & Assoc กับ AP ไม่มีอยู่จริง | `WIFI_EVENT_STA_DISCONNECTED` | ล้มเหลว (Failed) | - | 201 / 0xC9 |

### 6.2 บันทึกข้อมูล Link Layer จาก Event `WIFI_EVENT_STA_CONNECTED` (ข้อ 5.3.1)

| พารามิเตอร์ Link Layer   | ค่าที่อ่านได้จริงจาก Forensic Log |
| :----------------------- | :-------------------------------- |
| **SSID**                 | Redmi Note 10S |
| **BSSID (MAC Address)**  | 66:34:B4:F7:03:8A |
| **Channel**              | 5 |
| **Auth Mode Enum**       | 3 (WPA2_PSK) |
| **Association ID (AID)** | 34680 |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. **Association ID (AID)** คืออะไร มีบทบาทอย่างไรใน Phase 3 และส่งคืนมาในโครงสร้างข้อมูลตัวแปรใด?
   > เป็นหมายเลขประจำตัวที่ AP แจกให้ Station (คล้ายบัตรคิว) เพื่อใช้จัดการการส่งข้อมูลในเครือข่าย โดยส่งคืนมาในตัวแปร `aid` ของโครงสร้าง `wifi_event_sta_connected_t`

2. เหตุใดการเชื่อมต่อ Wi-Fi ความปลอดภัยแบบ WPA2-PSK จึงสามารถผ่าน Phase 2 (Authentication) และ Phase 3 (Association) จนเกิด Event `WIFI_EVENT_STA_CONNECTED` ได้สำเร็จ แม้ผู้ใช้จะป้อนรหัสผ่าน (Password) ผิด?
   > เพราะ Phase 2 และ 3 ของ WPA2-PSK เป็นแบบ Open System (รับเข้ามาผูกสัมพันธ์ก่อน) ส่วนการตรวจรหัสผ่านจริงๆ จะไปทำใน Phase 4 (4-Way Handshake)

3. หาก Router มีการตั้งค่า **MAC Address Filtering** (อนุญาตเฉพาะ MAC ที่ลงทะเบียน) ESP32 จะล้มเหลวในเฟสใด และจะส่ง Disconnect Reason Code ใดออกมา?
   > ล้มเหลวตั้งแต่ Phase 2 (Authentication) โดย AP จะปฏิเสธการเชื่อมต่อและส่ง Reason Code `1` (Unspecified) หรือ `202` (Auth Fail)

4. สรุปความแตกต่างสำคัญระหว่างจุดสิ้นสุดของ **Phase 3 (Link-Layer Connected)** กับจุดสิ้นสุดของ **Phase 5 (IP Address Assigned)**
   > สิ้นสุด Phase 3 คือเชื่อมต่อ Wi-Fi สำเร็จ (Layer 2) ส่วนสิ้นสุด Phase 5 คือได้รับหมายเลข IP สำเร็จ (Layer 3) พร้อมใช้งานอินเทอร์เน็ต

---

## 8. Log ของการทดลอง (Serial Console Log)
```text
I (27) boot: ESP-IDF v6.0.2-dirty 2nd stage bootloader
I (27) boot: compile time Aug  3 2026 10:35:40
I (28) boot: Multicore bootloader
I (29) boot: chip revision: v3.1
I (32) boot.esp32: SPI Speed      : 40MHz
I (36) boot.esp32: SPI Mode       : DIO
I (39) boot.esp32: SPI Flash Size : 2MB
I (43) boot: Enabling RNG early entropy source...
I (47) boot: Partition Table:
I (50) boot: ## Label            Usage          Type ST Offset   Length
I (56) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (63) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (69) boot:  2 factory          factory app      00 00 00010000 00100000
I (76) boot: End of partition table
I (79) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1a5a8h (107944) map
I (125) esp_image: segment 1: paddr=0002a5d0 vaddr=3ffb0000 size=04528h ( 17704) load
I (132) esp_image: segment 2: paddr=0002eb00 vaddr=40080000 size=01518h (  5400) load
I (135) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=861f0h (549360) map
I (332) esp_image: segment 4: paddr=000b6218 vaddr=40081518 size=140f0h ( 82160) load
I (366) esp_image: segment 5: paddr=000ca310 vaddr=50000000 size=00028h (    40) load
I (377) boot: Loaded app from partition at offset 0x10000
I (377) boot: Disabling RNG early entropy source...
I (388) cpu_start: Multicore app
I (396) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (396) cpu_start: Pro cpu start user code
I (396) cpu_start: cpu freq: 160000000 Hz
I (398) app_init: Application information:
I (402) app_init: Project name:     03-Labsheet-05-3
I (407) app_init: App version:      f9372cb-dirty
I (411) app_init: Compile time:     Aug  3 2026 10:34:22
I (416) app_init: ELF file SHA256:  04734aa24...
I (421) app_init: ESP-IDF:          v6.0.2-dirty
I (425) efuse_init: Min chip rev:     v0.0
I (429) efuse_init: Max chip rev:     v3.99 
I (433) efuse_init: Chip rev:         v3.1
I (437) heap_init: Initializing. RAM available for dynamic allocation:
I (443) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (448) heap_init: At 3FFB8A40 len 000275C0 (157 KiB): DRAM
I (453) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (459) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (464) heap_init: At 40095608 len 0000A9F8 (42 KiB): IRAM
I (471) spi_flash: detected chip: generic
I (473) spi_flash: flash io: dio
W (476) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (490) main_task: Started on CPU0
I (490) main_task: Calling app_main()
I (490) LAB_AUTH_ASSOC: [FORENSIC]: Call nvs_flash_init()
I (520) LAB_AUTH_ASSOC: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (520) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_netif_init()
I (520) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_event_loop_create_default()
I (530) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (540) LAB_AUTH_ASSOC: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbddbc
I (540) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_init(&cfg)
I (560) wifi:wifi driver task: 3ffc04a8, prio:23, stack:6656, core=0
I (570) wifi:wifi firmware version: 00ad238
I (570) wifi:wifi certification version: v7.0
I (570) wifi:config NVS flash: enabled
I (570) wifi:config nano formatting: disabled
I (580) wifi:Init data frame dynamic rx buffer num: 32
I (580) wifi:Init static rx mgmt buffer num: 5
I (590) wifi:Init management short buffer num: 32
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
I (640) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (650) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (650) LAB_AUTH_ASSOC: ==================================================================
I (660) LAB_AUTH_ASSOC:   Lab 5.3: Wi-Fi Authentication & Association Phase (ESP-IDF Forensic)
I (670) LAB_AUTH_ASSOC: ==================================================================
I (680) LAB_AUTH_ASSOC:

I (680) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (690) LAB_AUTH_ASSOC: >>> Experiment 5.3.1: Link-Layer Auth & Assoc Phase Test
I (690) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (700) LAB_AUTH_ASSOC:   Target SSID    : "Redmi Note 10S"
I (710) LAB_AUTH_ASSOC:   Target Password: "3832538325zzz"
I (710) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_stop()
I (720) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
W (720) wifi:Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2
I (730) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (740) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_start()
I (750) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06
I (840) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(0)
I (860) wifi:mode : sta (84:1f:e8:39:bd:64)
I (860) wifi:enable tsf
I (860) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (860) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (860) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (870) LAB_AUTH_ASSOC: [FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...
I (880) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (890) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (1250) wifi:new:<5,0>, old:<1,0>, ap:<255,255>, sta:<5,0>, prof:1, snd_ch_cfg:0x0
I (1250) wifi:state: init -> auth (0xb0)
I (1260) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (1280) wifi:state: auth -> assoc (0x0)
I (1300) wifi:state: assoc -> run (0x10)
I (1330) wifi:connected with Redmi Note 10S, aid = 2, channel 5, BW20, bssid = 66:34:b4:f7:03:8a
I (1330) wifi:security: WPA2-PSK, phy: bgn, rssi: -49, cipher(pairwise:0x3, group:0x3), pmf:0
I (1350) wifi:pm start, type: 1

I (1350) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (1350) LAB_AUTH_ASSOC: =======================================================
I (1360) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (1360) LAB_AUTH_ASSOC:   [SUCCESS]: Phase 2 (Auth) & Phase 3 (Assoc) COMPLETED!
I (1370) LAB_AUTH_ASSOC:   -> Connected SSID        : Redmi Note 10S
I (1380) LAB_AUTH_ASSOC:   -> BSSID (MAC Address)   : 66:34:B4:F7:03:8A
I (1380) LAB_AUTH_ASSOC:   -> Channel               : 5
I (1390) LAB_AUTH_ASSOC:   -> Auth Mode             : 3
I (1390) LAB_AUTH_ASSOC:   -> Association ID (AID)  : 34680
I (1400) LAB_AUTH_ASSOC: =======================================================
I (1400) wifi:dp: 2, bi: 102400, li: 4, scale listen interval from 307200 us to 409600 us
I (1410) wifi:AP's beacon interval = 102400 us, DTIM period = 2
I (1420) LAB_AUTH_ASSOC: [RESULT]: TEST PASSED - Phase 2 (Auth) & Phase 3 (Assoc) Successful!
I (2390) esp_netif_handlers: sta ip: 10.61.229.229, mask: 255.255.255.0, gw: 10.61.229.63
I (3430) LAB_AUTH_ASSOC: 

I (3430) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (3430) LAB_AUTH_ASSOC: >>> Experiment 5.3.2: Link-Layer Test - Non-Existent AP
I (3430) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (3440) LAB_AUTH_ASSOC:   Target SSID    : "NON_EXISTENT_AP_9999"
I (3450) LAB_AUTH_ASSOC:   Target Password: "12345678"
I (3450) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_stop()
I (3460) wifi:state: run -> init (0x0)
I (3470) wifi:pm stop, total sleep time: 1579051 us / 2118029 us

W (3470) LAB_AUTH_ASSOC: =======================================================
W (3470) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (3480) LAB_AUTH_ASSOC:   -> Target SSID          : Redmi Note 10S
W (3490) LAB_AUTH_ASSOC:   -> Reason Code (Decimal): 8
W (3490) LAB_AUTH_ASSOC:   -> Reason Code (Hex)    : 0x08
W (3500) LAB_AUTH_ASSOC:   -> Reason Diagnosis     : OTHER_DISCONNECT_REASON
W (3500) LAB_AUTH_ASSOC: =======================================================
I (3510) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (3530) wifi:flush txq
I (3530) wifi:stop sw txq
I (3530) wifi:lmac stop hw txq
I (3530) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
W (3530) wifi:Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2
I (3580) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (3580) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_start()
I (3580) wifi:mode : sta (84:1f:e8:39:bd:64)
I (3580) wifi:enable tsf
I (3590) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (3590) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (3590) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (3610) LAB_AUTH_ASSOC: [FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...
I (3610) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (3620) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (3630) LAB_AUTH_ASSOC: [RESULT]: TEST FAILED - Disconnected event captured in Link-Layer.
I (3630) LAB_AUTH_ASSOC: ==================================================================
I (3640) LAB_AUTH_ASSOC:   [Phase 2 & Phase 3 Completed: Link-Layer Auth & Assoc Finished]
I (3650) LAB_AUTH_ASSOC: ==================================================================
I (3660) main_task: Returned from app_main()
W (6040) LAB_AUTH_ASSOC: =======================================================
W (6040) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (6040) LAB_AUTH_ASSOC:   -> Target SSID          : NON_EXISTENT_AP_9999
W (6050) LAB_AUTH_ASSOC:   -> Reason Code (Decimal): 201
W (6050) LAB_AUTH_ASSOC:   -> Reason Code (Hex)    : 0xC9
W (6060) LAB_AUTH_ASSOC:   -> Reason Diagnosis     : WIFI_REASON_NO_AP_FOUND (201) [Phase 1: SSID Not Found]
W (6070) LAB_AUTH_ASSOC: =======================================================
```
