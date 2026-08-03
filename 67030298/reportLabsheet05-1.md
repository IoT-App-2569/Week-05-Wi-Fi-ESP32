# ใบงานที่ 5.1: การเชื่อมต่อ Wi-Fi และการค้นหาสัญญาณรอบข้าง (Wi-Fi Connection and Scanning)
## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบการสแกนทั้ง 4 กรณี

| ข้อการทดลอง | เงื่อนไขการสแกน | สถานะ (Success/Error Code) | จำนวน AP ที่พบ (เครือข่าย) | เวลาที่ใช้ในการสแกน (ms) |
| :---: | :--- | :---: | :---: | :---: |
| **5.1.1** | สแกนทั่วไปทุก Channel | ESP_OK (0x0) | 9 | 2502 |
| **5.1.2** | กำหนดสแกนเฉพาะ Channel 1 | ESP_OK (0x0) | 3 | 200 |
| **5.1.3** | กำหนดสแกน SSID ที่มีจริง ("KMITL-IoT") | ESP_OK (0x0) | 3 | 2499 |
| **5.1.4** | กำหนดสแกน SSID ที่ไม่มีจริง | ESP_OK (0x0) | 0 | 2498 |

### 6.2 ตารางรายละเอียด AP ที่พบจากการสแกนทั่วไป (ข้อ 5.1.1)

| ลำดับ | ชื่อเครือข่าย (SSID) | MAC Address (BSSID) | ความแรงสัญญาณ (RSSI: dBm) | ช่องความถี่ (Channel) | ประเภทการเข้ารหัส (Encryption Type) |
| :---: | :--- | :--- | :---: | :---: | :--- |
| 1 | KMITL-IoT | 78:17:BE:C0:7D:A2 | -46 | 1 | WPA2_PSK |
| 2 | Redmi Note 10S | 66:34:B4:F7:03:8A | -49 | 5 | WPA2_PSK |
| 3 | 😑 | 62:DD:AB:3C:2D:A6 | -59 | 11 | WPA2_PSK |
| 4 | PhuwishP | A6:AE:BD:24:7B:30 | -61 | 6 | WPA2_PSK |
| 5 | KMITL-IoT | 78:17:BE:C0:66:22 | -81 | 1 | WPA2_PSK |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. การกำหนดค่าในโครงสร้าง `wifi_scan_config_t` สำหรับสแกนเจาะจงเฉพาะช่องความถี่ (ข้อ 5.1.2) ช่วยลดเวลาในการสแกนเมื่อเทียบกับการสแกนทุกช่องความถี่ (ข้อ 5.1.1) อย่างไร และมีข้อจำกัดอย่างไร?
> **ช่วยลดเวลา**: สแกนเร็วขึ้นเพราะค้นหาแค่ช่องความถี่เดียว (ไม่ต้องสลับครบ 13 ช่อง)
> **ข้อจำกัด**: จะไม่พบเครือข่ายที่อยู่ช่องความถี่อื่นเลย

2. เมื่อสังเกตผล Forensic Log ในข้อ 5.1.4 (สแกนหา SSID ที่ไม่มีอยู่จริง) ฟังก์ชัน `esp_wifi_scan_start()`, `esp_wifi_scan_get_ap_num()` และ `esp_wifi_scan_get_ap_records()` ส่งคืนค่าอย่างไร?
> - `esp_wifi_scan_start()`: คืนค่า `ESP_OK` (สั่งสแกนสำเร็จ)
> - `esp_wifi_scan_get_ap_num()`: คืนค่า `ESP_OK` และได้ `ap_count = 0`
> - `esp_wifi_scan_get_ap_records()`: ไม่ถูกเรียกใช้งาน (เพราะติดเงื่อนไข `ap_count == 0`)

3. ค่าระดับความแรงสัญญาณ (RSSI) ที่แสดงเป็นตัวเลขติดลบ (เช่น -45 dBm กับ -80 dBm) ค่าใดแสดงถึงสัญญาณที่มีความแรงและความเสถียรมากกว่ากัน?
> `-45 dBm` แรงและเสถียรกว่า (ค่า RSSI ยิ่งติดลบน้อย ยิ่งแรง)

4. เหตุใดการดึงค่า `authmode` (`wifi_auth_mode_t`) จากโครงสร้าง `wifi_ap_record_t` จึงมีความสำคัญต่อการเตรียมการในเฟสถัดไป (Authentication & Association Phase)?
> เพื่อให้ทราบประเภทการเข้ารหัส (เช่น WPA2) สำหรับนำไปตั้งค่ารหัสผ่านตอน Authentication ได้อย่างถูกต้อง

---

## 8. Log ของการทดลอง (Serial Console Log)
```text
I (27) boot: ESP-IDF v6.0.2-dirty 2nd stage bootloader
I (27) boot: compile time Aug  3 2026 09:49:37
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
I (79) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1a40ch (107532) map
I (125) esp_image: segment 1: paddr=0002a434 vaddr=3ffb0000 size=04528h ( 17704) load
I (132) esp_image: segment 2: paddr=0002e964 vaddr=40080000 size=016b4h (  5812) load
I (135) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=85fb0h (548784) map
I (332) esp_image: segment 4: paddr=000b5fd8 vaddr=400816b4 size=13f54h ( 81748) load
I (366) esp_image: segment 5: paddr=000c9f34 vaddr=50000000 size=00028h (    40) load
I (377) boot: Loaded app from partition at offset 0x10000
I (377) boot: Disabling RNG early entropy source...
I (387) cpu_start: Multicore app
I (396) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (396) cpu_start: Pro cpu start user code
I (396) cpu_start: cpu freq: 160000000 Hz
I (398) app_init: Application information:
I (402) app_init: Project name:     01-Labsheet-05-1
I (406) app_init: App version:      adc27dd-dirty
I (411) app_init: Compile time:     Aug  3 2026 09:58:16
I (416) app_init: ELF file SHA256:  38e60e1dc...
I (420) app_init: ESP-IDF:          v6.0.2-dirty
I (424) efuse_init: Min chip rev:     v0.0
I (428) efuse_init: Max chip rev:     v3.99
I (432) efuse_init: Chip rev:         v3.1
I (436) heap_init: Initializing. RAM available for dynamic allocation:
I (442) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (447) heap_init: At 3FFB8A20 len 000275E0 (157 KiB): DRAM
I (453) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (458) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (464) heap_init: At 40095608 len 0000A9F8 (42 KiB): IRAM
I (470) spi_flash: detected chip: generic
I (472) spi_flash: flash io: dio
W (475) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (489) main_task: Started on CPU0
I (489) main_task: Calling app_main()
I (489) LAB_WIFI_SCAN: [FORENSIC]: Call nvs_flash_init()
I (519) LAB_WIFI_SCAN: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (519) LAB_WIFI_SCAN: [FORENSIC]: Call esp_netif_init()
I (519) LAB_WIFI_SCAN: [FORENSIC]: esp_netif_init() returned ESP_OK (0x0)
I (529) LAB_WIFI_SCAN: [FORENSIC]: Call esp_event_loop_create_default()
I (529) LAB_WIFI_SCAN: [FORENSIC]: esp_event_loop_create_default() returned ESP_OK (0x0)
I (539) LAB_WIFI_SCAN: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (549) LAB_WIFI_SCAN: [FORENSIC]: esp_netif_create_default_wifi_sta() returned pointer 0x3ffbdc70
I (559) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_init(&cfg)
I (569) wifi:wifi driver task: 3ffc035c, prio:23, stack:6656, core=0
I (579) wifi:wifi firmware version: 00ad238
I (579) wifi:wifi certification version: v7.0
I (579) wifi:config NVS flash: enabled
I (579) wifi:config nano formatting: disabled
I (589) wifi:Init data frame dynamic rx buffer num: 32
I (589) wifi:Init static rx mgmt buffer num: 5
I (599) wifi:Init management short buffer num: 32
I (599) wifi:Init dynamic tx buffer num: 32
I (599) wifi:Init static rx buffer size: 1600
I (609) wifi:Init static rx buffer num: 10
I (609) wifi:Init dynamic rx buffer num: 32
I (619) wifi_init: rx ba win: 6
I (619) wifi_init: accept mbox: 6
I (619) wifi_init: tcpip mbox: 32
I (619) wifi_init: udp mbox: 6
I (629) wifi_init: tcp mbox: 6
I (629) wifi_init: tcp tx win: 5760
I (629) wifi_init: tcp rx win: 5760
I (639) wifi_init: tcp mss: 1440
I (639) wifi_init: WiFi IRAM OP enabled
I (639) wifi_init: WiFi RX IRAM OP enabled
I (649) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_init() returned ESP_OK (0x0)
I (649) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (659) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_set_mode() returned ESP_OK (0x0)
I (669) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_start()
I (669) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06
W (679) phy_init: failed to load RF calibration data (0xffffffff), falling back to full calibration
I (769) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(2)   
I (799) wifi:mode : sta (84:1f:e8:39:bd:64)
I (799) wifi:enable tsf
I (799) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (799) LAB_WIFI_SCAN: ==================================================================
I (809) LAB_WIFI_SCAN:   Lab 5.1: Wi-Fi Connection and Scanning Phase (ESP-IDF Forensic)
I (809) LAB_WIFI_SCAN: ==================================================================
I (819) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (829) LAB_WIFI_SCAN: >>> Experiment 5.1.1: General AP Scan (All Channels)
I (839) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (849) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (3359) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2502 ms]
I (3359) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (3359) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=9
I (3369) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (3369) LAB_WIFI_SCAN: [AP COUNT]: 9 network(s) found
I (3379) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (3389) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=9

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | KMITL-IoT                | 78:17:BE:C0:7D:A2 | -46  dBm | 1    | WPA2_PSK
2    | Redmi Note 10S           | 66:34:B4:F7:03:8A | -49  dBm | 5    | WPA2_PSK
3    | 😑                     | 62:DD:AB:3C:2D:A6 | -59  dBm | 11   | WPA2_PSK
4    | PhuwishP                 | A6:AE:BD:24:7B:30 | -61  dBm | 6    | WPA2_PSK
5    | KMITL-IoT                | 78:17:BE:C0:66:22 | -81  dBm | 1    | WPA2_PSK
6    | KMITL-Legacy             | 78:17:BE:C0:66:20 | -82  dBm | 1    | WPA2_ENTERPRISE     
7    | KMITL-Legacy             | 78:17:BE:A9:94:E0 | -82  dBm | 6    | WPA2_ENTERPRISE     
8    | KMITL-WIFI               | 78:17:BE:C0:66:21 | -87  dBm | 1    | OPEN (No Password)
9    | RADAR1902601900480       | DA:BC:38:B3:75:51 | -91  dBm | 1    | WPA_WPA2_PSK        
--------------------------------------------------------------------------------------------------

I (4499) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (4499) LAB_WIFI_SCAN: >>> Experiment 5.1.2: Channel-Specific Scan (Channel 1)
I (4499) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (4509) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (4719) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 200 ms]
I (4719) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (4719) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=3
I (4729) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (4729) LAB_WIFI_SCAN: [AP COUNT]: 3 network(s) found
I (4739) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (4749) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=3

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | KMITL-Legacy             | 78:17:BE:C0:7D:A0 | -46  dBm | 1    | WPA2_ENTERPRISE     
2    | KMITL-IoT                | 78:17:BE:C0:7D:A2 | -46  dBm | 1    | WPA2_PSK            
3    | KMITL-WIFI               | 78:17:BE:C0:7D:A1 | -51  dBm | 1    | OPEN (No Password)
--------------------------------------------------------------------------------------------------

I (5809) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (5809) LAB_WIFI_SCAN: >>> Experiment 5.1.3: Targeted SSID Scan - Existing ("KMITL-IoT")
I (5809) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (5819) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (8329) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2499 ms]
I (8329) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (8329) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=3
I (8339) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (8339) LAB_WIFI_SCAN: [AP COUNT]: 3 network(s) found
I (8349) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (8359) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=3

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type
--------------------------------------------------------------------------------------------------
1    | KMITL-IoT                | 78:17:BE:C0:72:62 | -80  dBm | 11   | WPA2_PSK
2    | KMITL-IoT                | 78:17:BE:C0:66:62 | -83  dBm | 11   | WPA2_PSK
3    | KMITL-IoT                | 78:17:BE:C0:66:22 | -92  dBm | 1    | WPA2_PSK
--------------------------------------------------------------------------------------------------

I (9419) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (9419) LAB_WIFI_SCAN: >>> Experiment 5.1.4: Targeted SSID Scan - Non-Existent ("NON_EXISTENT_AP_9999")
I (9419) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (9429) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (11939) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2498 ms]
I (11939) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (11939) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=0
I (11949) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (11949) LAB_WIFI_SCAN: [AP COUNT]: 0 network(s) found
W (11959) LAB_WIFI_SCAN: [NOTE]: No Access Point found matching the criteria.
I (11959) LAB_WIFI_SCAN: ==================================================================
I (11969) LAB_WIFI_SCAN:   [Phase 1 Completed: Wi-Fi Scan Finished]
I (11979) LAB_WIFI_SCAN:   Program stopped after scanning. Auth/Assoc Phase not started.
I (11989) LAB_WIFI_SCAN: ==================================================================
I (11989) main_task: Returned from app_main()
```
