## 6. ตารางบันทึกผลการทดลอง (Experiment Results)
ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบการสแกนทั้ง 4 กรณี

| ข้อการทดลอง | เงื่อนไขการสแกน | สถานะ (Success/Error Code) | จำนวน AP ที่พบ (เครือข่าย) | เวลาที่ใช้ในการสแกน (ms) |
| :---: | :--- | :---: | :---: | :---: |
| **5.1.1** | สแกนทั่วไปทุก Channel |	Success (ESP_OK) |13 |2499 |
| **5.1.2** | กำหนดสแกนเฉพาะ Channel 1 |	Success (ESP_OK) |6 |200 |
| **5.1.3** | กำหนดสแกน SSID ที่มีจริง |	Success (ESP_OK) |2 |2499 |
| **5.1.4** | กำหนดสแกน SSID ที่ไม่มีจริง |Success (ESP_OK) |0 |2498 |

### 6.2 ตารางรายละเอียด AP ที่พบจากการสแกนทั่วไป (ข้อ 5.1.1)

| ลำดับ | ชื่อเครือข่าย (SSID) | MAC Address (BSSID) | ความแรงสัญญาณ (RSSI: dBm) | ช่องความถี่ (Channel) | ประเภทการเข้ารหัส (Encryption Type) |
| :---: | :--- | :--- | :---: | :---: | :--- |
| 1 |KMITL-WIFI |78:17:BE:C0:7D:A1 |-54 |1 |OPEN (No Password) |
| 2 |	😑 |62:DD:AB:3C:2D:A6 |-60 |11 |WPA2_PSK |
| 3 | Redmi Note 10S|66:34:B4:F7:03:8A |-63 |5 |WPA2_PSK |
| 4 |KMITL-Legacy |78:17:BE:C0:7D:A0 |-65 |1 |WPA2_ENTERPRISE |
| 5 |KMITL-IoT |78:17:BE:C0:7D:A2 |-65 |1 |WPA2_PSK |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. การกำหนดค่าในโครงสร้าง `wifi_scan_config_t` สำหรับสแกนเจาะจงเฉพาะช่องความถี่ (ข้อ 5.1.2) ช่วยลดเวลาในการสแกนเมื่อเทียบกับการสแกนทุกช่องความถี่ (ข้อ 5.1.1) อย่างไร และมีข้อจำกัดอย่างไร?
```c= wifi_scan_config_t ทำให้ไม่ต้องสลับช่องสัญญาณ (hop) ไปทีละช่อง จึงลดเวลาสแกนจาก 2499 ms เหลือเพียง 200 ms แต่ข้อจำกัดคือจะตรวจไม่พบ AP ที่อยู่นอกช่องนั้นเลย ดังผลการทดลองที่พบเพียง 6 จาก 13 เครือข่าย
```
2. เมื่อสังเกตผล Forensic Log ในข้อ 5.1.4 (สแกนหา SSID ที่ไม่มีอยู่จริง) ฟังก์ชัน `esp_wifi_scan_start()`, `esp_wifi_scan_get_ap_num()` และ `esp_wifi_scan_get_ap_records()` ส่งคืนค่าอย่างไร?
```c= ทั้งสามฟังก์ชันยังคืนค่า ESP_OK (0x0) เหมือนเดิมทุกฟังก์ชัน เพราะการไม่พบ AP ตรงเงื่อนไขไม่ถือเป็นข้อผิดพลาด เพียงแต่ค่า ap_count และ records ที่ได้เป็น 0 เท่านั้น
```
3. ค่าระดับความแรงสัญญาณ (RSSI) ที่แสดงเป็นตัวเลขติดลบ (เช่น -45 dBm กับ -80 dBm) ค่าใดแสดงถึงสัญญาณที่มีความแรงและความเสถียรมากกว่ากัน?
```c= -45 dBm แสดงสัญญาณที่แรงและเสถียรกว่า เนื่องจากยิ่งค่าใกล้ 0 มากยิ่งหมายถึงสัญญาณแรง ส่วน -80 dBm เป็นสัญญาณอ่อน ใกล้ขอบเขตการรับสัญญาณและมักไม่เสถีย
```
4. เหตุใดการดึงค่า `authmode` (`wifi_auth_mode_t`) จากโครงสร้าง `wifi_ap_record_t` จึงมีความสำคัญต่อการเตรียมการในเฟสถัดไป (Authentication & Association Phase)?
```c
= authmode บอกประเภทการเข้ารหัสของ AP เช่น Open, PSK หรือ Enterprise ซึ่งจำเป็นต่อการตั้งค่า wifi_config_t ให้ถูกต้อง หากตั้งค่าผิดประเภท กระบวนการ Authentication จะล้มเหลวทันที
```

```c
rst:0x1 (POWERON_�j     5
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (58) boot:  0 nvs              WiFi �ets Jul 29 2019 12:21:46

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0030,len:6380
ho 0 tail 12 room 4
load:0x40078000,len:15916
load:0x40080400,len:3860
--- 0x40080400: _invalid_pc_placeholder at C:/Users/hp/esp/v5.5.1/esp-idf/components/xtensa/xtensa_vectors.S:2235
entry 0x40080638
--- 0x40080638: call_start_cpu0 at C:/Users/hp/esp/v5.5.1/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v5.5.1 2nd stage bootloader
I (29) boot: compile time Aug  3 2026 10:06:14
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
I (389) app_init: Project name:     LED_Blink
I (393) app_init: App version:      1
I (396) app_init: Compile time:     Aug  3 2026 10:08:47
I (401) app_init: ELF file SHA256:  bc453067b...
I (406) app_init: ESP-IDF:          v5.5.1
I (409) efuse_init: Min chip rev:     v0.0
I (413) efuse_init: Max chip rev:     v3.99 
I (417) efuse_init: Chip rev:         v3.1
I (421) heap_init: Initializing. RAM available for dynamic allocation:
I (427) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (432) heap_init: At 3FFB7FC8 len 00028038 (160 KiB): DRAM
I (438) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (443) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (449) heap_init: At 40097E0C len 000081F4 (32 KiB): IRAM
I (455) spi_flash: detected chip: generic
I (457) spi_flash: flash io: dio
W (460) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (474) main_task: Started on CPU0
I (484) main_task: Calling app_main()
I (484) LAB_WIFI_SCAN: [FORENSIC]: Call nvs_flash_init()
I (494) LAB_WIFI_SCAN: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (494) LAB_WIFI_SCAN: [FORENSIC]: Call esp_netif_init()
I (494) LAB_WIFI_SCAN: [FORENSIC]: esp_netif_init() returned ESP_OK (0x0)
I (494) LAB_WIFI_SCAN: [FORENSIC]: Call esp_event_loop_create_default()
I (504) LAB_WIFI_SCAN: [FORENSIC]: esp_event_loop_create_default() returned ESP_OK (0x0)
I (514) LAB_WIFI_SCAN: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (524) LAB_WIFI_SCAN: [FORENSIC]: esp_netif_create_default_wifi_sta() returned pointer 0x3ffbd61c
I (524) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_init(&cfg)
I (544) wifi:wifi driver task: 3ffbfdac, prio:23, stack:6656, core=0
I (544) wifi:wifi firmware version: 14da9b7
I (544) wifi:wifi certification version: v7.0
I (544) wifi:config NVS flash: enabled
I (554) wifi:config nano formatting: disabled
I (554) wifi:Init data frame dynamic rx buffer num: 32
I (564) wifi:Init static rx mgmt buffer num: 5
I (564) wifi:Init management short buffer num: 32
I (564) wifi:Init dynamic tx buffer num: 32
I (574) wifi:Init static rx buffer size: 1600
I (574) wifi:Init static rx buffer num: 10
I (584) wifi:Init dynamic rx buffer num: 32
I (584) wifi_init: rx ba win: 6
I (584) wifi_init: accept mbox: 6
I (594) wifi_init: tcpip mbox: 32
I (594) wifi_init: udp mbox: 6
I (594) wifi_init: tcp mbox: 6
I (594) wifi_init: tcp tx win: 5760
I (604) wifi_init: tcp rx win: 5760
I (604) wifi_init: tcp mss: 1440
I (604) wifi_init: WiFi IRAM OP enabled
I (614) wifi_init: WiFi RX IRAM OP enabled
I (614) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_init() returned ESP_OK (0x0)
I (624) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (624) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_set_mode() returned ESP_OK (0x0)
I (634) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_start()
I (644) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
W (644) phy_init: failed to load RF calibration data (0x1102), falling back to full calibration
I (724) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(2)
I (734) wifi:mode : sta (14:33:5c:0d:cd:7c)
I (734) wifi:enable tsf
I (734) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (734) LAB_WIFI_SCAN: ==================================================================
I (744) LAB_WIFI_SCAN:   Lab 5.1: Wi-Fi Connection and Scanning Phase (ESP-IDF Forensic)
I (754) LAB_WIFI_SCAN: ==================================================================
I (764) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (764) LAB_WIFI_SCAN: >>> Experiment 5.1.1: General AP Scan (All Channels)
I (774) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (784) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (3294) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2499 ms]
I (3294) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (3294) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=13
I (3304) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (3304) LAB_WIFI_SCAN: [AP COUNT]: 13 network(s) found
I (3314) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (3324) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=13

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | KMITL-WIFI               | 78:17:BE:C0:7D:A1 | -54  dBm | 1    | OPEN (No Password)  
2    | 😑                     | 62:DD:AB:3C:2D:A6 | -60  dBm | 11   | WPA2_PSK            
3    | Redmi Note 10S           | 66:34:B4:F7:03:8A | -63  dBm | 5    | WPA2_PSK            
4    | KMITL-Legacy             | 78:17:BE:C0:7D:A0 | -65  dBm | 1    | WPA2_ENTERPRISE     
5    | KMITL-IoT                | 78:17:BE:C0:7D:A2 | -65  dBm | 1    | WPA2_PSK            
6    | <Hidden SSID>            | A6:AE:BD:24:7B:30 | -71  dBm | 6    | WPA2_PSK            
7    | KMITL-Legacy             | 78:17:BE:A9:94:E0 | -74  dBm | 6    | WPA2_ENTERPRISE     
8    | KMITL-IoT                | 78:17:BE:A9:94:E2 | -79  dBm | 6    | WPA2_PSK            
9    | KMITL-WIFI               | 78:17:BE:C0:72:61 | -80  dBm | 11   | OPEN (No Password)  
10   | KMITL-WIFI               | 78:17:BE:A9:94:E1 | -83  dBm | 6    | OPEN (No Password)  
11   | KMITL-Legacy             | 78:17:BE:C0:72:60 | -84  dBm | 11   | WPA2_ENTERPRISE     
12   | KMITL-IoT                | 78:17:BE:C0:72:62 | -84  dBm | 11   | WPA2_PSK            
13   | RADAR1902601900480       | DA:BC:38:B3:75:51 | -85  dBm | 1    | WPA_WPA2_PSK        
--------------------------------------------------------------------------------------------------

I (4474) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (4474) LAB_WIFI_SCAN: >>> Experiment 5.1.2: Channel-Specific Scan (Channel 1)
I (4474) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (4484) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (4694) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 200 ms]
I (4694) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (4694) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=6
I (4704) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (4704) LAB_WIFI_SCAN: [AP COUNT]: 6 network(s) found
I (4714) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (4724) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=6

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | KMITL-WIFI               | 78:17:BE:C0:7D:A1 | -54  dBm | 1    | OPEN (No Password)  
2    | KMITL-Legacy             | 78:17:BE:C0:7D:A0 | -67  dBm | 1    | WPA2_ENTERPRISE     
3    | KMITL-IoT                | 78:17:BE:C0:7D:A2 | -68  dBm | 1    | WPA2_PSK            
4    | KMITL-Legacy             | 78:17:BE:C0:66:20 | -84  dBm | 1    | WPA2_ENTERPRISE     
5    | KMITL-IoT                | 78:17:BE:C0:66:22 | -84  dBm | 1    | WPA2_PSK            
6    | RADAR1902601900480       | DA:BC:38:B3:75:51 | -84  dBm | 1    | WPA_WPA2_PSK        
--------------------------------------------------------------------------------------------------

I (5814) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (5814) LAB_WIFI_SCAN: >>> Experiment 5.1.3: Targeted SSID Scan - Existing ("KMITL-WIFI")
I (5814) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (5824) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (8334) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2499 ms]
I (8334) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (8334) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=2
I (8344) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (8344) LAB_WIFI_SCAN: [AP COUNT]: 2 network(s) found
I (8354) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (8364) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=2

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | KMITL-WIFI               | 78:17:BE:C0:7D:A1 | -54  dBm | 1    | OPEN (No Password)  
2    | KMITL-WIFI               | 78:17:BE:C0:66:21 | -87  dBm | 1    | OPEN (No Password)  
--------------------------------------------------------------------------------------------------

I (9424) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (9424) LAB_WIFI_SCAN: >>> Experiment 5.1.4: Targeted SSID Scan - Non-Existent ("NON_EXISTENT_AP_9999")
I (9424) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (9434) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (11944) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2498 ms]
I (11944) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (11944) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=0
I (11954) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (11954) LAB_WIFI_SCAN: [AP COUNT]: 0 network(s) found
W (11964) LAB_WIFI_SCAN: [NOTE]: No Access Point found matching the criteria.
I (11964) LAB_WIFI_SCAN: ==================================================================
I (11974) LAB_WIFI_SCAN:   [Phase 1 Completed: Wi-Fi Scan Finished]
I (11984) LAB_WIFI_SCAN:   Program stopped after scanning. Auth/Assoc Phase not started.
I (11994) LAB_WIFI_SCAN: ==================================================================
I (11994) main_task: Returned from app_main()
```
