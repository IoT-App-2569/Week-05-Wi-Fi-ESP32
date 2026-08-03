##  ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบการสแกนทั้ง 4 กรณี

| ข้อการทดลอง | เงื่อนไขการสแกน             | สถานะ (Success/Error Code) | จำนวน AP ที่พบ (เครือข่าย) | เวลาที่ใช้ในการสแกน (ms) |
| :---------: | :-------------------------- | :------------------------: | :------------------------: | :----------------------: |
|  **5.1.1**  | สแกนทั่วไปทุก Channel       |        Scan SUCCESS        |             18             |           2501           |
|  **5.1.2**  | กำหนดสแกนเฉพาะ Channel 1    |        Scan SUCCESS        |             6              |           200            |
|  **5.1.3**  | กำหนดสแกน SSID ที่มีจริง    |        Scan SUCCESS        |             4              |           2499           |
|  **5.1.4**  | กำหนดสแกน SSID ที่ไม่มีจริง |        Scan SUCCESS        |             0              |           2498           |

### 6.2 ตารางรายละเอียด AP ที่พบจากการสแกนทั่วไป (ข้อ 5.1.1)

| ลำดับ | ชื่อเครือข่าย (SSID) | MAC Address (BSSID) | ความแรงสัญญาณ (RSSI: dBm) | ช่องความถี่ (Channel) | ประเภทการเข้ารหัส (Encryption Type) |
| ----- | -------------------- | ------------------- | ------------------------- | --------------------- | ----------------------------------- |
| 1     | KMITL-Legacy         | 78:17:BE:C0:7D:A0   | -48                       | 1                     | WPA2_ENTERPRISE                     |
| 2     | KMITL-WIFI           | 78:17:BE:C0:7D:A1   | -50                       | 1                     | OPEN (No Password)                  |
| 3     | KMITL-IoT            | 78:17:BE:C0:7D:A2   | -50                       | 1                     | WPA2_PSK                            |
| 4     | FUB                  | EA:67:85:97:BF:39   | -51                       | 10                    | WPA2_PSK                            |
| 5     | eem_Luna             | 2E:2B:53:FB:4B:AC   | -60                       | 1                     | WPA2_WPA3_PSK                       |
| 6     | Test-WiFi            | 0A:8A:B4:BB:12:61   | -66                       | 6                     | WPA2_WPA3_PSK                       |
| 7     | ไก่ติดกาว            | EE:B5:07:32:C7:DC   | -67                       | 10                    | WPA2_WPA3_PSK                       |
| 8     | KMITL-WIFI           | 78:17:BE:C0:66:21   | -79                       | 1                     | OPEN (No Password)                  |
| 9     | KMITL-Legacy         | 78:17:BE:C0:66:20   | -80                       | 1                     | WPA2_ENTERPRISE                     |
| 10    | KMITL-IoT            | 78:17:BE:C0:66:22   | -81                       | 1                     | WPA2_PSK                            |
| 11    | KMITL-WIFI           | 78:17:BE:C0:72:61   | -82                       | 11                    | OPEN (No Password)                  |
| 12    | KMITL-IoT            | 78:17:BE:C0:72:62   | -83                       | 11                    | WPA2_PSK                            |
| 13    | KMITL-Legacy         | 78:17:BE:A9:94:E0   | -84                       | 6                     | WPA2_ENTERPRISE                     |
| 14    | KMITL-IoT            | 78:17:BE:C0:66:62   | -84                       | 11                    | WPA2_PSK                            |
| 15    | KMITL-Legacy         | 78:17:BE:C0:72:60   | -84                       | 11                    | WPA2_ENTERPRISE                     |
| 16    | KMITL-Legacy         | 78:17:BE:C0:66:60   | -85                       | 11                    | WPA2_ENTERPRISE                     |
| 17    | KMITL-WIFI           | 78:17:BE:C0:66:61   | -85                       | 11                    | OPEN (No Password)                  |
| 18    | KMITL-IoT            | 78:17:BE:A9:94:E2   | -86                       | 6                     | WPA2_PSK                            |

## คำถามท้ายการทดลอง (Post-Lab Questions)

1. การกำหนดค่าในโครงสร้าง `wifi_scan_config_t` สำหรับสแกนเจาะจงเฉพาะช่องความถี่ (ข้อ 5.1.2) ช่วยลดเวลาในการสแกนเมื่อเทียบกับการสแกนทุกช่องความถี่ (ข้อ 5.1.1) อย่างไร และมีข้อจำกัดอย่างไร?
	- ในการสแกนเฉพาะ Channel จะสแกนเฉพาะช่องนั้นช่องเดียว แล้วคืนค่ากลับทันที เวลาใช้เเค่ 200 ms เเต่การสแกนทุก Channel จะต้องส่ง Probe Request และคอยฟังสัญญาณไล่ไปทีละช่องสัญญาณตั้งแต่ Channel 1 ถึง 13  ทำให้ใช้เวลารวมทั้งหมด 2,501 ms ซึ่งนานกว่ามาก
	- ข้อจำกัด หาก AP ถูกตั้งค่าแบบ Auto Channel แล้วเปลี่ยนไปใช้ช่องความถี่อื่น หรือจำ Channel ของ AP ผิดจะสแกนไม่พบ AP เลย
	- 
2. เมื่อสังเกตผล Forensic Log ในข้อ 5.1.4 (สแกนหา SSID ที่ไม่มีอยู่จริง) ฟังก์ชัน `esp_wifi_scan_start()`, `esp_wifi_scan_get_ap_num()` และ `esp_wifi_scan_get_ap_records()` ส่งคืนค่าอย่างไร?
	- esp_wifi_scan_start(): ส่งคืนค่า ESP_OK (0x0) เพราะการสแกน ระดับฮาร์ดแวร์ทำงานสำเร็จสมบูรณ์ 
	- esp_wifi_scan_get_ap_num(): ส่งคืนค่า ESP_OK (0x0) และ ap_count = 0
	- esp_wifi_scan_get_ap_records(): คืนค่า ESP_OK (0x0) และ records = 0 

3. ค่าระดับความแรงสัญญาณ (RSSI) ที่แสดงเป็นตัวเลขติดลบ (เช่น -45 dBm กับ -80 dBm) ค่าใดแสดงถึงสัญญาณที่มีความแรงและความเสถียรมากกว่ากัน?
	- -45 dBm แรงและเสถียรกว่า ค่า RSSI  มีหน่วยเป็น dBm ซึ่งเป็นค่ากำลังทางไฟฟ้าแบบติดลบ ยิ่งเข้าใกล้ 0 คือสัญญาณยิ่งมีความแรงสูง

4. เหตุใดการดึงค่า `authmode` (`wifi_auth_mode_t`) จากโครงสร้าง `wifi_ap_record_t` จึงมีความสำคัญต่อการเตรียมการในเฟสถัดไป (Authentication & Association Phase)?
	- ช่วยให้รู้ล่วงหน้าว่า AP ใช้ความปลอดภัยแบบใด เพื่อกำหนดค่า wifi_config_t.sta.threshold.authmode ให้ตรงกับ AP  ทำให้ประหยัดเวลาในการสเเกน หรือข้ามไป เฟส ถัดไปได้เลย


## Log 

```
ets Jul 29 2019 12:21:46

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0040,len:6272
load:0x40078000,len:15848
load:0x40080400,len:3920
--- 0x40080400: _invalid_pc_placeholder at /Users/ittikorntongsima/My-Library/esp-idf/components/xtensa/xtensa_vectors.S:2259
entry 0x40080644
--- 0x40080644: call_start_cpu0 at /Users/ittikorntongsima/My-Library/esp-idf/components/bootloader/subproject/main/bootloader_start.c:27
I (27) boot: ESP-IDF v6.1-dev-3480-g44c77cbf46 2nd stage bootloader
I (27) boot: compile time Aug  3 2026 10:32:50
I (28) boot: Multicore bootloader
I (30) boot: chip revision: v3.1
I (33) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode       : DIO
I (40) boot.esp32: SPI Flash Size : 2MB
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (57) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory          factory app      00 00 00010000 00100000
I (77) boot: End of partition table
I (80) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1a3b8h (107448) map
I (126) esp_image: segment 1: paddr=0002a3e0 vaddr=3ffb0000 size=045a8h ( 17832) load
I (133) esp_image: segment 2: paddr=0002e990 vaddr=40080000 size=01688h (  5768) load
I (136) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=856c4h (546500) map
I (332) esp_image: segment 4: paddr=000b56ec vaddr=40081688 size=13f84h ( 81796) load
I (366) esp_image: segment 5: paddr=000c9678 vaddr=50000000 size=00028h (    40) load
I (377) boot: Loaded app from partition at offset 0x10000
I (377) boot: Disabling RNG early entropy source...
I (387) cpu_start: Multicore app
I (396) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (396) cpu_start: Pro cpu start user code
I (396) cpu_start: cpu freq: 160000000 Hz
I (398) app_init: Application information:
I (402) app_init: Project name:     lab_1
I (405) app_init: App version:      1
I (409) app_init: Compile time:     Aug  3 2026 10:32:46
I (414) app_init: ELF file SHA256:  d8e06ee5c...
I (418) app_init: ESP-IDF:          v6.1-dev-3480-g44c77cbf46
I (424) efuse_init: Min chip rev:     v0.0
I (427) efuse_init: Max chip rev:     v3.99
I (431) efuse_init: Chip rev:         v3.1
I (435) heap_init: Initializing. RAM available for dynamic allocation:
I (442) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (447) heap_init: At 3FFB8A90 len 00027570 (157 KiB): DRAM
I (452) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (457) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (463) heap_init: At 4009560C len 0000A9F4 (42 KiB): IRAM
I (470) spi_flash: detected chip: generic
I (472) spi_flash: flash io: dio
W (475) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (489) main_task: Started on CPU0
I (499) main_task: Calling app_main()
I (499) LAB_WIFI_SCAN: [FORENSIC]: Call nvs_flash_init()
I (539) LAB_WIFI_SCAN: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (539) LAB_WIFI_SCAN: [FORENSIC]: Call esp_netif_init()
I (539) LAB_WIFI_SCAN: [FORENSIC]: esp_netif_init() returned ESP_OK (0x0)
I (539) LAB_WIFI_SCAN: [FORENSIC]: Call esp_event_loop_create_default()
I (549) LAB_WIFI_SCAN: [FORENSIC]: esp_event_loop_create_default() returned ESP_OK (0x0)
I (559) LAB_WIFI_SCAN: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (569) LAB_WIFI_SCAN: [FORENSIC]: esp_netif_create_default_wifi_sta() returned pointer 0x3ffbdeac
I (569) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_init(&cfg)
I (589) wifi:wifi driver task: 3ffc0598, prio:23, stack:6656, core=0
I (609) wifi:wifi firmware version: 5d0a58b
I (609) wifi:wifi certification version: v7.0
I (609) wifi:config NVS flash: enabled
I (609) wifi:config nano formatting: disabled
I (609) wifi:Init data frame dynamic rx buffer num: 32
I (619) wifi:Init static rx mgmt buffer num: 5
I (619) wifi:Init management short buffer num: 32
I (629) wifi:Init dynamic tx buffer num: 32
I (629) wifi:Init static rx buffer size: 1600
I (639) wifi:Init static rx buffer num: 10
I (639) wifi:Init dynamic rx buffer num: 32
I (639) wifi_init: rx ba win: 6
I (649) wifi_init: accept mbox: 6
I (649) wifi_init: tcpip mbox: 32
I (649) wifi_init: udp mbox: 6
I (649) wifi_init: tcp mbox: 6
I (659) wifi_init: tcp tx win: 5760
I (659) wifi_init: tcp rx win: 5760
I (659) wifi_init: tcp mss: 1440
I (669) wifi_init: WiFi IRAM OP enabled
I (669) wifi_init: WiFi RX IRAM OP enabled
I (669) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_init() returned ESP_OK (0x0)
I (679) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (689) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_set_mode() returned ESP_OK (0x0)
I (689) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_start()
I (699) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06
I (789) wifi:mode : sta (8c:94:df:45:93:e4)
I (789) wifi:enable tsf
I (789) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (789) LAB_WIFI_SCAN: ==================================================================
I (799) LAB_WIFI_SCAN:   Lab 5.1: Wi-Fi Connection and Scanning Phase (ESP-IDF Forensic)
I (809) LAB_WIFI_SCAN: ==================================================================
I (809) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (819) LAB_WIFI_SCAN: >>> Experiment 5.1.1: General AP Scan (All Channels)
I (829) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (839) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (3349) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2501 ms]
I (3349) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (3349) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=18
I (3359) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (3359) LAB_WIFI_SCAN: [AP COUNT]: 18 network(s) found
I (3369) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (3379) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=18

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type
--------------------------------------------------------------------------------------------------
1    | KMITL-Legacy             | 78:17:BE:C0:7D:A0 | -48  dBm | 1    | WPA2_ENTERPRISE
2    | KMITL-WIFI               | 78:17:BE:C0:7D:A1 | -50  dBm | 1    | OPEN (No Password)
3    | KMITL-IoT                | 78:17:BE:C0:7D:A2 | -50  dBm | 1    | WPA2_PSK
4    | FUB                      | EA:67:85:97:BF:39 | -51  dBm | 10   | WPA2_PSK
5    | eem_Luna                 | 2E:2B:53:FB:4B:AC | -60  dBm | 1    | WPA2_WPA3_PSK
6    | Test-WiFi                | 0A:8A:B4:BB:12:61 | -66  dBm | 6    | WPA2_WPA3_PSK
7    | ไก่ติดกาว | EE:B5:07:32:C7:DC | -67  dBm | 10   | WPA2_WPA3_PSK
8    | KMITL-WIFI               | 78:17:BE:C0:66:21 | -79  dBm | 1    | OPEN (No Password)
9    | KMITL-Legacy             | 78:17:BE:C0:66:20 | -80  dBm | 1    | WPA2_ENTERPRISE
10   | KMITL-IoT                | 78:17:BE:C0:66:22 | -81  dBm | 1    | WPA2_PSK
11   | KMITL-WIFI               | 78:17:BE:C0:72:61 | -82  dBm | 11   | OPEN (No Password)
12   | KMITL-IoT                | 78:17:BE:C0:72:62 | -83  dBm | 11   | WPA2_PSK
13   | KMITL-Legacy             | 78:17:BE:A9:94:E0 | -84  dBm | 6    | WPA2_ENTERPRISE
14   | KMITL-IoT                | 78:17:BE:C0:66:62 | -84  dBm | 11   | WPA2_PSK
15   | KMITL-Legacy             | 78:17:BE:C0:72:60 | -84  dBm | 11   | WPA2_ENTERPRISE
16   | KMITL-Legacy             | 78:17:BE:C0:66:60 | -85  dBm | 11   | WPA2_ENTERPRISE
17   | KMITL-WIFI               | 78:17:BE:C0:66:61 | -85  dBm | 11   | OPEN (No Password)
18   | KMITL-IoT                | 78:17:BE:A9:94:E2 | -86  dBm | 6    | WPA2_PSK
--------------------------------------------------------------------------------------------------

I (4569) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (4569) LAB_WIFI_SCAN: >>> Experiment 5.1.2: Channel-Specific Scan (Channel 1)
I (4569) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (4579) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (4789) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 200 ms]
I (4789) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (4789) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=6
I (4799) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (4799) LAB_WIFI_SCAN: [AP COUNT]: 6 network(s) found
I (4809) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (4819) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=6

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type
--------------------------------------------------------------------------------------------------
1    | KMITL-Legacy             | 78:17:BE:C0:7D:A0 | -48  dBm | 1    | WPA2_ENTERPRISE
2    | KMITL-IoT                | 78:17:BE:C0:7D:A2 | -48  dBm | 1    | WPA2_PSK
3    | KMITL-WIFI               | 78:17:BE:C0:7D:A1 | -49  dBm | 1    | OPEN (No Password)
4    | eem_Luna                 | 2E:2B:53:FB:4B:AC | -61  dBm | 1    | WPA2_WPA3_PSK
5    | KMITL-Legacy             | 78:17:BE:C0:66:20 | -82  dBm | 1    | WPA2_ENTERPRISE
6    | KMITL-IoT                | 78:17:BE:C0:66:22 | -82  dBm | 1    | WPA2_PSK
--------------------------------------------------------------------------------------------------

I (5909) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (5909) LAB_WIFI_SCAN: >>> Experiment 5.1.3: Targeted SSID Scan - Existing ("KMITL-Legacy")
I (5909) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (5919) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (8429) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2499 ms]
I (8429) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (8429) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=4
I (8439) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (8439) LAB_WIFI_SCAN: [AP COUNT]: 4 network(s) found
I (8449) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (8459) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=4

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type
--------------------------------------------------------------------------------------------------
1    | KMITL-Legacy             | 78:17:BE:A9:94:E0 | -78  dBm | 6    | WPA2_ENTERPRISE
2    | KMITL-Legacy             | 78:17:BE:C0:66:20 | -81  dBm | 1    | WPA2_ENTERPRISE
3    | KMITL-Legacy             | 78:17:BE:C0:66:60 | -85  dBm | 11   | WPA2_ENTERPRISE
4    | KMITL-Legacy             | 78:17:BE:C0:72:60 | -85  dBm | 11   | WPA2_ENTERPRISE
--------------------------------------------------------------------------------------------------

I (9529) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (9529) LAB_WIFI_SCAN: >>> Experiment 5.1.4: Targeted SSID Scan - Non-Existent ("NON_EXISTENT_AP_9999")
I (9529) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (9539) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (12049) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2498 ms]
I (12049) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (12049) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=0
I (12059) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (12059) LAB_WIFI_SCAN: [AP COUNT]: 0 network(s) found
W (12069) LAB_WIFI_SCAN: [NOTE]: No Access Point found matching the criteria.
I (12069) LAB_WIFI_SCAN: ==================================================================
I (12079) LAB_WIFI_SCAN:   [Phase 1 Completed: Wi-Fi Scan Finished]
I (12089) LAB_WIFI_SCAN:   Program stopped after scanning. Auth/Assoc Phase not started.
I (12099) LAB_WIFI_SCAN: ==================================================================
I (12099) main_task: Returned from app_main()

```
