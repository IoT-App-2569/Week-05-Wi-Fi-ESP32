## 07-Labsheet-05-1-Wi-Fi-Scan-Phase
## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบการสแกนทั้ง 4 กรณี

| ข้อการทดลอง | เงื่อนไขการสแกน             | สถานะ (Success/Error Code) | จำนวน AP ที่พบ (เครือข่าย) | เวลาที่ใช้ในการสแกน (ms) |
| :---------: | :-------------------------- | :------------------------: | :------------------------: | :----------------------: |
|  **5.1.1**  | สแกนทั่วไปทุก Channel       |   ESP_OK (0x0) / SUCCESS   |             15             |         2498 ms          |
|  **5.1.2**  | กำหนดสแกนเฉพาะ Channel 1    |   ESP_OK (0x0) / SUCCESS   |             7              |          200 ms          |
|  **5.1.3**  | กำหนดสแกน SSID ที่มีจริง    |   ESP_OK (0x0) / SUCCESS   |             5              |         2499 ms          |
|  **5.1.4**  | กำหนดสแกน SSID ที่ไม่มีจริง |   ESP_OK (0x0) / SUCCESS   |             0              |         2498 ms          |

### 6.2 ตารางรายละเอียด AP ที่พบจากการสแกนทั่วไป (ข้อ 5.1.1)

| ลำดับ | ชื่อเครือข่าย (SSID) | MAC Address (BSSID) | ความแรงสัญญาณ (RSSI: dBm) | ช่องความถี่ (Channel) | ประเภทการเข้ารหัส (Encryption Type) |
| :---: | :------------------- | :------------------ | :-----------------------: | :-------------------: | :---------------------------------- |
| 1 | KMITL-Legacy | 78:17:BE:C0:7D:A0 | -48 dBm | 1 | WPA2_ENTERPRISE |
| 2 | KMITL-IoT | 78:17:BE:C0:7D:A2 | -48 dBm | 1 | WPA2_PSK |
| 3 | KMITL-WIFI | 78:17:BE:C0:7D:A1 | -54 dBm | 1 | OPEN (No Password) |
| 4 | KMITL-Legacy | 78:17:BE:C0:72:60 | -79 dBm | 11 | WPA2_ENTERPRISE |
| 5 | KMITL-WIFI | 78:17:BE:C0:66:61 | -80 dBm | 11 | OPEN (No Password) |
| 6 | KMITL-IoT | 78:17:BE:C0:72:62 | -80 dBm | 11 | WPA2_PSK |
| 7 | KMITL-IoT | 78:17:BE:C0:66:62 | -81 dBm | 11 | WPA2_PSK |
| 8 | KMITL-WIFI | 78:17:BE:C0:66:21 | -82 dBm | 1 | OPEN (No Password) |
| 9 | KMITL-IoT | 78:17:BE:A9:94:E2 | -82 dBm | 6 | WPA2_PSK |
| 10 | KMITL-Legacy | 78:17:BE:C0:66:60 | -82 dBm | 11 | WPA2_ENTERPRISE |
| 11 | KMITL-WIFI | 78:17:BE:A9:94:E1 | -84 dBm | 6 | OPEN (No Password) |
| 12 | KMITL-Legacy | 78:17:BE:A9:94:E0 | -84 dBm | 6 | WPA2_ENTERPRISE |
| 13 | KMITL-WIFI | 78:17:BE:C0:72:61 | -84 dBm | 11 | OPEN (No Password) |
| 14 | KMITL-IoT | 78:17:BE:C0:66:22 | -91 dBm | 1 | WPA2_PSK |
| 15 | Olympus EP50 Room406 | 9C:53:22:7B:3C:9E | -93 dBm | 9 | WPA2_PSK |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. การกำหนดค่าในโครงสร้าง `wifi_scan_config_t` สำหรับสแกนเจาะจงเฉพาะช่องความถี่ (ข้อ 5.1.2) ช่วยลดเวลาในการสแกนเมื่อเทียบกับการสแกนทุกช่องความถี่ (ข้อ 5.1.1) อย่างไร และมีข้อจำกัดอย่างไร?
	* **การลดเวลา:** ช่วยลดเวลาสแกนลงได้อย่างมหาศาล (จากผลการทดลองลดจากประมาณ 2,498 ms เหลือเพียง 200 ms) เนื่องจากไมโครคอนโทรลเลอร์ไม่จำเป็นต้องกระโดดสลับช่องสัญญาณและรอรับ Beacon Frame ให้ครบทุกแบนด์ความถี่ (ช่อง 1-13) แต่สามารถล็อกการดักฟังเฉพาะช่องเป้าหมายได้ทันที 
	* **ข้อจำกัด:** หาก Access Point ปลายทางเปิดใช้งานระบบสลับช่องสัญญาณอัตโนมัติ (Auto Channel) หรือเราไม่ทราบช่องสัญญาณที่แน่ชัดล่วงหน้า การระบุช่องเฉพาะเจาะจงจะทำให้ระบบหาเครือข่ายเป้าหมายไม่พบ
	
2. เมื่อสังเกตผล Forensic Log ในข้อ 5.1.4 (สแกนหา SSID ที่ไม่มีอยู่จริง) ฟังก์ชัน `esp_wifi_scan_start()`, `esp_wifi_scan_get_ap_num()` และ `esp_wifi_scan_get_ap_records()` ส่งคืนค่าอย่างไร?
	* `esp_wifi_scan_start()`: ส่งคืนค่า **ESP_OK (0x0)** ซึ่งหมายถึงระบบสามารถรับคำสั่งและดำเนินการกวาดสัญญาณจนจบกระบวนการได้อย่างสมบูรณ์ โดยไม่ถือว่าเป็น Error 
	* `esp_wifi_scan_get_ap_num()`: ส่งคืนค่า **ESP_OK (0x0)** และอัปเดตค่าตัวแปรจำนวนเครือข่ายที่พบเป็น `ap_count = 0` 
	* `esp_wifi_scan_get_ap_records()`: ในทางปฏิบัติฟังก์ชันนี้จะ **ไม่ถูกเรียกให้ทำงาน** เนื่องจากจำนวนเครือข่าย (`ap_count`) เป็นศูนย์แล้ว หรือหากโปรแกรมฝืนเรียกฟังก์ชัน ก็จะไม่มีการเขียนข้อมูลเรคคอร์ดใดๆ ลงในหน่วยความจำ
	
3. ค่าระดับความแรงสัญญาณ (RSSI) ที่แสดงเป็นตัวเลขติดลบ (เช่น -45 dBm กับ -80 dBm) ค่าใดแสดงถึงสัญญาณที่มีความแรงและความเสถียรมากกว่ากัน?
	* ค่า **-45 dBm** แสดงถึงสัญญาณที่มีความแรงและเสถียรมากกว่า เนื่องจากหน่วย dBm (Decibel-milliwatts) สำหรับภาครับ Wi-Fi จะมีค่าติดลบ ค่าที่เข้าใกล้ 0 มากกว่าจะหมายถึงระดับพลังงานของคลื่นวิทยุที่รับได้สูงกว่า ในขณะที่ -80 dBm ถือว่าเป็นสัญญาณที่อ่อนและเสี่ยงต่อการหลุดเชื่อมต่อหรือข้อมูลสูญหาย

4. เหตุใดการดึงค่า `authmode` (`wifi_auth_mode_t`) จากโครงสร้าง `wifi_ap_record_t` จึงมีความสำคัญต่อการเตรียมการในเฟสถัดไป (Authentication & Association Phase)?
	* การดึงค่า `authmode` (เช่น OPEN, WPA2_PSK หรือ WPA2_ENTERPRISE) มีความสำคัญอย่างยิ่ง เพราะไมโครคอนโทรลเลอร์จำเป็นต้องทราบโปรโตคอลความปลอดภัยที่ Access Point ร้องขอ เพื่อนำไปปรับโหมดการทำงานและเตรียมข้อมูลให้สอดคล้องกัน (เช่น เตรียมรหัสผ่าน หรือเตรียมใบรับรอง EAP) หากเตรียมแพ็กเกจยืนยันตัวตนผิดประเภท Access Point จะปฏิเสธการเชื่อมต่อ (Association Denied) ทันที


Log
```text
I (29) boot: ESP-IDF v5.5.1 2nd stage bootloader
I (29) boot: compile time Aug  4 2026 09:57:29
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
I (398) app_init: Compile time:     Aug  4 2026 09:57:01
I (403) app_init: ELF file SHA256:  68e41a675...
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
I (457) spi_flash: detected chip: generic
I (459) spi_flash: flash io: dio
W (462) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (475) main_task: Started on CPU0
I (485) main_task: Calling app_main()
I (485) LAB_WIFI_SCAN: [FORENSIC]: Call nvs_flash_init()
I (495) LAB_WIFI_SCAN: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (495) LAB_WIFI_SCAN: [FORENSIC]: Call esp_netif_init()
I (495) LAB_WIFI_SCAN: [FORENSIC]: esp_netif_init() returned ESP_OK (0x0)
I (505) LAB_WIFI_SCAN: [FORENSIC]: Call esp_event_loop_create_default()
I (505) LAB_WIFI_SCAN: [FORENSIC]: esp_event_loop_create_default() returned ESP_OK (0x0)
I (515) LAB_WIFI_SCAN: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (525) LAB_WIFI_SCAN: [FORENSIC]: esp_netif_create_default_wifi_sta() returned pointer 0x3ffbd700
I (535) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_init(&cfg)
I (545) wifi:wifi driver task: 3ffbfdec, prio:23, stack:6656, core=0
I (545) wifi:wifi firmware version: 14da9b7
I (545) wifi:wifi certification version: v7.0
I (555) wifi:config NVS flash: enabled
I (555) wifi:config nano formatting: disabled
I (555) wifi:Init data frame dynamic rx buffer num: 32
I (565) wifi:Init static rx mgmt buffer num: 5
I (565) wifi:Init management short buffer num: 32
I (575) wifi:Init dynamic tx buffer num: 32
I (575) wifi:Init static rx buffer size: 1600
I (575) wifi:Init static rx buffer num: 10
I (585) wifi:Init dynamic rx buffer num: 32
I (585) wifi_init: rx ba win: 6
I (585) wifi_init: accept mbox: 6
I (595) wifi_init: tcpip mbox: 32
I (595) wifi_init: udp mbox: 6
I (595) wifi_init: tcp mbox: 6
I (605) wifi_init: tcp tx win: 5760
I (605) wifi_init: tcp rx win: 5760
I (605) wifi_init: tcp mss: 1440
I (615) wifi_init: WiFi IRAM OP enabled
I (615) wifi_init: WiFi RX IRAM OP enabled
I (615) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_init() returned ESP_OK (0x0)
I (625) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (635) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_set_mode() returned ESP_OK (0x0)
I (635) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_start()
I (645) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (725) wifi:mode : sta (14:33:5c:0e:94:44)
I (725) wifi:enable tsf
I (725) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (735) LAB_WIFI_SCAN: ==================================================================
I (735) LAB_WIFI_SCAN:   Lab 5.1: Wi-Fi Connection and Scanning Phase (ESP-IDF Forensic)
I (745) LAB_WIFI_SCAN: ==================================================================
I (755) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (755) LAB_WIFI_SCAN: >>> Experiment 5.1.1: General AP Scan (All Channels)
I (765) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (775) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (3285) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2498 ms]
I (3285) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (3285) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=15
I (3295) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (3295) LAB_WIFI_SCAN: [AP COUNT]: 15 network(s) found
I (3305) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (3315) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=15

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | KMITL-Legacy             | 78:17:BE:C0:7D:A0 | -48  dBm | 1    | WPA2_ENTERPRISE     
2    | KMITL-IoT                | 78:17:BE:C0:7D:A2 | -48  dBm | 1    | WPA2_PSK            
3    | KMITL-WIFI               | 78:17:BE:C0:7D:A1 | -54  dBm | 1    | OPEN (No Password)  
4    | KMITL-Legacy             | 78:17:BE:C0:72:60 | -79  dBm | 11   | WPA2_ENTERPRISE     
5    | KMITL-WIFI               | 78:17:BE:C0:66:61 | -80  dBm | 11   | OPEN (No Password)  
6    | KMITL-IoT                | 78:17:BE:C0:72:62 | -80  dBm | 11   | WPA2_PSK            
7    | KMITL-IoT                | 78:17:BE:C0:66:62 | -81  dBm | 11   | WPA2_PSK            
8    | KMITL-WIFI               | 78:17:BE:C0:66:21 | -82  dBm | 1    | OPEN (No Password)  
9    | KMITL-IoT                | 78:17:BE:A9:94:E2 | -82  dBm | 6    | WPA2_PSK            
10   | KMITL-Legacy             | 78:17:BE:C0:66:60 | -82  dBm | 11   | WPA2_ENTERPRISE     
11   | KMITL-WIFI               | 78:17:BE:A9:94:E1 | -84  dBm | 6    | OPEN (No Password)  
12   | KMITL-Legacy             | 78:17:BE:A9:94:E0 | -84  dBm | 6    | WPA2_ENTERPRISE     
13   | KMITL-WIFI               | 78:17:BE:C0:72:61 | -84  dBm | 11   | OPEN (No Password)  
14   | KMITL-IoT                | 78:17:BE:C0:66:22 | -91  dBm | 1    | WPA2_PSK            
15   | Olympus EP50 Room406     | 9C:53:22:7B:3C:9E | -93  dBm | 9    | WPA2_PSK            
--------------------------------------------------------------------------------------------------

I (4475) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (4475) LAB_WIFI_SCAN: >>> Experiment 5.1.2: Channel-Specific Scan (Channel 1)
I (4475) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (4485) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (4695) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 200 ms]
I (4695) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (4695) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=7
I (4705) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (4705) LAB_WIFI_SCAN: [AP COUNT]: 7 network(s) found
I (4715) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (4725) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=7

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | KMITL-Legacy             | 78:17:BE:C0:7D:A0 | -45  dBm | 1    | WPA2_ENTERPRISE     
2    | KMITL-IoT                | 78:17:BE:C0:7D:A2 | -45  dBm | 1    | WPA2_PSK            
3    | KMITL-WIFI               | 78:17:BE:C0:7D:A1 | -51  dBm | 1    | OPEN (No Password)  
4    | KMITL-WIFI               | 78:17:BE:C0:66:21 | -79  dBm | 1    | OPEN (No Password)  
5    | KMITL-Legacy             | 78:17:BE:C0:66:20 | -88  dBm | 1    | WPA2_ENTERPRISE     
6    | KMITL-Legacy             | 78:17:BE:C0:65:E0 | -89  dBm | 1    | WPA2_ENTERPRISE     
7    | KMITL-IoT                | 78:17:BE:C0:66:22 | -90  dBm | 1    | WPA2_PSK            
--------------------------------------------------------------------------------------------------

I (5825) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (5825) LAB_WIFI_SCAN: >>> Experiment 5.1.3: Targeted SSID Scan - Existing ("KMITL-Legacy")
I (5825) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (5835) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (8345) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2499 ms]
I (8345) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (8345) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=5
I (8355) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (8355) LAB_WIFI_SCAN: [AP COUNT]: 5 network(s) found
I (8365) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (8375) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=5

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | KMITL-Legacy             | 78:17:BE:C0:7D:A0 | -56  dBm | 1    | WPA2_ENTERPRISE     
2    | KMITL-Legacy             | 78:17:BE:A9:94:E0 | -76  dBm | 6    | WPA2_ENTERPRISE     
3    | KMITL-Legacy             | 78:17:BE:C0:72:60 | -76  dBm | 11   | WPA2_ENTERPRISE     
4    | KMITL-Legacy             | 78:17:BE:C0:66:60 | -79  dBm | 11   | WPA2_ENTERPRISE     
5    | KMITL-Legacy             | 78:17:BE:C0:66:20 | -89  dBm | 1    | WPA2_ENTERPRISE     
--------------------------------------------------------------------------------------------------

I (9455) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (9455) LAB_WIFI_SCAN: >>> Experiment 5.1.4: Targeted SSID Scan - Non-Existent ("NON_EXISTENT_AP_9999")
I (9455) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (9465) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (11975) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2498 ms]
I (11975) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (11975) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=0
I (11985) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (11985) LAB_WIFI_SCAN: [AP COUNT]: 0 network(s) found
W (11995) LAB_WIFI_SCAN: [NOTE]: No Access Point found matching the criteria.
I (11995) LAB_WIFI_SCAN: ==================================================================
I (12005) LAB_WIFI_SCAN:   [Phase 1 Completed: Wi-Fi Scan Finished]
I (12015) LAB_WIFI_SCAN:   Program stopped after scanning. Auth/Assoc Phase not started.
I (12025) LAB_WIFI_SCAN: ==================================================================
I (12025) main_task: Returned from app_main()
```

---

## 08-Labsheet-05-2-Wi-Fi-Connection-Phase
## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองทั้ง 3 สถานการณ์

| ข้อการทดลอง | สถานการณ์ทดสอบ                     |   Event สุดท้ายที่ได้รับ    | ผลลัพธ์ (Passed/Failed) | Reason Code (Decimal / Hex) | คำอธิบาย Reason Code                                                                  |
| :---------: | :--------------------------------- | :-------------------------: | :---------------------: | :-------------------------: | :------------------------------------------------------------------------------------ |
|  **5.2.1**  | SSID และ Password ถูกต้อง          |     IP_EVENT_STA_GOT_IP     |         Passed          |              -              | เชื่อมต่อสำเร็จและได้รับ IP Address จาก DHCP Server                                   |
|  **5.2.2**  | ระบุ SSID ผิด (ไม่มีในระบบ)        | WIFI_EVENT_STA_DISCONNECTED |         Failed          |         201 / 0xC9          | WIFI_REASON_NO_AP_FOUND (ไม่พบ Access Point ที่ตรงกับ SSID)                           |
|  **5.2.3**  | ระบุ SSID ถูกต้อง แต่ Password ผิด | WIFI_EVENT_STA_DISCONNECTED |         Failed          |          15 / 0x0F          | WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT (การยืนยันตัวตนล้มเหลวเนื่องจากรหัสผ่านไม่ถูกต้อง) |

### 6.2 บันทึกข้อมูลเครือข่ายจากการเชื่อมต่อสำเร็จ (ข้อ 5.2.1)

| พารามิเตอร์เครือข่าย    | ค่าที่ได้รับจริงจาก DHCP |
| :---------------------- | :----------------------- |
| **SSID**                | Pleum825               |
| **BSSID (MAC Address)** | D6:65:F4:32:83:9C        |
| **Channel**             | 6                        |
| **IP Address**          | 10.219.61.137            |
| **Subnet Mask**         | 255.255.255.0            |
| **Default Gateway**     | 10.219.61.159            |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการระบุ SSID ผิด (ข้อ 5.2.2) จึงส่งผลให้เกิด Disconnect Event ด้วย Reason Code `201` (`WIFI_REASON_NO_AP_FOUND`) ตั้งแต่เฟส Scan?
	* **ตอบ:** ตามมาตรฐาน 802.11 ก่อนที่อุปกรณ์จะเริ่มเชื่อมต่อ (Authentication/Association) ได้ จะต้องผ่านเฟสการสแกนหาเครือข่ายก่อน (Scan Phase) โดย ESP32 จะส่ง Probe Request ออกไปเพื่อหา SSID ที่ตรงกับที่ตั้งค่าไว้ หากระบุ SSID ผิด บอร์ดจะไม่ได้รับ Probe Response กลับมาจาก Access Point ใดเลยในอากาศ ระบบจึงทราบทันทีว่าไม่มีเครือข่ายเป้าหมายอยู่จริง และทำการตัดจบกระบวนการทำงานตั้งแต่ต้น (ส่งโค้ด 201) โดยไม่เสียเวลาเข้าสู่เฟสถัดไป

2. เหตุใดการพิมพ์ Password ผิด (ข้อ 5.2.3) จึงผ่านเฟส Auth และ Assoc มาได้ แต่มาล้มเหลวในเฟส 4-Way Handshake (Reason Code `15` หรือ `204`)?
	* **ตอบ:** ในระบบความปลอดภัยแบบ WPA2-PSK กระบวนการ 802.11 Authentication และ Association ในช่วงแรกเป็นเพียงการจับมือแบบเปิด (Open System) เพื่อสร้างช่องสัญญาณสื่อสารระดับวิทยุพื้นฐานเท่านั้น (ยังไม่มีการตรวจรหัสผ่าน) การตรวจสอบรหัสผ่าน (Pre-Shared Key) จะเกิดขึ้นในเฟส EAPOL 4-Way Handshake หลังจากจับมือทางกายภาพสำเร็จแล้ว เมื่อใส่รหัสผ่านผิด กระบวนการสร้างคีย์เข้ารหัส (PTK/GTK) จะล้มเหลวเนื่องจากข้อมูลไม่ตรงกัน ส่งผลให้เกิดอาการ Timeout (Reason Code 15 หรือ 204) และถูก Access Point เตะออกจากระบบในที่สุด

3. ลำดับการเกิด Event ระหว่าง **`WIFI_EVENT_STA_CONNECTED`** กับ **`IP_EVENT_STA_GOT_IP`** Event ใดเกิดขึ้นก่อนกัน และมีความหมายทางกายภาพของ Layer Network ต่างกันอย่างไร?
	* **ตอบ:** 
	* **เกิดก่อน:** `WIFI_EVENT_STA_CONNECTED` เกิดขึ้นก่อน หมายถึงการเชื่อมต่อสำเร็จในระดับ **Data Link Layer (Layer 2)** หรือ MAC Layer (อุปกรณ์วิทยุจับมือกับ Access Point สำเร็จแล้ว) 
	* **เกิดหลัง:** `IP_EVENT_STA_GOT_IP` เกิดขึ้นตามมา หมายถึงการเชื่อมต่อสำเร็จในระดับ **Network Layer (Layer 3)** (อุปกรณ์ผ่านกระบวนการ DHCP และได้รับหมายเลข IP Address เรียบร้อยแล้ว พร้อมส่งต่อแพ็กเก็ตข้อมูลออกสู่อินเทอร์เน็ต)

4. สมาชิกตัวแปร `reason` ในโครงสร้าง `wifi_event_sta_disconnected_t` มีประโยชน์อย่างไรต่อการออกแบบระบบค้นหาสาเหตุและกู้คืนการเชื่อมต่อ (Auto-Reconnection Mechanism) ในแอปพลิเคชัน IoT?
	* **ตอบ:** ตัวแปร `reason` ช่วยให้โปรแกรมเมอร์ทราบ "สาเหตุที่แท้จริง" ของการหลุดจากการเชื่อมต่อ เพื่อนำไปเขียนเงื่อนไข State Machine ให้ระบบฟื้นฟูตัวเอง (Auto-Reconnect) ได้อย่างชาญฉลาด เช่น: 
	* หากหลุดเพราะ `WIFI_REASON_NO_AP_FOUND` (เราเตอร์อาจดับ): สามารถสั่งให้บอร์ดหน่วงเวลา (Delay) ให้นานขึ้นก่อนพยายามต่อใหม่ เพื่อประหยัดพลังงาน 
	* หากหลุดเพราะ `WIFI_REASON_AUTH_FAIL` (รหัสผ่านผิด): การพยายามเชื่อมต่อซ้ำๆ จะไม่มีประโยชน์ ระบบสามารถหยุดการเชื่อมต่อและเปิดโหมด SmartConfig หรือ Access Point เพื่อให้ผู้ใช้งานกรอกรหัสผ่านใหม่ได้ทันที



Log
```text
I (29) boot: ESP-IDF v5.5.1 2nd stage bootloader
I (29) boot: compile time Aug  4 2026 11:11:26
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
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=19e38h (106040) map
I (124) esp_image: segment 1: paddr=00029e60 vaddr=3ffb0000 size=03eech ( 16108) load
I (130) esp_image: segment 2: paddr=0002dd54 vaddr=40080000 size=022c4h (  8900) load
I (134) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=861fch (549372) map
I (323) esp_image: segment 4: paddr=000b6224 vaddr=400822c4 size=15b48h ( 88904) load
I (358) esp_image: segment 5: paddr=000cbd74 vaddr=50000000 size=00020h (    32) load
I (370) boot: Loaded app from partition at offset 0x10000
I (370) boot: Disabling RNG early entropy source...
I (381) cpu_start: Multicore app
I (389) cpu_start: Pro cpu start user code
I (389) cpu_start: cpu freq: 160000000 Hz
I (389) app_init: Application information:
I (389) app_init: Project name:     wifi_connection_phase
I (394) app_init: App version:      37de524-dirty
I (399) app_init: Compile time:     Aug  4 2026 11:10:59
I (404) app_init: ELF file SHA256:  cc1ccca48...
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
I (458) spi_flash: detected chip: generic
I (460) spi_flash: flash io: dio
W (463) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (476) main_task: Started on CPU0
I (486) main_task: Calling app_main()
I (486) LAB_WIFI_CONN: [FORENSIC]: Call nvs_flash_init()
I (506) LAB_WIFI_CONN: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (506) LAB_WIFI_CONN: [FORENSIC]: Call esp_netif_init()
I (506) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_loop_create_default()
I (516) LAB_WIFI_CONN: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (516) LAB_WIFI_CONN: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbd8bc
I (526) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_init(&cfg)
I (546) wifi:wifi driver task: 3ffbffa8, prio:23, stack:6656, core=0
I (556) wifi:wifi firmware version: 14da9b7
I (556) wifi:wifi certification version: v7.0
I (556) wifi:config NVS flash: enabled
I (556) wifi:config nano formatting: disabled
I (556) wifi:Init data frame dynamic rx buffer num: 32
I (566) wifi:Init static rx mgmt buffer num: 5
I (566) wifi:Init management short buffer num: 32
I (576) wifi:Init dynamic tx buffer num: 32
I (576) wifi:Init static rx buffer size: 1600
I (586) wifi:Init static rx buffer num: 10
I (586) wifi:Init dynamic rx buffer num: 32
I (586) wifi_init: rx ba win: 6
I (596) wifi_init: accept mbox: 6
I (596) wifi_init: tcpip mbox: 32
I (596) wifi_init: udp mbox: 6
I (606) wifi_init: tcp mbox: 6
I (606) wifi_init: tcp tx win: 5760
I (606) wifi_init: tcp rx win: 5760
I (606) wifi_init: tcp mss: 1440
I (616) wifi_init: WiFi IRAM OP enabled
I (616) wifi_init: WiFi RX IRAM OP enabled
I (616) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (626) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_handler_instance_register(IP_EVENT)
I (636) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (646) LAB_WIFI_CONN: ==================================================================
I (646) LAB_WIFI_CONN:   Lab 5.2: Wi-Fi Connection & IP Assignment (ESP-IDF Forensic)
I (656) LAB_WIFI_CONN: ==================================================================
I (666) LAB_WIFI_CONN: 

I (666) LAB_WIFI_CONN: ------------------------------------------------------------------
I (676) LAB_WIFI_CONN: >>> Experiment 5.2.1: Connection Test - Correct Credentials
I (686) LAB_WIFI_CONN: ------------------------------------------------------------------
I (696) LAB_WIFI_CONN:   Target SSID: "Pleum825"
I (696) LAB_WIFI_CONN:   Target Password: "12345678"
I (696) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (706) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (716) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (716) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (726) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (806) wifi:mode : sta (14:33:5c:0e:94:44)
I (806) wifi:enable tsf
I (816) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (816) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (816) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (826) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (836) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (1706) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
I (1706) wifi:state: init -> auth (0xb0)
I (1716) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (1716) wifi:state: auth -> assoc (0x0)
I (1726) wifi:state: assoc -> run (0x10)
I (1766) wifi:connected with Pleum825, aid = 1, channel 6, BW20, bssid = d6:65:f4:32:83:9c
I (1766) wifi:security: WPA2-PSK, phy: bgn, rssi: -36
I (1776) wifi:pm start, type: 1

I (1776) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (1786) LAB_WIFI_CONN: =======================================================
I (1786) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (1796) LAB_WIFI_CONN:   -> Connected to SSID : Pleum825
I (1796) LAB_WIFI_CONN:   -> BSSID            : D6:65:F4:32:83:9C
I (1806) LAB_WIFI_CONN:   -> Channel          : 6
I (1806) LAB_WIFI_CONN:   -> Auth Mode        : 3
I (1816) LAB_WIFI_CONN: =======================================================
I (1786) wifi:<ba-add>idx:0 (ifx:0, d6:65:f4:32:83:9c), tid:0, ssn:0, winSize:64
I (1826) wifi:dp: 2, bi: 102400, li: 4, scale listen interval from 307200 us to 409600 us
I (1836) wifi:AP's beacon interval = 102400 us, DTIM period = 2
I (2876) esp_netif_handlers: sta ip: 10.219.61.137, mask: 255.255.255.0, gw: 10.219.61.159
I (2876) LAB_WIFI_CONN: =======================================================
I (2876) LAB_WIFI_CONN: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!
I (2886) LAB_WIFI_CONN:   -> IP Address : 10.219.61.137
I (2886) LAB_WIFI_CONN:   -> Netmask    : 255.255.255.0
I (2896) LAB_WIFI_CONN:   -> Gateway    : 10.219.61.159
I (2896) LAB_WIFI_CONN: =======================================================
I (2906) LAB_WIFI_CONN: [RESULT]: TEST PASSED - Connected to AP successfully!
I (4916) LAB_WIFI_CONN: 

I (4916) LAB_WIFI_CONN: ------------------------------------------------------------------
I (4916) LAB_WIFI_CONN: >>> Experiment 5.2.2: Connection Test - Wrong SSID (No AP Found)
I (4916) LAB_WIFI_CONN: ------------------------------------------------------------------
I (4926) LAB_WIFI_CONN:   Target SSID: "NON_EXISTENT_SSID_9999"
I (4936) LAB_WIFI_CONN:   Target Password: "12345678"
I (4936) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (4946) wifi:state: run -> init (0x0)
I (4956) wifi:pm stop, total sleep time: 2555761 us / 3172620 us

I (4956) wifi:<ba-del>idx:0, tid:0
I (4956) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
W (4966) LAB_WIFI_CONN: =======================================================
W (4966) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (4976) LAB_WIFI_CONN:   -> Target SSID          : Pleum825
W (4986) LAB_WIFI_CONN:   -> Reason Code (Decimal): 8
W (4986) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0x08
W (4996) LAB_WIFI_CONN:   -> Reason Description   : OTHER_DISCONNECT_REASON
W (4996) LAB_WIFI_CONN: =======================================================
I (5006) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (5016) wifi:flush txq
I (5016) wifi:stop sw txq
I (5016) wifi:lmac stop hw txq
I (5016) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (5056) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (5056) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (5056) wifi:mode : sta (14:33:5c:0e:94:44)
I (5056) wifi:enable tsf
I (5066) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (5066) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (5066) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (5086) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (5086) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (5096) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (7096) LAB_WIFI_CONN: 

I (7096) LAB_WIFI_CONN: ------------------------------------------------------------------
I (7096) LAB_WIFI_CONN: >>> Experiment 5.2.3: Connection Test - Wrong Password (Auth/Handshake Fail)
I (7096) LAB_WIFI_CONN: ------------------------------------------------------------------
I (7106) LAB_WIFI_CONN:   Target SSID: "Pleum825"
I (7116) LAB_WIFI_CONN:   Target Password: "WRONG_PASS_9999"
I (7116) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (7126) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (7126) wifi:flush txq
I (7126) wifi:stop sw txq
I (7136) wifi:lmac stop hw txq
I (7136) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (7186) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (7186) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (7196) wifi:mode : sta (14:33:5c:0e:94:44)
I (7196) wifi:enable tsf
I (7196) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (7206) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (7206) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (7196) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (7476) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
I (7476) wifi:state: init -> auth (0xb0)
I (7486) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (7486) wifi:state: auth -> assoc (0x0)
I (7496) wifi:state: assoc -> run (0x10)
I (10516) wifi:state: run -> init (0xf00)
I (10526) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
W (10526) LAB_WIFI_CONN: =======================================================
W (10526) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (10536) LAB_WIFI_CONN:   -> Target SSID          : Pleum825
W (10536) LAB_WIFI_CONN:   -> Reason Code (Decimal): 15
W (10546) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0x0F
W (10546) LAB_WIFI_CONN:   -> Reason Description   : WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT (204)
W (10556) LAB_WIFI_CONN: =======================================================
W (10566) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (10576) LAB_WIFI_CONN: ==================================================================
I (10576) LAB_WIFI_CONN:   [Phase 2/3/4/5 Completed: Wi-Fi Connection Lab Finished]
I (10586) LAB_WIFI_CONN: ==================================================================
I (10596) main_task: Returned from app_main()
```


---

## 09-Labsheet-05-3-Wi-Fi-Auth-Assoc-Phase

## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองในระดับ Link Layer

| ข้อการทดลอง | สถานการณ์ทดสอบ                           |       Event ที่ได้รับ       | ผลการผูกสัมพันธ์ Link Layer | ค่า Association ID (AID) ที่ได้ | Reason Code (ถ้ามี)           |
| :---------: | :--------------------------------------- | :-------------------------: | :-------------------------: | :-----------------------------: | :---------------------------- |
|  **5.3.1**  | ร้องขอ Auth & Assoc กับ AP มีอยู่จริง    |  WIFI_EVENT_STA_CONNECTED   |       สำเร็จ (Passed)       |                3                | -                             |
|  **5.3.2**  | ร้องขอ Auth & Assoc กับ AP ไม่มีอยู่จริง | WIFI_EVENT_STA_DISCONNECTED |      ล้มเหลว (Failed)       |                -                | 201 (WIFI_REASON_NO_AP_FOUND) |

### 6.2 บันทึกข้อมูล Link Layer จาก Event `WIFI_EVENT_STA_CONNECTED` (ข้อ 5.3.1)

| พารามิเตอร์ Link Layer   | ค่าที่อ่านได้จริงจาก Forensic Log |
| :----------------------- | :-------------------------------- |
| **SSID**                 | Pleum825                        |
| **BSSID (MAC Address)**  | D6:65:F4:32:83:9C                 |
| **Channel**              | 6                                 |
| **Auth Mode Enum**       | 3                                 |
| **Association ID (AID)** | 3                                 |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. **Association ID (AID)** คืออะไร มีบทบาทอย่างไรใน Phase 3 และส่งคืนมาในโครงสร้างข้อมูลตัวแปรใด?
	* **ตอบ:** Association ID (AID) คือหมายเลขประจำตัว (ID) ที่ Access Point (AP) กำหนดให้กับอุปกรณ์ (Station) แต่ละเครื่องเมื่อผ่านกระบวนการ Association (Phase 3) สำเร็จ มีบทบาทสำคัญในการระบุตัวตนของอุปกรณ์บนเครือข่ายย่อยนั้นๆ เพื่อใช้ในการจัดการคิวส่งข้อมูลและระบบจัดการพลังงาน (Power Management / DTIM) ค่านี้จะถูกส่งคืนกลับมาในโครงสร้างข้อมูล `wifi_event_sta_connected_t` ผ่านตัวแปรสมาชิกชื่อ `.aid`

2. เหตุใดการเชื่อมต่อ Wi-Fi ความปลอดภัยแบบ WPA2-PSK จึงสามารถผ่าน Phase 2 (Authentication) และ Phase 3 (Association) จนเกิด Event `WIFI_EVENT_STA_CONNECTED` ได้สำเร็จ แม้ผู้ใช้จะป้อนรหัสผ่าน (Password) ผิด?
	* **ตอบ:** เพราะในมาตรฐาน WPA2-PSK การทำ Authentication ใน Phase 2 จะเป็นแบบ "Open System" ซึ่งเป็นการเปิดรับการจับมือเบื้องต้นเพื่อสร้างช่องสัญญาณวิทยุ (Layer 2) โดยที่ **ยังไม่มีการนำรหัสผ่าน Wi-Fi มาตรวจสอบในขั้นตอนนี้** บอร์ดจึงสามารถเชื่อมต่อจนจบ Phase 3 และเกิด Event แจ้งเตือนการเชื่อมต่อสำเร็จได้ การตรวจสอบรหัสผ่านที่แท้จริงจะเกิดขึ้นใน Phase 4 (EAPOL 4-Way Handshake) ซึ่งหากผู้ใช้ใส่รหัสผ่านผิด AP จะเตะอุปกรณ์ออกจากระบบ (Deauthentication) ในภายหลัง

3. หาก Router มีการตั้งค่า **MAC Address Filtering** (อนุญาตเฉพาะ MAC ที่ลงทะเบียน) ESP32 จะล้มเหลวในเฟสใด และจะส่ง Disconnect Reason Code ใดออกมา?
	* **ตอบ:** การล้มเหลวจะเกิดขึ้นตั้งแต่ต้นใน **Phase 2 (Authentication Phase)** ทันทีที่ ESP32 ร้องขอเข้าใช้งาน Router จะตรวจสอบ MAC Address และปฏิเสธการเชื่อมต่อ (Authentication Rejected) โดยระบบจะส่ง Disconnect Reason Code กลับมาเป็น **WIFI_REASON_AUTH_FAIL** (เช่น Reason Code 1 หรือ 202)

4. สรุปความแตกต่างสำคัญระหว่างจุดสิ้นสุดของ **Phase 3 (Link-Layer Connected)** กับจุดสิ้นสุดของ **Phase 5 (IP Address Assigned)**
	* **ตอบ:** 
	* **จุดสิ้นสุด Phase 3 (Link-Layer Connected):** คือการเชื่อมต่อสำเร็จในระดับกายภาพและ Data Link Layer (MAC Layer) บอร์ด ESP32 และ AP รู้จักกันแล้ว (เกิด Event `WIFI_EVENT_STA_CONNECTED`) แต่บอร์ดยังไม่สามารถสื่อสารออกสู่อินเทอร์เน็ตได้เนื่องจากยังไม่มีที่อยู่ IP
	* **จุดสิ้นสุด Phase 5 (IP Address Assigned):** คือการเชื่อมต่อสำเร็จในระดับ Network Layer อย่างสมบูรณ์ บอร์ดผ่านกระบวนการเจรจา DHCP จนได้รับ IP Address, Subnet Mask และ Gateway (เกิด Event `IP_EVENT_STA_GOT_IP`) ทำให้อุปกรณ์พร้อมส่งผ่านข้อมูลโปรโตคอล TCP/IP ออกสู่โลกอินเทอร์เน็ตได้จริง


Log
```text
I (29) boot: ESP-IDF v5.5.1 2nd stage bootloader
I (29) boot: compile time Aug  4 2026 11:48:49
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
I (399) app_init: Compile time:     Aug  4 2026 11:47:55
I (404) app_init: ELF file SHA256:  6cf3578db...
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
I (458) spi_flash: detected chip: generic
I (460) spi_flash: flash io: dio
W (463) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (476) main_task: Started on CPU0
I (486) main_task: Calling app_main()
I (486) LAB_AUTH_ASSOC: [FORENSIC]: Call nvs_flash_init()
I (506) LAB_AUTH_ASSOC: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (506) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_netif_init()
I (506) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_event_loop_create_default()
I (516) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (516) LAB_AUTH_ASSOC: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbd838
I (526) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_init(&cfg)
I (546) wifi:wifi driver task: 3ffbff24, prio:23, stack:6656, core=0
I (556) wifi:wifi firmware version: 14da9b7
I (556) wifi:wifi certification version: v7.0
I (556) wifi:config NVS flash: enabled
I (556) wifi:config nano formatting: disabled
I (566) wifi:Init data frame dynamic rx buffer num: 32
I (566) wifi:Init static rx mgmt buffer num: 5
I (566) wifi:Init management short buffer num: 32
I (576) wifi:Init dynamic tx buffer num: 32
I (576) wifi:Init static rx buffer size: 1600
I (586) wifi:Init static rx buffer num: 10
I (586) wifi:Init dynamic rx buffer num: 32
I (596) wifi_init: rx ba win: 6
I (596) wifi_init: accept mbox: 6
I (596) wifi_init: tcpip mbox: 32
I (596) wifi_init: udp mbox: 6
I (606) wifi_init: tcp mbox: 6
I (606) wifi_init: tcp tx win: 5760
I (606) wifi_init: tcp rx win: 5760
I (616) wifi_init: tcp mss: 1440
I (616) wifi_init: WiFi IRAM OP enabled
I (616) wifi_init: WiFi RX IRAM OP enabled
I (626) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (626) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (636) LAB_AUTH_ASSOC: ==================================================================
I (646) LAB_AUTH_ASSOC:   Lab 5.3: Wi-Fi Authentication & Association Phase (ESP-IDF Forensic)
I (656) LAB_AUTH_ASSOC: ==================================================================
I (656) LAB_AUTH_ASSOC: 

I (666) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (666) LAB_AUTH_ASSOC: >>> Experiment 5.3.1: Link-Layer Auth & Assoc Phase Test
I (676) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (686) LAB_AUTH_ASSOC:   Target SSID    : "Pleum825"
I (686) LAB_AUTH_ASSOC:   Target Password: "12345678"
I (696) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_stop()
I (696) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
W (706) wifi:Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2
I (736) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (736) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_start()
I (736) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (826) wifi:mode : sta (14:33:5c:0e:94:44)
I (826) wifi:enable tsf
I (826) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (826) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (826) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (836) LAB_AUTH_ASSOC: [FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...
I (846) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (856) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (1126) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
I (1126) wifi:state: init -> auth (0xb0)
I (1136) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (1166) wifi:state: auth -> assoc (0x0)
I (1186) wifi:state: assoc -> run (0x10)
I (1226) wifi:connected with Pleum825, aid = 1, channel 6, BW20, bssid = d6:65:f4:32:83:9c
I (1236) wifi:security: WPA2-PSK, phy: bgn, rssi: -42
I (1246) wifi:pm start, type: 1

I (1246) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (1246) LAB_AUTH_ASSOC: =======================================================
I (1256) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (1256) LAB_AUTH_ASSOC:   [SUCCESS]: Phase 2 (Auth) & Phase 3 (Assoc) COMPLETED!
I (1266) LAB_AUTH_ASSOC:   -> Connected SSID        : Pleum825
I (1276) LAB_AUTH_ASSOC:   -> BSSID (MAC Address)   : D6:65:F4:32:83:9C
I (1276) LAB_AUTH_ASSOC:   -> Channel               : 6
I (1286) LAB_AUTH_ASSOC:   -> Auth Mode             : 3
I (1286) LAB_AUTH_ASSOC:   -> Association ID (AID)  : 3
I (1296) LAB_AUTH_ASSOC: =======================================================
I (1256) wifi:<ba-add>idx:0 (ifx:0, d6:65:f4:32:83:9c), tid:0, ssn:0, winSize:64
I (1306) LAB_AUTH_ASSOC: [RESULT]: TEST PASSED - Phase 2 (Auth) & Phase 3 (Assoc) Successful!
I (1326) wifi:dp: 2, bi: 102400, li: 4, scale listen interval from 307200 us to 409600 us
I (1326) wifi:AP's beacon interval = 102400 us, DTIM period = 2
I (2346) esp_netif_handlers: sta ip: 10.219.61.137, mask: 255.255.255.0, gw: 10.219.61.159
I (3316) LAB_AUTH_ASSOC: 

I (3316) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (3316) LAB_AUTH_ASSOC: >>> Experiment 5.3.2: Link-Layer Test - Non-Existent AP
I (3316) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (3326) LAB_AUTH_ASSOC:   Target SSID    : "NON_EXISTENT_AP_9999"
I (3336) LAB_AUTH_ASSOC:   Target Password: "12345678"
I (3336) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_stop()
I (3346) wifi:state: run -> init (0x0)
I (3356) wifi:pm stop, total sleep time: 1515508 us / 2107988 us

I (3356) wifi:<ba-del>idx:0, tid:0
I (3356) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
W (3366) LAB_AUTH_ASSOC: =======================================================
W (3366) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (3376) LAB_AUTH_ASSOC:   -> Target SSID          : Pleum825
W (3386) LAB_AUTH_ASSOC:   -> Reason Code (Decimal): 8
W (3386) LAB_AUTH_ASSOC:   -> Reason Code (Hex)    : 0x08
W (3396) LAB_AUTH_ASSOC:   -> Reason Diagnosis     : OTHER_DISCONNECT_REASON
W (3396) LAB_AUTH_ASSOC: =======================================================
I (3406) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (3426) wifi:flush txq
I (3426) wifi:stop sw txq
I (3426) wifi:lmac stop hw txq
I (3426) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
W (3426) wifi:Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2
I (3476) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (3476) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_start()
I (3486) wifi:mode : sta (14:33:5c:0e:94:44)
I (3486) wifi:enable tsf
I (3486) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (3496) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (3496) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (3506) LAB_AUTH_ASSOC: [FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...
I (3516) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (3516) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (3526) LAB_AUTH_ASSOC: [RESULT]: TEST FAILED - Disconnected event captured in Link-Layer.
I (3536) LAB_AUTH_ASSOC: ==================================================================
I (3546) LAB_AUTH_ASSOC:   [Phase 2 & Phase 3 Completed: Link-Layer Auth & Assoc Finished]
I (3546) LAB_AUTH_ASSOC: ==================================================================
I (3556) main_task: Returned from app_main()
W (5936) LAB_AUTH_ASSOC: =======================================================
W (5936) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (5936) LAB_AUTH_ASSOC:   -> Target SSID          : NON_EXISTENT_AP_9999
W (5946) LAB_AUTH_ASSOC:   -> Reason Code (Decimal): 201
W (5946) LAB_AUTH_ASSOC:   -> Reason Code (Hex)    : 0xC9
W (5956) LAB_AUTH_ASSOC:   -> Reason Diagnosis     : WIFI_REASON_NO_AP_FOUND (201) [Phase 1: SSID Not Found]
W (5966) LAB_AUTH_ASSOC: =======================================================
```

---

## 10-Labsheet-05-4-Wi-Fi-Handshake-IP-Phase

## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองใน Handshake & IP Phase

| ข้อการทดลอง | สถานการณ์ทดสอบ   | Event `WIFI_EVENT_STA_CONNECTED` (เกิด/ไม่เกิด) | Event `IP_EVENT_STA_GOT_IP` (เกิด/ไม่เกิด) | ผลการทดลอง | Disconnect Reason Code (ถ้ามี)          |
| :---------: | :--------------- | :---------------------------------------------: | :----------------------------------------: | :--------: | :-------------------------------------- |
|  **5.4.1**  | Password ถูกต้อง |                      เกิด                       |                    เกิด                    |   Passed   | -                                       |
|  **5.4.2**  | Password ผิด     |                     ไม่เกิด                     |                  ไม่เกิด                   |   Failed   | 15 (WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT) |

### 6.2 บันทึกข้อมูล IP Network จาก Event `IP_EVENT_STA_GOT_IP` (ข้อ 5.4.1)

| พารามิเตอร์ Network Layer | ค่าที่จัดสรรได้จริงจาก DHCP Server |
| :------------------------ | :--------------------------------- |
| **IP Address**            | 10.219.61.137                      |
| **Subnet Mask**           | 255.255.255.0                      |
| **Default Gateway**       | 10.219.61.159                      |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดกระบวนการ **4-Way Handshake** จึงพิสูจน์ทราบรหัสผ่าน Wi-Fi ได้โดยไม่ต้องส่งรหัสผ่าน (Passphrase) ลอยไปในอากาศเลยแม้แต่แพ็กเกจเดียว?
	* **ตอบ:** กระบวนการนี้ใช้กลไกการพิสูจน์แบบ **Challenge-Response** โดยทั้ง Access Point (AP) และ ESP32 จะนำรหัสผ่าน (Passphrase) ไปคำนวณร่วมกับชื่อ SSID เพื่อสร้างคีย์หลัก (PMK) เอาไว้ในเครื่องของตนเองล่วงหน้า เมื่อถึงเวลา Handshake ทั้งสองฝั่งจะแลกเปลี่ยนเพียง "ตัวเลขสุ่ม (Nonce)" และ "ค่ายืนยันความถูกต้อง (MIC)" ผ่านอากาศแทน หากปลายทางสามารถถอดรหัสและคำนวณค่า MIC ออกมาได้ตรงกัน ก็เป็นการพิสูจน์ได้ทันทีว่าทั้งสองฝั่งถือรหัสผ่านเดียวกันอยู่ โดยไม่จำเป็นต้องส่งรหัสผ่านตัวจริงให้เสี่ยงต่อการถูกดักจับ

2. อธิบายบทบาทและที่มาของคีย์ **PMK (Pairwise Master Key)** และ **PTK (Pairwise Transient Key)** ว่ามีความสัมพันธ์กันอย่างไรในการเข้ารหัสเฟรมข้อมูล?
	* **ตอบ:** 
	* **PMK (Pairwise Master Key):** คือ "คีย์ตั้งต้น" ที่ได้จากการนำรหัสผ่าน (Passphrase) และชื่อเครือข่าย (SSID) มาผ่านฟังก์ชันแฮช (PBKDF2) คีย์นี้จะมีค่าคงที่ตลอดตราบใดที่รหัสผ่านไม่เปลี่ยน บทบาทของ PMK คือเป็นวัตถุดิบหลักในการนำไปสร้างคีย์ชั่วคราว 
	* **PTK (Pairwise Transient Key):** คือ "คีย์ชั่วคราว" ที่ถูกสร้างขึ้นใหม่ทุกครั้งที่มีการเชื่อมต่อ โดยเกิดจากการนำ **PMK + MAC Address ของทั้ง 2 ฝั่ง + ค่าสุ่ม (Nonce) ของทั้ง 2 ฝั่ง** มาผสมกัน บทบาทของ PTK คือการนำไปใช้ **เข้ารหัสเฟรมข้อมูล (Data Frame)** ที่รับส่งกันจริงๆ ในเซสชันนั้น ทำให้แต่ละการเชื่อมต่อมีคีย์เข้ารหัสที่ไม่ซ้ำกันเลย

3. เหตุใดเมื่อเราพิมพ์ Password ผิด (ข้อ 5.4.2) ESP32 จึงยังคงได้รับ Event **`WIFI_EVENT_STA_CONNECTED`** ก่อนที่จะเกิด Event **`WIFI_EVENT_STA_DISCONNECTED`** ตามมาในภายหลัง?
	* **ตอบ:** ในมาตรฐานความปลอดภัยแบบ WPA2-PSK กระบวนการในระดับ Link Layer (Phase 2: Authentication และ Phase 3: Association) จะเป็นการเปิดรับการเชื่อมต่อแบบ Open System เพื่อสร้างช่องสัญญาณทางกายภาพเท่านั้น (ยังไม่มีการตรวจสอบรหัสผ่าน) เมื่อผ่าน Phase 3 บอร์ดจึงแจ้งเตือน Event `WIFI_EVENT_STA_CONNECTED` ออกมาก่อน จากนั้นการตรวจสอบรหัสผ่านอย่างจริงจังจะเริ่มขึ้นใน Phase 4 (4-Way Handshake) เมื่อรหัสผ่านผิด กระบวนการเจรจาคีย์ PTK จึงล้มเหลว (Timeout) AP จึงทำการเตะบอร์ดออกจากเครือข่าย ทำให้เกิด Event `WIFI_EVENT_STA_DISCONNECTED` (Reason Code 15) ตามมาเตะออกในที่สุด

4. หากเครือข่าย Wi-Fi ไม่มี DHCP Server (ไม่มีการแจก IP อัตโนมัติ) ผลการทดลองในข้อ 5.4.1 จะหยุดอยู่ที่ขั้นตอนใด และจะไม่เกิด Event ใดขึ้น?
	* **ตอบ:** หากไม่มี DHCP Server ผลการทดลองจะทำงานผ่านเฟสการจับมือและตรวจสอบรหัสผ่าน (Phase 1-4) ได้สำเร็จตามปกติ แต่จะไป **หยุดชะงักอยู่ที่ Phase 5 (IP Assignment Phase)** โดยระบบจะยังคงเกิด Event `WIFI_EVENT_STA_CONNECTED` (เพราะเชื่อมต่อ Layer 2 สำเร็จ) แต่จะ **ไม่เกิด Event `IP_EVENT_STA_GOT_IP`** ขึ้นเลย เนื่องจากบอร์ดไม่ได้รับการตอบกลับจาก DHCP Server ส่งผลให้บอร์ดไม่สามารถเชื่อมต่อออกสู่อินเทอร์เน็ตได้ (ใช้งานในระดับ Network Layer ไม่ได้)

Log
```
I (29) boot: ESP-IDF v5.5.1 2nd stage bootloader
I (29) boot: compile time Aug  4 2026 12:14:37
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
I (399) app_init: Compile time:     Aug  4 2026 12:13:37
I (404) app_init: ELF file SHA256:  8d64e9b94...
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
I (458) spi_flash: detected chip: generic
I (460) spi_flash: flash io: dio
W (463) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (476) main_task: Started on CPU0
I (486) main_task: Calling app_main()
I (486) LAB_HANDSHAKE_IP: [FORENSIC]: Call nvs_flash_init()
I (506) LAB_HANDSHAKE_IP: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (506) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_netif_init()
I (506) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_loop_create_default()
I (506) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (516) LAB_HANDSHAKE_IP: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbd838
I (526) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_init(&cfg)
I (546) wifi:wifi driver task: 3ffbff24, prio:23, stack:6656, core=0
I (556) wifi:wifi firmware version: 14da9b7
I (556) wifi:wifi certification version: v7.0
I (556) wifi:config NVS flash: enabled
I (556) wifi:config nano formatting: disabled
I (566) wifi:Init data frame dynamic rx buffer num: 32
I (566) wifi:Init static rx mgmt buffer num: 5
I (566) wifi:Init management short buffer num: 32
I (576) wifi:Init dynamic tx buffer num: 32
I (576) wifi:Init static rx buffer size: 1600
I (586) wifi:Init static rx buffer num: 10
I (586) wifi:Init dynamic rx buffer num: 32
I (596) wifi_init: rx ba win: 6
I (596) wifi_init: accept mbox: 6
I (596) wifi_init: tcpip mbox: 32
I (596) wifi_init: udp mbox: 6
I (606) wifi_init: tcp mbox: 6
I (606) wifi_init: tcp tx win: 5760
I (606) wifi_init: tcp rx win: 5760
I (616) wifi_init: tcp mss: 1440
I (616) wifi_init: WiFi IRAM OP enabled
I (616) wifi_init: WiFi RX IRAM OP enabled
I (626) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (626) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_handler_instance_register(IP_EVENT)
I (636) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (646) LAB_HANDSHAKE_IP: ==================================================================
I (656) LAB_HANDSHAKE_IP:   Lab 5.4: 4-Way Handshake & IP Assignment Phase (ESP-IDF Forensic)
I (656) LAB_HANDSHAKE_IP: ==================================================================
I (666) LAB_HANDSHAKE_IP: 

I (676) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (676) LAB_HANDSHAKE_IP: >>> Experiment 5.4.1: Handshake & IP Test - Correct Password
I (686) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (696) LAB_HANDSHAKE_IP:   Target SSID    : "Pleum825"
I (696) LAB_HANDSHAKE_IP:   Target Password: "12345678"
I (706) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_stop()
I (706) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (746) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (746) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_start()
I (746) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (826) wifi:mode : sta (14:33:5c:0e:94:44)
I (836) wifi:enable tsf
I (836) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (836) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (836) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (846) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_connect()
I (856) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (956) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
I (956) wifi:state: init -> auth (0xb0)
I (956) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (976) wifi:state: auth -> assoc (0x0)
I (986) wifi:state: assoc -> run (0x10)
I (1016) wifi:connected with Pleum825, aid = 1, channel 6, BW20, bssid = d6:65:f4:32:83:9c
I (1016) wifi:security: WPA2-PSK, phy: bgn, rssi: -42
I (1026) wifi:pm start, type: 1

I (1026) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (1036) LAB_HANDSHAKE_IP: =======================================================
I (1036) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (1046) LAB_HANDSHAKE_IP:   -> Phase 2 (Auth) & Phase 3 (Assoc) PASSED
I (1046) LAB_HANDSHAKE_IP:   -> Connected SSID  : Pleum825
I (1056) LAB_HANDSHAKE_IP:   -> BSSID           : D6:65:F4:32:83:9C
I (1056) LAB_HANDSHAKE_IP:   -> Channel         : 6
I (1066) LAB_HANDSHAKE_IP:   -> Association ID  : 3
I (1066) LAB_HANDSHAKE_IP: [FORENSIC]: Entering Phase 4: 4-Way EAPOL Key Exchange...
I (1076) LAB_HANDSHAKE_IP: =======================================================
I (1036) wifi:<ba-add>idx:0 (ifx:0, d6:65:f4:32:83:9c), tid:0, ssn:0, winSize:64
I (1086) wifi:dp: 2, bi: 102400, li: 4, scale listen interval from 307200 us to 409600 us
I (1096) wifi:AP's beacon interval = 102400 us, DTIM period = 2
I (2146) esp_netif_handlers: sta ip: 10.219.61.137, mask: 255.255.255.0, gw: 10.219.61.159
I (2146) LAB_HANDSHAKE_IP: =======================================================
I (2146) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!
I (2156) LAB_HANDSHAKE_IP:   [SUCCESS]: Phase 4 (4-Way Handshake) & Phase 5 (DHCP IP) COMPLETED!
I (2166) LAB_HANDSHAKE_IP:   -> Allocated IP Address : 10.219.61.137
I (2166) LAB_HANDSHAKE_IP:   -> Subnet Mask          : 255.255.255.0
I (2176) LAB_HANDSHAKE_IP:   -> Default Gateway      : 10.219.61.159
I (2176) LAB_HANDSHAKE_IP: =======================================================
I (2186) LAB_HANDSHAKE_IP: [RESULT]: TEST PASSED - 4-Way Handshake & DHCP IP Assignment Successful!
I (4196) LAB_HANDSHAKE_IP: 

I (4196) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (4196) LAB_HANDSHAKE_IP: >>> Experiment 5.4.2: Handshake Test - Incorrect Password
I (4196) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (4206) LAB_HANDSHAKE_IP:   Target SSID    : "Pleum825"
I (4216) LAB_HANDSHAKE_IP:   Target Password: "WRONG_PASSWORD_1234"
I (4216) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_stop()
I (4226) wifi:state: run -> init (0x0)
I (4236) wifi:pm stop, total sleep time: 2543431 us / 3208004 us

I (4236) wifi:<ba-del>idx:0, tid:0
I (4236) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
W (4246) LAB_HANDSHAKE_IP: =======================================================
W (4246) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (4256) LAB_HANDSHAKE_IP:   -> Target SSID          : Pleum825
W (4266) LAB_HANDSHAKE_IP:   -> Reason Code (Decimal): 8
W (4266) LAB_HANDSHAKE_IP:   -> Reason Code (Hex)    : 0x08
W (4276) LAB_HANDSHAKE_IP:   -> Reason Diagnosis     : OTHER_DISCONNECT_REASON
W (4276) LAB_HANDSHAKE_IP: =======================================================
I (4286) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (4296) wifi:flush txq
I (4296) wifi:stop sw txq
I (4296) wifi:lmac stop hw txq
I (4306) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (4336) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (4336) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_start()
I (4346) wifi:mode : sta (14:33:5c:0e:94:44)
I (4346) wifi:enable tsf
I (4346) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (4356) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (4356) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (4366) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_connect()
I (4376) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (4376) LAB_HANDSHAKE_IP: [RESULT]: TEST FAILED - Disconnected during Handshake or Auth.
I (4386) LAB_HANDSHAKE_IP: ==================================================================
I (4396) LAB_HANDSHAKE_IP:   [Phase 4 & Phase 5 Completed: Wi-Fi Handshake & IP Lab Finished]
I (4406) LAB_HANDSHAKE_IP: ==================================================================
I (4416) main_task: Returned from app_main()
I (4696) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
I (4696) wifi:state: init -> auth (0xb0)
I (4706) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (4706) wifi:state: auth -> assoc (0x0)
I (4716) wifi:state: assoc -> run (0x10)
I (7726) wifi:state: run -> init (0xf00)
I (7736) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
W (7736) LAB_HANDSHAKE_IP: =======================================================
W (7736) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (7746) LAB_HANDSHAKE_IP:   -> Target SSID          : Pleum825
W (7746) LAB_HANDSHAKE_IP:   -> Reason Code (Decimal): 15
W (7756) LAB_HANDSHAKE_IP:   -> Reason Code (Hex)    : 0x0F
W (7756) LAB_HANDSHAKE_IP:   -> Reason Diagnosis     : WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT (204) [Phase 4: Wrong Password]
W (7766) LAB_HANDSHAKE_IP: =======================================================
```

---