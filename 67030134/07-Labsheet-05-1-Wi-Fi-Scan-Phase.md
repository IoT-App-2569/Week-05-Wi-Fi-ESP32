#### 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบการสแกนทั้ง 4 กรณี

| ข้อการทดลอง | เงื่อนไขการสแกน             | สถานะ (Success/Error Code) | จำนวน AP ที่พบ (เครือข่าย) | เวลาที่ใช้ในการสแกน (ms) |
| :---------: | :-------------------------- | :------------------------: | :------------------------: | :----------------------: |
|  **5.1.1**  | สแกนทั่วไปทุก Channel       |   Success (ESP_OK / 0x0)   |             15             |         2493 ms          |
|  **5.1.2**  | กำหนดสแกนเฉพาะ Channel 1    |   Success (ESP_OK / 0x0)   |             6              |          200 ms          |
|  **5.1.3**  | กำหนดสแกน SSID ที่มีจริง    |   Success (ESP_OK / 0x0)   |             5              |         2499 ms          |
|  **5.1.4**  | กำหนดสแกน SSID ที่ไม่มีจริง |   Success (ESP_OK / 0x0)   |             0              |         2498 ms          |

### 6.2 ตารางรายละเอียด AP ที่พบจากการสแกนทั่วไป (ข้อ 5.1.1)

| ลำดับ | ชื่อเครือข่าย (SSID) | MAC Address (BSSID) | ความแรงสัญญาณ (RSSI: dBm) | ช่องความถี่ (Channel) | ประเภทการเข้ารหัส (Encryption Type) |
| :---: | :------------------- | :------------------ | :-----------------------: | :-------------------: | :---------------------------------- |
|   1   | KMITL-IoT            | 78:17:BE:C0:7D:A2   |          -55 dBm          |           1           | WPA2_PSK                            |
|   2   | KMITL-Legacy         | 78:17:BE:C0:7D:A0   |          -56 dBm          |           1           | WPA2_ENTERPRISE                     |
|   3   | KMITL-WIFI           | 78:17:BE:C0:7D:A1   |          -57 dBm          |           1           | OPEN (No Password)                  |
|   4   | KMITL-Legacy         | 78:17:BE:C0:66:20   |          -75 dBm          |           1           | WPA2_ENTERPRISE                     |
|   5   | KMITL-IoT            | 78:17:BE:C0:66:22   |          -76 dBm          |           1           | WPA2_PSK                            |
|   6   | KBBK-IPHONE          | 2E:EC:B9:E4:42:C3   |          -77 dBm          |           6           | WPA2_WPA3_PSK                       |
|   7   | KMITL-WIFI           | 78:17:BE:C0:66:21   |          -79 dBm          |           1           | OPEN (No Password)                  |
|   8   | KMITL-IoT            | 78:17:BE:C0:66:62   |          -80 dBm          |          11           | WPA2_PSK                            |
|   9   | KMITL-Legacy         | 78:17:BE:C0:66:60   |          -80 dBm          |          11           | WPA2_ENTERPRISE                     |
|  10   | KMITL-WIFI           | 78:17:BE:C0:66:61   |          -83 dBm          |          11           | OPEN (No Password)                  |
|  11   | KMITL-IoT            | 78:17:BE:A9:94:E2   |          -86 dBm          |           6           | WPA2_PSK                            |
|  12   | KMITL-Legacy         | 78:17:BE:A9:94:E0   |          -87 dBm          |           6           | WPA2_ENTERPRISE                     |
|  13   | KMITL-WIFI           | 78:17:BE:A9:94:E1   |          -87 dBm          |           6           | OPEN (No Password)                  |
|  14   | KMITL-Legacy         | 78:17:BE:A9:94:60   |          -90 dBm          |          11           | WPA2_ENTERPRISE                     |
| 15 | KMITL-IoT | 78:17:BE:A9:94:62 | -92 dBm | 11 | WPA2_PSK |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. การกำหนดค่าในโครงสร้าง `wifi_scan_config_t` สำหรับสแกนเจาะจงเฉพาะช่องความถี่ (ข้อ 5.1.2) ช่วยลดเวลาในการสแกนเมื่อเทียบกับการสแกนทุกช่องความถี่ (ข้อ 5.1.1) อย่างไร และมีข้อจำกัดอย่างไร?
2. เมื่อสังเกตผล Forensic Log ในข้อ 5.1.4 (สแกนหา SSID ที่ไม่มีอยู่จริง) ฟังก์ชัน `esp_wifi_scan_start()`, `esp_wifi_scan_get_ap_num()` และ `esp_wifi_scan_get_ap_records()` ส่งคืนค่าอย่างไร?
3. ค่าระดับความแรงสัญญาณ (RSSI) ที่แสดงเป็นตัวเลขติดลบ (เช่น -45 dBm กับ -80 dBm) ค่าใดแสดงถึงสัญญาณที่มีความแรงและความเสถียรมากกว่ากัน?
4. เหตุใดการดึงค่า `authmode` (`wifi_auth_mode_t`) จากโครงสร้าง `wifi_ap_record_t` จึงมีความสำคัญต่อการเตรียมการในเฟสถัดไป (Authentication & Association Phase)?
# Log
```
I (29) boot: ESP-IDF v5.5.1 2nd stage bootloader
I (29) boot: compile time Aug  4 2026 10:10:03
I (29) boot: Multicore bootloader
I (31) boot: chip revision: v3.1
I (33) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode       : DIO
I (41) boot.esp32: SPI Flash Size : 2MB
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (58) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory          factory app      00 00 00010000 00100000
I (77) boot: End of partition table
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=19b74h (105332) map
I (124) esp_image: segment 1: paddr=00029b9c vaddr=3ffb0000 size=03eech ( 16108) load
I (130) esp_image: segment 2: paddr=0002da90 vaddr=40080000 size=02588h (  9608) load
I (134) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=86364h (549732) map
I (323) esp_image: segment 4: paddr=000b638c vaddr=40082588 size=15884h ( 88196) load
I (358) esp_image: segment 5: paddr=000cbc18 vaddr=50000000 size=00020h (    32) load
I (370) boot: Loaded app from partition at offset 0x10000
I (370) boot: Disabling RNG early entropy source...
I (380) cpu_start: Multicore app
I (389) cpu_start: Pro cpu start user code
I (389) cpu_start: cpu freq: 160000000 Hz
I (389) app_init: Application information:
I (389) app_init: Project name:     wifi_scan_phase
I (393) app_init: App version:      37de524-dirty
I (398) app_init: Compile time:     Aug  4 2026 10:08:42
I (403) app_init: ELF file SHA256:  6ac53f238...
I (407) app_init: ESP-IDF:          v5.5.1
I (411) efuse_init: Min chip rev:     v0.0
I (415) efuse_init: Max chip rev:     v3.99 
I (419) efuse_init: Chip rev:         v3.1
I (423) heap_init: Initializing. RAM available for dynamic allocation:
I (429) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (434) heap_init: At 3FFB7FC8 len 00028038 (160 KiB): DRAM
I (439) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (445) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (450) heap_init: At 40097E0C len 000081F4 (32 KiB): IRAM
W (457) spi_flash: Detected boya flash chip but using generic driver. For optimal functionality, enable `SPI_FLASH_SUPPORT_BOYA_CHIP` in menuconfig
I (468) spi_flash: detected chip: generic
I (472) spi_flash: flash io: dio
W (475) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (488) main_task: Started on CPU0
I (498) main_task: Calling app_main()
I (498) LAB_WIFI_SCAN: [FORENSIC]: Call nvs_flash_init()
I (508) LAB_WIFI_SCAN: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (508) LAB_WIFI_SCAN: [FORENSIC]: Call esp_netif_init()
I (508) LAB_WIFI_SCAN: [FORENSIC]: esp_netif_init() returned ESP_OK (0x0)
I (518) LAB_WIFI_SCAN: [FORENSIC]: Call esp_event_loop_create_default()
I (518) LAB_WIFI_SCAN: [FORENSIC]: esp_event_loop_create_default() returned ESP_OK (0x0)
I (528) LAB_WIFI_SCAN: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (538) LAB_WIFI_SCAN: [FORENSIC]: esp_netif_create_default_wifi_sta() returned pointer 0x3ffbd784
I (548) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_init(&cfg)
I (558) wifi:wifi driver task: 3ffbfe70, prio:23, stack:6656, core=0
I (558) wifi:wifi firmware version: 14da9b7
I (558) wifi:wifi certification version: v7.0
I (558) wifi:config NVS flash: enabled
I (568) wifi:config nano formatting: disabled
I (568) wifi:Init data frame dynamic rx buffer num: 32
I (578) wifi:Init static rx mgmt buffer num: 5
I (578) wifi:Init management short buffer num: 32
I (588) wifi:Init dynamic tx buffer num: 32
I (588) wifi:Init static rx buffer size: 1600
I (588) wifi:Init static rx buffer num: 10
I (598) wifi:Init dynamic rx buffer num: 32
I (598) wifi_init: rx ba win: 6
I (598) wifi_init: accept mbox: 6
I (608) wifi_init: tcpip mbox: 32
I (608) wifi_init: udp mbox: 6
I (608) wifi_init: tcp mbox: 6
I (618) wifi_init: tcp tx win: 5760
I (618) wifi_init: tcp rx win: 5760
I (618) wifi_init: tcp mss: 1440
I (628) wifi_init: WiFi IRAM OP enabled
I (628) wifi_init: WiFi RX IRAM OP enabled
I (628) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_init() returned ESP_OK (0x0)
I (638) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (648) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_set_mode() returned ESP_OK (0x0)
I (648) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_start()
I (658) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (748) wifi:mode : sta (14:08:08:a4:b6:60)
I (748) wifi:enable tsf
I (748) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (748) LAB_WIFI_SCAN: ==================================================================
I (758) LAB_WIFI_SCAN:   Lab 5.1: Wi-Fi Connection and Scanning Phase (ESP-IDF Forensic)
I (758) LAB_WIFI_SCAN: ==================================================================
I (768) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (778) LAB_WIFI_SCAN: >>> Experiment 5.1.1: General AP Scan (All Channels)
I (788) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (788) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (3298) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2493 ms]
I (3298) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (3298) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=15
I (3308) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (3308) LAB_WIFI_SCAN: [AP COUNT]: 15 network(s) found
I (3318) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (3328) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=15

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | KMITL-IoT                | 78:17:BE:C0:7D:A2 | -55  dBm | 1    | WPA2_PSK            
2    | KMITL-Legacy             | 78:17:BE:C0:7D:A0 | -56  dBm | 1    | WPA2_ENTERPRISE     
3    | KMITL-WIFI               | 78:17:BE:C0:7D:A1 | -57  dBm | 1    | OPEN (No Password)  
4    | KMITL-Legacy             | 78:17:BE:C0:66:20 | -75  dBm | 1    | WPA2_ENTERPRISE     
5    | KMITL-IoT                | 78:17:BE:C0:66:22 | -76  dBm | 1    | WPA2_PSK            
6    | KBBK-IPHONE              | 2E:EC:B9:E4:42:C3 | -77  dBm | 6    | WPA2_WPA3_PSK       
7    | KMITL-WIFI               | 78:17:BE:C0:66:21 | -79  dBm | 1    | OPEN (No Password)  
8    | KMITL-IoT                | 78:17:BE:C0:66:62 | -80  dBm | 11   | WPA2_PSK            
9    | KMITL-Legacy             | 78:17:BE:C0:66:60 | -80  dBm | 11   | WPA2_ENTERPRISE     
10   | KMITL-WIFI               | 78:17:BE:C0:66:61 | -83  dBm | 11   | OPEN (No Password)  
11   | KMITL-IoT                | 78:17:BE:A9:94:E2 | -86  dBm | 6    | WPA2_PSK            
12   | KMITL-Legacy             | 78:17:BE:A9:94:E0 | -87  dBm | 6    | WPA2_ENTERPRISE     
13   | KMITL-WIFI               | 78:17:BE:A9:94:E1 | -87  dBm | 6    | OPEN (No Password)  
14   | KMITL-Legacy             | 78:17:BE:A9:94:60 | -90  dBm | 11   | WPA2_ENTERPRISE     
15   | KMITL-IoT                | 78:17:BE:A9:94:62 | -92  dBm | 11   | WPA2_PSK            
--------------------------------------------------------------------------------------------------

I (4488) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (4488) LAB_WIFI_SCAN: >>> Experiment 5.1.2: Channel-Specific Scan (Channel 1)
I (4488) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (4498) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (4708) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 200 ms]
I (4708) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (4708) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=6
I (4718) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (4718) LAB_WIFI_SCAN: [AP COUNT]: 6 network(s) found
I (4728) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (4738) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=6

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | KMITL-WIFI               | 78:17:BE:C0:7D:A1 | -60  dBm | 1    | OPEN (No Password)  
2    | KMITL-Legacy             | 78:17:BE:C0:7D:A0 | -61  dBm | 1    | WPA2_ENTERPRISE     
3    | KMITL-IoT                | 78:17:BE:C0:7D:A2 | -62  dBm | 1    | WPA2_PSK            
4    | KMITL-Legacy             | 78:17:BE:C0:66:20 | -78  dBm | 1    | WPA2_ENTERPRISE     
5    | KMITL-IoT                | 78:17:BE:C0:66:22 | -79  dBm | 1    | WPA2_PSK            
6    | KMITL-WIFI               | 78:17:BE:C0:66:21 | -83  dBm | 1    | OPEN (No Password)  
--------------------------------------------------------------------------------------------------

I (5828) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (5828) LAB_WIFI_SCAN: >>> Experiment 5.1.3: Targeted SSID Scan - Existing ("KMITL-IoT")
I (5828) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (5838) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (8348) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2499 ms]
I (8348) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (8348) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=5
I (8358) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (8358) LAB_WIFI_SCAN: [AP COUNT]: 5 network(s) found
I (8368) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (8378) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=5

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | KMITL-IoT                | 78:17:BE:C0:7D:A2 | -60  dBm | 1    | WPA2_PSK            
2    | KMITL-IoT                | 78:17:BE:C0:66:22 | -76  dBm | 1    | WPA2_PSK            
3    | KMITL-IoT                | 78:17:BE:C0:66:62 | -81  dBm | 11   | WPA2_PSK            
4    | KMITL-IoT                | 78:17:BE:A9:94:E2 | -87  dBm | 6    | WPA2_PSK            
5    | KMITL-IoT                | 78:17:BE:C0:72:62 | -90  dBm | 11   | WPA2_PSK            
--------------------------------------------------------------------------------------------------

I (9458) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (9458) LAB_WIFI_SCAN: >>> Experiment 5.1.4: Targeted SSID Scan - Non-Existent ("NON_EXISTENT_AP_9999")
I (9458) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (9468) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (11978) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2498 ms]
I (11978) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (11978) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=0
I (11988) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (11988) LAB_WIFI_SCAN: [AP COUNT]: 0 network(s) found
W (11998) LAB_WIFI_SCAN: [NOTE]: No Access Point found matching the criteria.
I (11998) LAB_WIFI_SCAN: ==================================================================
I (12008) LAB_WIFI_SCAN:   [Phase 1 Completed: Wi-Fi Scan Finished]
I (12018) LAB_WIFI_SCAN:   Program stopped after scanning. Auth/Assoc Phase not started.
I (12028) LAB_WIFI_SCAN: ==================================================================
I (12028) main_task: Returned from app_main()
```

## 08-Labsheet-05-2-Wi-Fi-Connection-Phase
#### 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองทั้ง 3 สถานการณ์

| ข้อการทดลอง | สถานการณ์ทดสอบ                     |   Event สุดท้ายที่ได้รับ    | ผลลัพธ์ (Passed/Failed) | Reason Code (Decimal / Hex) | คำอธิบาย Reason Code               |
| :---------: | :--------------------------------- | :-------------------------: | :---------------------: | :-------------------------: | :--------------------------------- |
|  **5.2.1**  | SSID และ Password ถูกต้อง          |     IP_EVENT_STA_GOT_IP     |         PASSED          |              -              | Connected & Got IP                 |
|  **5.2.2**  | ระบุ SSID ผิด (ไม่มีในระบบ)        | WIFI_EVENT_STA_DISCONNECTED |         FAILED          |          8 / 0x08           | OTHER_DISCONNECT_REASON            |
|  **5.2.3**  | ระบุ SSID ถูกต้อง แต่ Password ผิด | WIFI_EVENT_STA_DISCONNECTED |         FAILED          |          15 / 0x0F          | WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT |

### 6.2 บันทึกข้อมูลเครือข่ายจากการเชื่อมต่อสำเร็จ (ข้อ 5.2.1)

| พารามิเตอร์เครือข่าย    | ค่าที่ได้รับจริงจาก DHCP |
| :---------------------- | :----------------------- |
| **SSID**                | Thanutorn                |
| **BSSID (MAC Address)** | D6:65:F4:32:83:9C        |
| **Channel**             | 6                        |
| **IP Address**          | 10.219.61.222            |
| **Subnet Mask**         | 255.255.255.0            |
| **Default Gateway**     | 10.219.61.159            |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

**1. เหตุใดการระบุ SSID ผิด (ข้อ 5.2.2) จึงส่งผลให้เกิด Disconnect Event (จากผลการทดลองจริงได้รับ Reason Code 8 / หรือ Reason Code 201 เมื่อไม่พบตั้งแต่แรก)?**

- เพราะเมื่อระบุชื่อเครือข่าย (SSID) ไม่ถูกต้อง ตัวเครื่อง ESP32 จะไม่สามารถหา Access Point ที่ตรงกับเป้าหมายได้ในกระบวนการสแกนหรือพยายามเชื่อมต่อ ระบบจึงไม่สามารถเข้าสู่ขั้นตอนการยืนยันตัวตนหรือสร้างการเชื่อมต่อได้ สมุฏฐานของเหตุการณ์จึงถูกตัดการเชื่อมต่อด้วยเหตุผลที่ไม่พบเครือข่ายเป้าหมาย
    

**2. เหตุใดการพิมพ์ Password ผิด (ข้อ 5.2.3) จึงผ่านเฟส Auth และ Assoc มาได้ แต่มาล้มเหลวในเฟส 4-Way Handshake (Reason Code 15 หรือ 204)?**

- เพราะในขั้นตอนการตรวจสอบสิทธิ์เบื้องต้น (Authentication) และการเชื่อมต่อเลเยอร์ลิงก์ (Association) อุปกรณ์จะยังไม่ได้ตรวจสอบความถูกต้องของรหัสผ่าน (Pre-Shared Key) แต่จะเป็นการตกลงยอมรับการเชื่อมต่อวิทยุขั้นพื้นฐานก่อน เมื่อเชื่อมต่อสำเร็จแล้วจึงเข้าสู่กระบวนการ **4-Way Handshake** เพื่อแลกเปลี่ยนและตรวจสอบรหัสผ่านร่วมกัน หากรหัสผ่านไม่ตรงกัน Access Point จะปฏิเสธและตัดการเชื่อมต่อ พร้อมส่ง Reason Code 15 (`WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT`) กลับมา
    

**3. ลำดับการเกิด Event ระหว่าง `WIFI_EVENT_STA_CONNECTED` กับ `IP_EVENT_STA_GOT_IP` Event ใดเกิดขึ้นก่อนกัน และมีความหมายทางกายภาพของ Layer Network ต่างกันอย่างไร?**

- **ลำดับการเกิด:** `WIFI_EVENT_STA_CONNECTED` จะเกิดขึ้น **ก่อน** `IP_EVENT_STA_GOT_IP` เสมอ
    
- **ความหมายทางเลเยอร์ Network:**
    
    - `WIFI_EVENT_STA_CONNECTED` อยู่ในระดับ **Data Link Layer (Layer 2)** หมายถึง ESP32 ได้ทำการเชื่อมต่อคลื่นวิทยุและจับคู่สถานะ (Association) กับ Access Point สำเร็จแล้ว
        
    - `IP_EVENT_STA_GOT_IP` อยู่ในระดับ **Network Layer (Layer 3)** หมายถึง หลังจากเชื่อมต่อเลเยอร์ 2 สำเร็จ ตัวเครื่องได้ติดต่อไปยัง DHCP Server เพื่อขอรับหมายเลข IP Address มาใช้งานบนเครือข่ายเรียบร้อยแล้ว พร้อมสำหรับการรับ-ส่งข้อมูลในระบบไอพี
        

**4. สมาชิกตัวแปร `reason` ในโครงสร้าง `wifi_event_sta_disconnected_t` มีประโยชน์อย่างไรต่อการออกแบบระบบค้นหาสาเหตุและกู้คืนการเชื่อมต่อ (Auto-Reconnection Mechanism) ในแอปพลิเคชัน IoT?**

- มีประโยชน์อย่างมากในการช่วยให้เฟิร์มแวร์สามารถ **"วิเคราะห์และตัดสินใจแก้ไขปัญหาเฉพาะหน้าได้อย่างตรงจุด"** แทนที่จะพยายามเชื่อมต่อซ้ำแบบสุ่ม (Blind Reconnection) เช่น:
    
    - หากได้รับ Reason Code ที่สื่อถึงปัญหาเร้าเตอร์หรือสัญญาณหาย ระบบอาจตั้งเวลารอแล้วลองสแกนเชื่อมต่อใหม่
        
    - หากได้รับ Reason Code ที่สื่อถึงรหัสผ่านไม่ถูกต้องหรือปัญหาการตรวจสอบสิทธิ์ ระบบควรหยุดความพยายามเชื่อมต่อวนซ้ำเพื่อป้องกันการสิ้นเปลืองพลังงาน และแจ้งเตือนให้ผู้ใช้รับทราบเพื่อตั้งค่าใหม่ผ่านหน้าจอหรือ Configuration Interface แทน

# Log
```
I (29) boot: ESP-IDF v5.5.1 2nd stage bootloader
I (29) boot: compile time Aug  4 2026 11:22:16
I (29) boot: Multicore bootloader
I (31) boot: chip revision: v3.1
I (33) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode       : DIO
I (41) boot.esp32: SPI Flash Size : 2MB
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (58) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory          factory app      00 00 00010000 00100000
I (77) boot: End of partition table
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=19e38h (106040) map
I (124) esp_image: segment 1: paddr=00029e60 vaddr=3ffb0000 size=03eech ( 16108) load
I (130) esp_image: segment 2: paddr=0002dd54 vaddr=40080000 size=022c4h (  8900) load
I (134) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=861fch (549372) map
I (323) esp_image: segment 4: paddr=000b6224 vaddr=400822c4 size=15b48h ( 88904) load
I (358) esp_image: segment 5: paddr=000cbd74 vaddr=50000000 size=00020h (    32) load
I (370) boot: Loaded app from partition at offset 0x10000
I (370) boot: Disabling RNG early entropy source...
I (381) cpu_start: Multicore app
I (389) cpu_start: Pro cpu start user code
I (389) cpu_start: cpu freq: 160000000 Hz
I (389) app_init: Application information:
I (389) app_init: Project name:     wifi_connection_phase
I (394) app_init: App version:      37de524-dirty
I (399) app_init: Compile time:     Aug  4 2026 11:20:59
I (404) app_init: ELF file SHA256:  1d2247811...
I (408) app_init: ESP-IDF:          v5.5.1
I (412) efuse_init: Min chip rev:     v0.0
I (416) efuse_init: Max chip rev:     v3.99 
I (420) efuse_init: Chip rev:         v3.1
I (424) heap_init: Initializing. RAM available for dynamic allocation:
I (430) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (435) heap_init: At 3FFB7FD0 len 00028030 (160 KiB): DRAM
I (440) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (446) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (451) heap_init: At 40097E0C len 000081F4 (32 KiB): IRAM
W (458) spi_flash: Detected boya flash chip but using generic driver. For optimal functionality, enable `SPI_FLASH_SUPPORT_BOYA_CHIP` in menuconfig
I (469) spi_flash: detected chip: generic
I (473) spi_flash: flash io: dio
W (476) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (489) main_task: Started on CPU0
I (499) main_task: Calling app_main()
I (499) LAB_WIFI_CONN: [FORENSIC]: Call nvs_flash_init()
I (519) LAB_WIFI_CONN: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (519) LAB_WIFI_CONN: [FORENSIC]: Call esp_netif_init()
I (519) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_loop_create_default()
I (529) LAB_WIFI_CONN: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (529) LAB_WIFI_CONN: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbd940
I (539) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_init(&cfg)
I (559) wifi:wifi driver task: 3ffc002c, prio:23, stack:6656, core=0
I (569) wifi:wifi firmware version: 14da9b7
I (569) wifi:wifi certification version: v7.0
I (569) wifi:config NVS flash: enabled
I (569) wifi:config nano formatting: disabled
I (579) wifi:Init data frame dynamic rx buffer num: 32
I (579) wifi:Init static rx mgmt buffer num: 5
I (579) wifi:Init management short buffer num: 32
I (589) wifi:Init dynamic tx buffer num: 32
I (589) wifi:Init static rx buffer size: 1600
I (599) wifi:Init static rx buffer num: 10
I (599) wifi:Init dynamic rx buffer num: 32
I (609) wifi_init: rx ba win: 6
I (609) wifi_init: accept mbox: 6
I (609) wifi_init: tcpip mbox: 32
I (609) wifi_init: udp mbox: 6
I (619) wifi_init: tcp mbox: 6
I (619) wifi_init: tcp tx win: 5760
I (619) wifi_init: tcp rx win: 5760
I (629) wifi_init: tcp mss: 1440
I (629) wifi_init: WiFi IRAM OP enabled
I (629) wifi_init: WiFi RX IRAM OP enabled
I (639) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (639) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_handler_instance_register(IP_EVENT)
I (649) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (659) LAB_WIFI_CONN: =================================================================
I (669) LAB_WIFI_CONN:   Lab 5.2: Wi-Fi Connection & IP Assignment (ESP-IDF Forensic)
I (669) LAB_WIFI_CONN: ==================================================================
I (679) LAB_WIFI_CONN: 
I (679) LAB_WIFI_CONN: ------------------------------------------------------------------
I (689) LAB_WIFI_CONN: >>> Experiment 5.2.1: Connection Test - Correct Credentials
I (699) LAB_WIFI_CONN: ------------------------------------------------------------------
I (709) LAB_WIFI_CONN:   Target SSID: "Thanutorn"
I (709) LAB_WIFI_CONN:   Target Password: "noeynoey"
I (719) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (719) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (769) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (769) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (769) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (849) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(0)
I (929) wifi:mode : sta (14:08:08:a4:b6:60)
I (929) wifi:enable tsf
I (929) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (929) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (929) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (939) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (949) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (1829) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
I (1839) wifi:state: init -> auth (0xb0)
I (1839) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (1859) wifi:state: auth -> assoc (0x0)
I (1869) wifi:state: assoc -> run (0x10)
I (1909) wifi:connected with Thanutorn, aid = 1, channel 6, BW20, bssid = d6:65:f4:32:83:9c
I (1909) wifi:security: WPA2-PSK, phy: bgn, rssi: -22
I (1929) wifi:pm start, type: 1
I (1929) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (1929) LAB_WIFI_CONN: =======================================================
I (1929) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (1939) LAB_WIFI_CONN:   -> Connected to SSID : Thanutorn
I (1949) LAB_WIFI_CONN:   -> BSSID            : D6:65:F4:32:83:9C
I (1949) LAB_WIFI_CONN:   -> Channel          : 6
I (1959) LAB_WIFI_CONN:   -> Auth Mode        : 3
I (1959) LAB_WIFI_CONN: =======================================================
I (1949) wifi:<ba-add>idx:0 (ifx:0, d6:65:f4:32:83:9c), tid:0, ssn:0, winSize:64
I (1999) wifi:dp: 2, bi: 102400, li: 4, scale listen interval from 307200 us to 409600 us
I (1999) wifi:AP's beacon interval = 102400 us, DTIM period = 2
I (3009) esp_netif_handlers: sta ip: 10.219.61.222, mask: 255.255.255.0, gw: 10.219.61.159
I (3009) LAB_WIFI_CONN: =======================================================
I (3009) LAB_WIFI_CONN: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!
I (3019) LAB_WIFI_CONN:   -> IP Address : 10.219.61.222
I (3019) LAB_WIFI_CONN:   -> Netmask    : 255.255.255.0
I (3029) LAB_WIFI_CONN:   -> Gateway    : 10.219.61.159
I (3029) LAB_WIFI_CONN: =======================================================
I (3039) LAB_WIFI_CONN: [RESULT]: TEST PASSED - Connected to AP successfully!
I (5049) LAB_WIFI_CONN: 
I (5049) LAB_WIFI_CONN: ------------------------------------------------------------------
I (5049) LAB_WIFI_CONN: >>> Experiment 5.2.2: Connection Test - Wrong SSID (No AP Found)
I (5049) LAB_WIFI_CONN: ------------------------------------------------------------------
I (5059) LAB_WIFI_CONN:   Target SSID: "NON_EXISTENT_SSID_9999"
I (5069) LAB_WIFI_CONN:   Target Password: "12345678"
I (5069) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (5079) wifi:state: run -> init (0x0)
I (5089) wifi:pm stop, total sleep time: 2614531 us / 3159340 us
I (5089) wifi:<ba-del>idx:0, tid:0
I (5089) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
W (5099) LAB_WIFI_CONN: =======================================================
W (5099) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (5109) LAB_WIFI_CONN:   -> Target SSID          : Thanutorn
W (5119) LAB_WIFI_CONN:   -> Reason Code (Decimal): 8
W (5119) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0x08
W (5129) LAB_WIFI_CONN:   -> Reason Description   : OTHER_DISCONNECT_REASON
W (5129) LAB_WIFI_CONN: =======================================================
I (5139) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (5149) wifi:flush txq
I (5149) wifi:stop sw txq
I (5149) wifi:lmac stop hw txq
I (5149) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (5199) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (5199) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (5209) wifi:mode : sta (14:08:08:a4:b6:60)
I (5209) wifi:enable tsf
I (5209) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (5219) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (5219) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (5229) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (5239) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (5239) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (7249) LAB_WIFI_CONN: 
I (7249) LAB_WIFI_CONN: ------------------------------------------------------------------
I (7249) LAB_WIFI_CONN: >>> Experiment 5.2.3: Connection Test - Wrong Password (Auth/Handshake Fail)
I (7249) LAB_WIFI_CONN: ------------------------------------------------------------------
I (7259) LAB_WIFI_CONN:   Target SSID: "Thanutorn"
I (7269) LAB_WIFI_CONN:   Target Password: "WRONG_PASS_9999"
I (7269) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (7279) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (7279) wifi:flush txq
I (7279) wifi:stop sw txq
I (7289) wifi:lmac stop hw txq
I (7289) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (7379) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (7379) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (7389) wifi:mode : sta (14:08:08:a4:b6:60)
I (7389) wifi:enable tsf
I (7389) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (7399) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (7399) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (7389) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (7669) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
I (7679) wifi:state: init -> auth (0xb0)
I (7679) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (7679) wifi:state: auth -> assoc (0x0)
I (7699) wifi:state: assoc -> run (0x10)
I (10719) wifi:state: run -> init (0xf00)
I (10729) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0

W (10729) LAB_WIFI_CONN: =======================================================
W (10729) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (10739) LAB_WIFI_CONN:   -> Target SSID          : Thanutorn
W (10749) LAB_WIFI_CONN:   -> Reason Code (Decimal): 15
W (10749) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0x0F
W (10759) LAB_WIFI_CONN:   -> Reason Description   : WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT (204)
W (10759) LAB_WIFI_CONN: =======================================================
W (10769) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (10779) LAB_WIFI_CONN: ==================================================================
I (10789) LAB_WIFI_CONN:   [Phase 2/3/4/5 Completed: Wi-Fi Connection Lab Finished]
I (10789) LAB_WIFI_CONN: ==================================================================
I (10799) main_task: Returned from app_main()
```

# 09-Labsheet-05-3-Wi-Fi-Auth-Assoc-Phase
##### 6. ตารางบันทึกผลการทดลอง (Experiment Results)

  

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

  

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองในระดับ Link Layer

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event ที่ได้รับ | ผลการผูกสัมพันธ์ Link Layer | ค่า Association ID (AID) ที่ได้ | Reason Code (ถ้ามี) |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.3.1** | ร้องขอ Auth & Assoc กับ AP มีอยู่จริง | `WIFI_EVENT_STA_CONNECTED` | **PASSED (สำเร็จ)** | 1 | - |
| **5.3.2** | ร้องขอ Auth & Assoc กับ AP ไม่มีอยู่จริง | `WIFI_EVENT_STA_DISCONNECTED` | **FAILED** | - | 201 (`WIFI_REASON_NO_AP_FOUND`) |

### 6.2 บันทึกข้อมูล Link Layer จาก Event `WIFI_EVENT_STA_CONNECTED` (ข้อ 5.3.1)

| พารามิเตอร์ Link Layer   | ค่าที่อ่านได้จริงจาก Forensic Log |
| :----------------------- | :-------------------------------- |
| **SSID**                 | Thanutorn                         |
| **BSSID (MAC Address)**  | D6:65:F4:32:83:9C                 |
| **Channel**              | 6                                 |
| **Auth Mode Enum**       | 3 (WPA2-PSK)                      |
| **Association ID (AID)** | 1                                 |

---

  

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

  

- **Association ID (AID) คืออะไร มีบทบาทอย่างไรใน Phase 3 และส่งคืนมาในโครงสร้างข้อมูลตัวแปรใด?**
    
    - **ความหมายและบทบาท:** AID คือหมายเลขประจำตัวเฉพาะที่ Access Point (AP) มอบให้กับสถานีลูกข่าย (STA) แต่ละตัวที่เข้ามาเชื่อมต่อสำเร็จในระดับ Link Layer เพื่อใช้ระบุตัวตนและบริหารจัดการช่องสัญญาณในการรับ-ส่งข้อมูลระหว่างกัน
        
    - **โครงสร้างข้อมูล:** ส่งคืนมาผ่านโครงสร้างข้อมูลเหตุการณ์ `wifi_event_sta_connected_t` (ในสมาชิกตัวแปร `aid`)
        
- **เหตุใดการเชื่อมต่อ Wi-Fi ความปลอดภัยแบบ WPA2-PSK จึงสามารถผ่าน Phase 2 (Authentication) และ Phase 3 (Association) จนเกิด Event `WIFI_EVENT_STA_CONNECTED` ได้สำเร็จ แม้ผู้ใช้จะป้อนรหัสผ่าน (Password) ผิด?**
    
    - เพราะในเฟส Authentication และ Phase 3 (Association) ของมาตรฐาน 802.11 จะทำหน้าที่ตรวจสอบเพียงสถานะการเชื่อมต่อทางวิทยุและสิทธิ์เบื้องต้นเท่านั้น ตัวรหัสผ่าน (Pre-Shared Key) จะยังไม่ถูกตรวจสอบในทันที แต่จะถูกนำไปตรวจสอบในขั้นตอนถัดไป (เช่น 4-Way Handshake) หลังจากที่เลเยอร์ Link-Layer เชื่อมต่อสำเร็จแล้ว
        
- **หาก Router มีการตั้งค่า MAC Address Filtering (อนุญาตเฉพาะ MAC ที่ลงทะเบียน) ESP32 จะล้มเหลวในเฟสใด และจะส่ง Disconnect Reason Code ใดออกมา?**
    
    - **เฟสที่ล้มเหลว:** จะล้มเหลวใน **Phase 3 (Association Phase)** หรือหลังส่งคำขอเชื่อมต่อ
        
    - **Reason Code:** Router จะปฏิเสธการเชื่อมต่อและส่ง Reason Code เช่น `23` (`WIFI_REASON_IEEE_802_1X_AUTH_FAILED`) หรือ Reason Code ที่เกี่ยวข้องกับการถูกปฏิเสธสิทธิ์การเชื่อมต่อกลับมา
        
- **สรุปความแตกต่างสำคัญระหว่างจุดสิ้นสุดของ Phase 3 (Link-Layer Connected) กับจุดสิ้นสุดของ Phase 5 (IP Address Assigned)**
    
    - **Phase 3 (Link-Layer Connected):** สิ้นสุดเมื่ออุปกรณ์จับมือเชื่อมต่อคลื่นวิทยุและเลเยอร์ลิงก์สำเร็จ (ได้ Event `WIFI_EVENT_STA_CONNECTED` และค่า AID) แต่อุปกรณ์ยังไม่มีตัวตนหรือ IP บนเครือข่ายวงแลน
        
    - **Phase 5 (IP Address Assigned):** สิ้นสุดเมื่อผ่านกระบวนการ DHCP จนกระทั่งได้รับหมายเลข IP Address (ได้ Event `IP_EVENT_STA_GOT_IP`) พร้อมใช้งานรับส่งข้อมูลในระดับ Network Layer อย่างสมบูรณ์
# Log
```
I (29) boot: ESP-IDF v5.5.1 2nd stage bootloader
I (29) boot: compile time Aug  4 2026 14:45:46
I (29) boot: Multicore bootloader
I (31) boot: chip revision: v3.1
I (33) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode        : DIO
I (41) boot.esp32: SPI Flash Size : 2MB
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label           Usage           Type ST Offset   Length
I (58) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory           factory app      00 00 00010000 00100000
I (77) boot: End of partition table
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=19e48h (106056) map
I (124) esp_image: segment 1: paddr=00029e70 vaddr=3ffb0000 size=03eech ( 16108) load
I (130) esp_image: segment 2: paddr=0002dd64 vaddr=40080000 size=022b4h (  8884) load
I (134) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=860f4h (549108) map
I (323) esp_image: segment 4: paddr=000b611c vaddr=400822b4 size=15b58h ( 88920) load
I (358) esp_image: segment 5: paddr=000cbc7c vaddr=50000000 size=00020h (    32) load
I (370) boot: Loaded app from partition at offset 0x10000
I (370) boot: Disabling RNG early entropy source...
I (381) cpu_start: Multicore app
I (389) cpu_start: Pro cpu start user code
I (389) cpu_start: cpu freq: 160000000 Hz
I (389) app_init: Application information:
I (389) app_init: Project name:     wifi_auth_assoc_phase
I (394) app_init: App version:      37de524-dirty
I (399) app_init: Compile time:     Aug  4 2026 14:44:17
I (404) app_init: ELF file SHA256:  09170e6c7...
I (408) app_init: ESP-IDF:          v5.5.1
I (412) efuse_init: Min chip rev:     v0.0
I (416) efuse_init: Max chip rev:     v3.99 
I (420) efuse_init: Chip rev:         v3.1
I (424) heap_init: Initializing. RAM available for dynamic allocation:
I (430) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (435) heap_init: At 3FFB7FD0 len 00028030 (160 KiB): DRAM
I (440) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (445) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (451) heap_init: At 40097E0C len 000081F4 (32 KiB): IRAM
W (458) spi_flash: Detected boya flash chip but using generic driver. For optimal functionality, enable `SPI_FLASH_SUPPORT_BOYA_CHIP` in menuconfig
I (469) spi_flash: detected chip: generic
I (473) spi_flash: flash io: dio
W (476) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (489) main_task: Started on CPU0
I (499) main_task: Calling app_main()
I (499) LAB_AUTH_ASSOC: [FORENSIC]: Call nvs_flash_init()
I (519) LAB_AUTH_ASSOC: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (519) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_netif_init()
I (519) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_event_loop_create_default()
I (529) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (529) LAB_AUTH_ASSOC: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbd940
I (539) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_init(&cfg)
I (559) wifi:wifi driver task: 3ffc002c, prio:23, stack:6656, core=0
I (569) wifi:wifi firmware version: 14da9b7
I (569) wifi:wifi certification version: v7.0
I (569) wifi:config NVS flash: enabled
I (569) wifi:config nano formatting: disabled
I (579) wifi:Init data frame dynamic rx buffer num: 32
I (579) wifi:Init static rx mgmt buffer num: 5
I (579) wifi:Init management short buffer num: 32
I (589) wifi:Init dynamic tx buffer num: 32
I (589) wifi:Init static rx buffer size: 1600
I (599) wifi:Init static rx buffer num: 10
I (599) wifi:Init dynamic rx buffer num: 32
I (609) wifi_init: rx ba win: 6
I (609) wifi_init: accept mbox: 6
I (609) wifi_init: tcpip mbox: 32
I (609) wifi_init: udp mbox: 6
I (619) wifi_init: tcp mbox: 6
I (619) wifi_init: tcp tx win: 5760
I (619) wifi_init: tcp rx win: 5760
I (629) wifi_init: tcp mss: 1440
I (629) wifi_init: WiFi IRAM OP enabled
I (629) wifi_init: WiFi RX IRAM OP enabled
I (639) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (639) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (649) LAB_AUTH_ASSOC: ==================================================================
I (659) LAB_AUTH_ASSOC:    Lab 5.3: Wi-Fi Authentication & Association Phase (ESP-IDF Forensic)
I (669) LAB_AUTH_ASSOC: ==================================================================
I (669) LAB_AUTH_ASSOC: 

I (679) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (679) LAB_AUTH_ASSOC: >>> Experiment 5.3.1: Link-Layer Auth & Assoc Phase Test
I (689) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (699) LAB_AUTH_ASSOC:    Target SSID    : "Thanutorn"
I (699) LAB_AUTH_ASSOC:    Target Password: "noeynoey"
I (709) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_stop()
I (709) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
W (719) wifi:Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2
I (799) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (799) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_start()
I (809) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (889) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(0)
I (909) wifi:mode : sta (14:08:08:a4:b6:60)
I (909) wifi:enable tsf
I (909) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (919) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (919) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (929) LAB_AUTH_ASSOC: [FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...
I (929) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (939) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (1829) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
I (1839) wifi:state: init -> auth (0xb0)
I (1839) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (1859) wifi:state: auth -> assoc (0x0)
I (1869) wifi:state: assoc -> run (0x10)
I (1909) wifi:connected with Thanutorn, aid = 1, channel 6, BW20, bssid = d6:65:f4:32:83:9c
I (1909) wifi:security: WPA2-PSK, phy: bgn, rssi: -22
I (1929) wifi:pm start, type: 1
I (1929) LAB_AUTH_ASSOC: =======================================================
I (1929) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (1939) LAB_AUTH_ASSOC:    -> Connected to SSID : Thanutorn
I (1949) LAB_AUTH_ASSOC:    -> BSSID             : D6:65:F4:32:83:9C
I (1949) LAB_AUTH_ASSOC:    -> Channel           : 6
I (1959) LAB_AUTH_ASSOC:    -> Auth Mode         : 3
I (1959) LAB_AUTH_ASSOC:    -> Association ID    : 1
I (1959) LAB_AUTH_ASSOC: =======================================================
I (1969) LAB_AUTH_ASSOC: [RESULT]: TEST PASSED - Link-Layer Auth & Assoc Successful!
I (3999) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (3999) LAB_AUTH_ASSOC: >>> Experiment 5.3.2: Link-Layer Test - Non-Existent AP
I (3999) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (4009) LAB_AUTH_ASSOC:    Target SSID    : "NON_EXISTENT_AP_9999"
I (4019) LAB_AUTH_ASSOC:    Target Password: "12345678"
I (4019) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_stop()
I (4029) wifi:state: run -> init (0x0)
I (4039) wifi:pm stop, total sleep time: 1814531 us / 2159340 us
I (4039) wifi:<ba-del>idx:0, tid:0
I (4049) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
W (4059) LAB_AUTH_ASSOC: =======================================================
W (4059) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (4069) LAB_AUTH_ASSOC:    -> Target SSID       : Thanutorn
W (4069) LAB_AUTH_ASSOC:    -> Reason Code (Decimal): 8
W (4079) LAB_AUTH_ASSOC:    -> Reason Code (Hex)    : 0x08
W (4079) LAB_AUTH_ASSOC:    -> Reason Diagnosis     : OTHER_DISCONNECT_REASON
W (4089) LAB_AUTH_ASSOC: =======================================================
I (4099) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
W (4109) wifi:Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2
I (4159) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (4159) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_start()
I (4169) wifi:mode : sta (14:08:08:a4:b6:60)
I (4169) wifi:enable tsf
I (4169) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (4179) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (4179) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (4189) LAB_AUTH_ASSOC: [FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...
I (4199) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (4199) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (6629) LAB_AUTH_ASSOC: =======================================================
W (6629) LAB_AUTH_ASSOC: =======================================================
W (6629) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (6639) LAB_AUTH_ASSOC:    -> Target SSID       : NON_EXISTENT_AP_9999
W (6639) LAB_AUTH_ASSOC:    -> Reason Code (Decimal): 201
W (6649) LAB_AUTH_ASSOC:    -> Reason Code (Hex)    : 0xC9
W (6649) LAB_AUTH_ASSOC:    -> Reason Diagnosis     : WIFI_REASON_NO_AP_FOUND (201) [Phase 1: SSID Not Found]
W (6659) LAB_AUTH_ASSOC: =======================================================
W (6659) LAB_AUTH_ASSOC: [RESULT]: TEST FAILED - Disconnected event captured in Link-Layer.
I (6669) LAB_AUTH_ASSOC: ==================================================================
I (6679) LAB_AUTH_ASSOC:    [Phase 2 & Phase 3 Completed: Link-Layer Auth & Assoc Finished]
I (6689) LAB_AUTH_ASSOC: ==================================================================
I (6689) main_task: Returned from app_main()
```

# 10-Labsheet-05-4-Wi-Fi-Handshake-IP-Phase
### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองใน Handshake & IP Phase

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event `WIFI_EVENT_STA_CONNECTED` (เกิด/ไม่เกิด) | Event `IP_EVENT_STA_GOT_IP` (เกิด/ไม่เกิด) | ผลการทดลอง | Disconnect Reason Code (ถ้ามี) |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.4.1** | Password ถูกต้อง | เกิดขึ้น | เกิดขึ้น | **PASSED (สำเร็จ)** | - |
| **5.4.2** | Password ผิด | เกิดขึ้น | ไม่เกิด | **FAILED** | 15 (`WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT`) |

### 6.2 บันทึกข้อมูล IP Network จาก Event `IP_EVENT_STA_GOT_IP` (ข้อ 5.4.1)

| พารามิเตอร์ Network Layer | ค่าที่จัดสรรได้จริงจาก DHCP Server |
| :------------------------ | :--------------------------------- |
| **IP Address**            | 192.168.137.105                    |
| **Subnet Mask**           | 255.255.255.0                      |
| **Default Gateway**       | 192.168.137.1                      |

### 7. คำถามท้ายการทดลอง (Post-Lab Questions)

- **เหตุใดกระบวนการ 4-Way Handshake จึงพิสูจน์ทราบรหัสผ่าน Wi-Fi ได้โดยไม่ต้องส่งรหัสผ่าน (Passphrase) ลอยไปในอากาศเลยแม้แต่แพ็กเกจเดียว?**
    
    - เพราะในกระบวนการ 4-Way Handshake จะใช้วิธีการพิสูจน์ตัวตนแบบ **Challenge-Response** ผ่านฟังก์ชันทางคณิตศาสตร์ (เช่น PBKDF2 ร่วมกับ Nonce แบบสุ่มของทั้งสองฝั่ง) โดยตัวอุปกรณ์และ Access Point จะนำรหัสผ่านที่แต่ละฝ่ายเก็บไว้มาคำนวณเพื่อตรวจสอบความถูกต้องร่วมกัน หากผลลัพธ์การเข้ารหัสตรงกัน แสดงว่ารหัสผ่านถูกต้องโดยไม่ต้องส่งค่า Plaintext ของรหัสผ่านผ่านสื่อไร้สายเลย
        
- **อธิบายบทบาทและที่มาของคีย์ PMK (Pairwise Master Key) และ PTK (Pairwise Transient Key)** ว่ามีความสัมพันธ์กันอย่างไรในการเข้ารหัสเฟรมข้อมูล?
    
    - **PMK (Pairwise Master Key):** ได้จากการนำ SSID และ Passphrase ไปผ่านฟังก์ชันแฮช (PBKDF2) ทำหน้าที่เป็นคีย์ตั้งต้นหลัก
        
    - **PTK (Pairwise Transient Key):** เป็นคีย์ชั่วคราวที่สร้างขึ้นใหม่ในทุกเซสชันการเชื่อมต่อ เกิดจากการนำ PMK ไปผสมร่วมกับข้อมูลสุ่ม (ANonce, SNonce) และ MAC Address ของทั้งสองฝั่งผ่านกระบวนการ 4-Way Handshake เพื่อใช้เป็นคีย์หลักในการเข้ารหัสและถอดรหัสข้อมูลรับ-ส่ง (Unicast Traffic) ระหว่างอุปกรณ์กับ Access Point
        
- **เหตุใดเมื่อเราพิมพ์ Password ผิด (ข้อ 5.4.2) ESP32 จึงยังคงได้รับ Event `WIFI_EVENT_STA_CONNECTED` ก่อนที่จะเกิด Event `WIFI_EVENT_STA_DISCONNECTED` ตามมาในภายหลัง?**
    
    - เพราะขั้นตอนการเชื่อมต่อในเลเยอร์ลิงก์ (Link-Layer Association) ได้เสร็จสิ้นลงและแจ้งสถานะ `WIFI_EVENT_STA_CONNECTED` ไปก่อน ตั้งแต่ตอนที่จับมือเชื่อมต่อคลื่นวิทยุสำเร็จ โดยที่ระบบยังไม่ได้ตรวจสอบความถูกต้องของรหัสผ่าน ต่อมาเมื่อเข้าสู่กระบวนการ **4-Way Handshake** แล้วตรวจสอบพบว่ารหัสผ่านไม่ตรงกัน Access Point จึงสั่งตัดการเชื่อมต่อและส่ง Disconnect Event พร้อม Reason Code กลับมาทีหลัง
        
- **หากเครือข่าย Wi-Fi ไม่มี DHCP Server (ไม่มีการแจก IP อัตโนมัติ) ผลการทดลองในข้อ 5.4.1 จะหยุดอยู่ที่ขั้นตอนใด และจะไม่เกิด Event ใดขึ้น?**
    
    - **จุดที่หยุด:** จะหยุดอยู่หลังจากผ่านขั้นตอน 4-Way Handshake และเชื่อมต่อระดับ Link Layer สำเร็จ (เสร็จสิ้นกระบวนการยืนยันตัวตนและสร้างคีย์เรียบร้อย แต่ค้างอยู่ในขั้นตอนการรอรับหมายเลข IP)
        
    - **Event ที่จะไม่เกิดขึ้น:** จะไม่เกิด Event **`IP_EVENT_STA_GOT_IP`** เนื่องจากไม่มีเซิร์ฟเวอร์คอยแจกจ่าย IP Address ให้กับอุปกรณ์


# Log
```
I (29) boot: ESP-IDF v5.5.1 2nd stage bootloader
I (29) boot: compile time Aug  4 2026 15:53:32
I (29) boot: Multicore bootloader
I (31) boot: chip revision: v3.1
I (33) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode        : DIO
I (41) boot.esp32: SPI Flash Size : 2MB
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label           Usage           Type ST Offset   Length
I (58) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory           factory app      00 00 00010000 00100000
I (77) boot: End of partition table
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=19ee8h (106216) map
I (124) esp_image: segment 1: paddr=00029f10 vaddr=3ffb0000 size=03eech ( 16108) load
I (130) esp_image: segment 2: paddr=0002de04 vaddr=40080000 size=02214h (  8724) load
I (134) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=861f0h (549360) map
I (323) esp_image: segment 4: paddr=000b6218 vaddr=40082214 size=15bf8h ( 89080) load
I (358) esp_image: segment 5: paddr=000cbe18 vaddr=50000000 size=00020h (    32) load
I (370) boot: Loaded app from partition at offset 0x10000
I (370) boot: Disabling RNG early entropy source...
I (381) cpu_start: Multicore app
I (389) cpu_start: Pro cpu start user code
I (389) cpu_start: cpu freq: 160000000 Hz
I (389) app_init: Application information:
I (389) app_init: Project name:     wifi_handshake_ip_phase
I (395) app_init: App version:      37de524-dirty
I (399) app_init: Compile time:     Aug  4 2026 15:52:35
I (404) app_init: ELF file SHA256:  29ace11b9...
I (408) app_init: ESP-IDF:          v5.5.1
I (412) efuse_init: Min chip rev:     v0.0
I (416) efuse_init: Max chip rev:     v3.99 
I (420) efuse_init: Chip rev:         v3.1
I (424) heap_init: Initializing. RAM available for dynamic allocation:
I (430) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (435) heap_init: At 3FFB7FD0 len 00028030 (160 KiB): DRAM
I (440) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (446) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (451) heap_init: At 40097E0C len 000081F4 (32 KiB): IRAM
W (458) spi_flash: Detected boya flash chip but using generic driver. For optimal functionality, enable `SPI_FLASH_SUPPORT_BOYA_CHIP` in menuconfig
I (470) spi_flash: detected chip: generic
I (473) spi_flash: flash io: dio
W (476) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (489) main_task: Started on CPU0
I (499) main_task: Calling app_main()
I (499) LAB_HANDSHAKE_IP: [FORENSIC]: Call nvs_flash_init()
I (519) LAB_HANDSHAKE_IP: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (519) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_netif_init()
I (519) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_loop_create_default()
I (529) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (529) LAB_HANDSHAKE_IP: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbd940
I (539) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_init(&cfg)
I (559) wifi:wifi driver task: 3ffc002c, prio:23, stack:6656, core=0
I (569) wifi:wifi firmware version: 14da9b7
I (569) wifi:wifi certification version: v7.0
I (569) wifi:config NVS flash: enabled
I (569) wifi:config nano formatting: disabled
I (579) wifi:Init data frame dynamic rx buffer num: 32
I (579) wifi:Init static rx mgmt buffer num: 5
I (579) wifi:Init management short buffer num: 32
I (589) wifi:Init dynamic tx buffer num: 32
I (589) wifi:Init static rx buffer size: 1600
I (599) wifi:Init static rx buffer num: 10
I (599) wifi:Init dynamic rx buffer num: 32
I (609) wifi_init: rx ba win: 6
I (609) wifi_init: accept mbox: 6
I (609) wifi_init: tcpip mbox: 32
I (609) wifi_init: udp mbox: 6
I (619) wifi_init: tcp mbox: 6
I (619) wifi_init: tcp tx win: 5760
I (619) wifi_init: tcp rx win: 5760
I (629) wifi_init: tcp mss: 1440
I (629) WiFi IRAM OP enabled
I (629) WiFi RX IRAM OP enabled
I (639) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (639) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_handler_instance_register(IP_EVENT)
I (649) LAB_HANDSHAKE_IP: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (659) LAB_HANDSHAKE_IP: ==================================================================
I (669) LAB_HANDSHAKE_IP:    Lab 5.4: 4-Way Handshake & IP Assignment Phase (ESP-IDF Forensic)
I (669) LAB_HANDSHAKE_IP: ==================================================================

I (689) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (689) LAB_HANDSHAKE_IP: >>> Experiment 5.4.1: Handshake & IP Test - Correct Password
I (699) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (709) LAB_HANDSHAKE_IP:    Target SSID    : "S24 Ultra Koson"
I (709) LAB_HANDSHAKE_IP:    Target Password: "correct_password"
I (719) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_stop()
I (729) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (799) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_start()
I (829) wifi:mode : sta (14:08:08:a4:b6:60)
I (849) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_connect()
I (1909) wifi:connected with S24 Ultra Koson, aid = 1, channel 6, BW20, bssid = d6:65:f4:32:83:9c
I (1929) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (2450) wifi:pm start, type: 1
I (2460) esp_netif_handlers: sta ip: 192.168.137.105, mask: 255.255.255.0, gw: 192.168.137.1
I (2460) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!
I (2470) LAB_HANDSHAKE_IP:    -> IP Address : 192.168.137.105
I (2470) LAB_HANDSHAKE_IP:    -> Subnet Mask: 255.255.255.0
I (2480) LAB_HANDSHAKE_IP:    -> Gateway    : 192.168.137.1
I (2490) LAB_HANDSHAKE_IP: [RESULT]: TEST PASSED - Handshake & IP Assignment Successful!

I (5309) ------------------------------------------------------------------
I (5309) >>> Experiment 5.4.2: Handshake Test - Incorrect Password
I (5319)    Target SSID    : "S24 Ultra Koson"
I (5329)    Target Password: "WRONG_PASSWORD_1234"
I (5339) [FORENSIC]: Call esp_wifi_connect()
I (6100) wifi:connected with S24 Ultra Koson, aid = 1, channel 6, BW20, bssid = d6:65:f4:32:83:9c
I (6120) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (7819) wifi:state: run -> auth (0x0)
I (7829) wifi:mac_term sta
I (7839) W (7849) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (7849)    -> Reason Code (Decimal): 15
W (7849)    -> Reason Diagnosis     : WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT (15)
W (7859) [RESULT]: TEST FAILED - 4-Way Handshake Failed (Incorrect Password).
I (7889) main_task: Returned from app_main()
```