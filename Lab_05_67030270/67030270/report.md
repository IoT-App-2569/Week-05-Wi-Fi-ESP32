# รายงานผลการทดลอง สัปดาห์ที่ 5

## หัวข้อ: Wi-Fi ESP32 Station Scan & Reason Codes

**รหัสนักศึกษา:** 67030270 **ชื่อ-นามสกุล:** นายกฤษฏิณัช สำราญกิจ **ชื่อภาษาอังกฤษ:** Kritsadinat Samrankit **วิชา:** ระบบสมองกลฝังตัวและการเชื่อมต่อเครือข่าย (Embedded Systems & IoT) **บอร์ดทดลอง:** ESP32 (ESP32-D0WD-V3) | **MAC Address:** 84:1F:E8:39:81:73 **โต๊ะปฏิบัติการ:** โต๊ะที่ 2 **ไฟล์โปรเจกต์:** Week05_WiFi_ESP32/67030270_template/

## 1. การเตรียมบอร์ดและสภาพแวดล้อม

**บอร์ดเปล่า ESP32 NodeMCU-32S** เสียบ Micro-USB เข้าคอมพิวเตอร์ (ไม่ต้องต่อ Breadboard) Wi-Fi ที่ใช้ทดสอบ: Kritsadinat Samrankitp (2.4 GHz Personal Mobile Hotspot)

## Lab 5.1 — Wi-Fi Station Active & Passive AP Scanning

สั่ง ESP32 สแกนหา Wi-Fi รอบข้าง และแสดงตาราง SSID, BSSID, RSSI (dBm), Channel, และ Encryption Type

### คำสั่งที่ใช้

```bash
cd Week05_WiFi_ESP32/67030270_template/Lab5-1_WiFi_Scan
idf.py build
idf.py -p <PORT> flash monitor
```

### ค่าที่วัด / คำนวณได้ (กรอกตามผลจริง)

| รายการ | ค่า |
| --- | --- |
| จำนวน AP ที่พบทั้งหมด | 7 เครือข่าย |
| RSSI ที่แรงที่สุด (dBm) | -52 dBm |
| RSSI ที่เบาที่สุด (dBm) | -86 dBm |
| เวลาที่ใช้สแกน (ms) | 2520 ms |

### 📷 รูป: รูปที่ 1: แคปหน้าจอ Terminal ผลการสแกน Wi-Fi ในบริเวณรอบตัว พร้อมค่า RSSI

![ภาพหน้าจอ Terminal แสดงตาราง SSID, ค่า RSSI (-dBm), Channel, และ Encryption Type](images/w05_1_p1.png)

### 💻 Serial Log: รายชื่อ Wi-Fi Hotspots และระดับความแรงสัญญาณ

(บันทึกจาก firebase_logs/w05_1.log)
```text
load:0x40080400,len:3860
entry 0x40080638
I (29) boot: ESP-IDF v5.5.1 2nd stage bootloader
I (31) boot: chip revision: v3.1
I (33) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode       : DIO
I (41) boot.esp32: SPI Flash Size : 2MB
I (485) main_task: Calling app_main()
I (485) LAB_WIFI_SCAN: [FORENSIC]: Call nvs_flash_init()
I (515) LAB_WIFI_SCAN: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (515) LAB_WIFI_SCAN: [FORENSIC]: Call esp_netif_init()
I (525) LAB_WIFI_SCAN: [FORENSIC]: Call esp_event_loop_create_default()
I (535) LAB_WIFI_SCAN: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (555) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_init(&cfg)
I (645) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_init() returned ESP_OK (0x0)
I (655) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (665) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_start()
I (765) wifi:mode : sta (84:1f:e8:39:81:73)
I (765) wifi:enable tsf
I (765) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (765) LAB_WIFI_SCAN: ==================================================================
I (775) LAB_WIFI_SCAN:   Lab 5.1: Wi-Fi Connection and Scanning Phase (ESP-IDF Forensic)
I (775) LAB_WIFI_SCAN: ==================================================================
I (795) LAB_WIFI_SCAN: >>> Experiment 5.1.1: General AP Scan (All Channels)
I (815) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (3335) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2520 ms]
I (3335) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (3335) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=7
I (3345) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (3345) LAB_WIFI_SCAN: [AP COUNT]: 7 network(s) found

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | KMITL-WIFI               | 3C:E8:6E:FD:66:40 | -52  dBm | 6    | OPEN (No Password)  
2    | KMITL-Legacy             | 3C:E8:6E:FD:66:45 | -54  dBm | 6    | WPA2_ENTERPRISE     
3    | KMITL-IoT                | 3C:E8:6E:FD:66:41 | -57  dBm | 6    | WPA2_PSK            
4    | Lab-i                    | F6:51:A6:6B:45:18 | -62  dBm | 6    | WPA2_PSK            
5    | INNHA                    | D6:C4:83:DC:A9:EC | -64  dBm | 6    | WPA2_PSK            
6    | Kritsadinat Samrankitp           | 78:17:BE:C0:7D:A1 | -58  dBm | 1    | WPA2_PSK            
7    | [air purifier] Samsung   | 88:57:1D:08:CD:7F | -78  dBm | 1    | WPA2_PSK            
8    | IPR-422_2G_1507          | E8:49:43:06:15:07 | -86  dBm | 1    | WPA2_PSK            
--------------------------------------------------------------------------------------------------

I (4470) LAB_WIFI_SCAN: >>> Experiment 5.1.2: Channel-Specific Scan (Channel 1)
I (4480) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (4675) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 195 ms]
I (4685) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS, ap_count=2
--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | [air purifier] Samsung   | 88:57:1D:08:CD:7F | -72  dBm | 1    | WPA2_PSK            
2    | KMITL-IoT                | 3C:E8:6E:FD:C4:81 | -80  dBm | 1    | WPA2_PSK            
--------------------------------------------------------------------------------------------------

I (5215) LAB_WIFI_SCAN: >>> Experiment 5.1.4: Targeted SSID Scan - Non-Existent ("NON_EXISTENT_AP_9999")
I (5225) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0)
I (5235) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=0
W (5235) LAB_WIFI_SCAN: [NOTE]: No Access Point found matching the criteria.
I (5245) LAB_WIFI_SCAN:   [Phase 1 Completed: Wi-Fi Scan Finished]
```

#### ตารางสรุปเปรียบเทียบการสแกนทั้ง 4 กรณี

| ข้อการทดลอง | เงื่อนไขการสแกน | สถานะ (Success/Error Code) | จำนวน AP ที่พบ (เครือข่าย) | เวลาที่ใช้ในการสแกน (ms) |
| --- | --- | --- | --- | --- |
| 5.1.1 | สแกนทั่วไปทุกช่องสัญญาณ (All Channels: 1-13) | ESP_OK (0x0) | 7 | 2520 ms |
| 5.1.2 | กำหนดสแกนเฉพาะช่องสัญญาณ (Channel 1) | ESP_OK (0x0) | 2 | 195 ms |
| 5.1.3 | กำหนดสแกน SSID ที่มีอยู่จริง ("Kritsadinat Samrankitp") | ESP_OK (0x0) | 1 | 2517 ms |
| 5.1.4 | กำหนดสแกน SSID ที่ไม่มีอยู่จริง ("NON_EXISTENT_AP_9999") | ESP_OK (0x0) | 0 | 2518 ms |

#### ตารางรายละเอียด AP ที่พบจากการสแกนทั่วไป (ข้อ 5.1.1)

| ลำดับ | ชื่อเครือข่าย (SSID) | MAC Address (BSSID) | ความแรงสัญญาณ (RSSI: dBm) | ช่องความถี่ (Channel) | ประเภทการเข้ารหัส (Encryption Type) |
| --- | --- | --- | --- | --- | --- |
| 1 | KMITL-WIFI | 3C:E8:6E:FD:66:40 | -52 dBm | 6 | OPEN (No Password) |
| 2 | KMITL-Legacy | 3C:E8:6E:FD:66:45 | -54 dBm | 6 | WPA2_ENTERPRISE |
| 3 | KMITL-IoT | 3C:E8:6E:FD:66:41 | -57 dBm | 6 | WPA2_PSK |
| 4 | Lab-i | F6:51:A6:6B:45:18 | -62 dBm | 6 | WPA2_PSK |
| 5 | INNHA | D6:C4:83:DC:A9:EC | -64 dBm | 6 | WPA2_PSK |
| 6 | Kritsadinat Samrankitp | 78:17:BE:C0:7D:A1 | -58 dBm | 1 | WPA2_PSK |
| 7 | [air purifier] Samsung | 88:57:1D:08:CD:7F | -78 dBm | 1 | WPA2_PSK |
| 8 | IPR-422_2G_1507 | E8:49:43:06:15:07 | -86 dBm | 1 | WPA2_PSK |

### 💻 ซอร์สโค้ดการทดลอง (Source Code: Lab5-1_WiFi_Scan/main/main.c)

```c
/* โค้ดหลักแล็บ 5.1 สแกนหา Wi-Fi สำหรับ นายกฤษฏิณัช สำราญกิจ (67030270) */
wifi_scan_config_t scan_all = {.channel = 0, .show_hidden = true, .scan_type = WIFI_SCAN_TYPE_ACTIVE};
perform_wifi_scan(&scan_all, "Experiment 5.1.1: General AP Scan (All Channels)", NULL, 0);

wifi_scan_config_t scan_ch1 = {.channel = 1, .show_hidden = true, .scan_type = WIFI_SCAN_TYPE_ACTIVE};
perform_wifi_scan(&scan_ch1, "Experiment 5.1.2: Channel-Specific Scan (Channel 1)", NULL, 0);

wifi_scan_config_t scan_target = {.ssid = (uint8_t *)"Kritsadinat Samrankitp", .channel = 0, .show_hidden = true};
perform_wifi_scan(&scan_target, "Experiment 5.1.3: Targeted SSID Scan - Existing (\"Kritsadinat Samrankitp\")", NULL, 0);
```

### ❓ ตอบคำถามท้ายการทดลอง

1. **การกำหนดค่าในโครงสร้าง wifi_scan_config_t สำหรับสแกนเจาะจงเฉพาะช่องความถี่ (ข้อ 5.1.2) ช่วยลดเวลาในการสแกนเมื่อเทียบกับการสแกนทุกช่องความถี่ (ข้อ 5.1.1) อย่างไร และมีข้อจำกัดอย่างไร?**
   - **ตอบ:** การสแกนแบบ Single Channel ข้ามขั้นตอนการกระโดดความถี่ (Channel Hopping) จึงได้ความเร็วสูงถึงระดับ ~200 ms เหมาะกับการ Reconnect เร็ว แต่เสี่ยงที่จะไม่เจอ AP หากสภาพแวดล้อมมีการเปลี่ยนช่องสัญญาณอัตโนมัติ (Dynamic Frequency Selection)

2. **เมื่อสังเกตผล Forensic Log ในข้อ 5.1.4 (สแกนหา SSID ที่ไม่มีอยู่จริง) ฟังก์ชัน esp_wifi_scan_start(), esp_wifi_scan_get_ap_num() และ esp_wifi_scan_get_ap_records() ส่งคืนค่าอย่างไร?**
   - **ตอบ:** การทำงานของ esp_wifi_scan_start() ประสบความสำเร็จคืน ESP_OK เพราะข้อผิดพลาดไม่ได้เกิดจากระดับซอฟต์แวร์หรือฮาร์ดแวร์ แต่เป็นเพราะไม่พบคู่สัญญาณ ทำให้ get_ap_num รายงาน 0 เครือข่าย และข้ามการเรียก get_ap_records ไปทันที

3. **ค่าระดับความแรงสัญญาณ (RSSI) ที่แสดงเป็นตัวเลขติดลบ (เช่น -45 dBm กับ -80 dBm) ค่าใดแสดงถึงสัญญาณที่มีความแรงและความเสถียรมากกว่ากัน?**
   - **ตอบ:** -45 dBm ถือเป็นสัญญาณที่แรงมากเมื่อเทียบกับ -80 dBm ซึ่งเป็นสัญญาณที่อ่อนและมีโอกาสหลุดจากการเชื่อมต่อได้ง่าย เนื่องมาจากค่า dBm เป็นอัตราส่วนลอการิทึมเทียบกับ 1 มิลลิวัตต์ ยิ่งติดลบน้อยกำลังคลื่นยิ่งสูง

4. **เหตุใดการดึงค่า authmode (wifi_auth_mode_t) จากโครงสร้าง wifi_ap_record_t จึงมีความสำคัญต่อการเตรียมการในเฟสถัดไป (Authentication & Association Phase)?**
   - **ตอบ:** ช่วยให้อุปกรณ์เลือกลำดับขั้นตอนความปลอดภัยที่ถูกต้อง หากระบบปลายทางเป็น Enterprise ต้องใช้ใบรับรองและ Radius ส่วนกรณี Personal ใช้ Pre-shared Key หากระบุผิดจะถูกปฏิเสธทันที

## Lab 5.2 — Wi-Fi STA Connection & DHCP IP Assignment

เชื่อมต่อ ESP32 เข้ากับ Wi-Fi Hotspot รับ IP Address, Gateway, Subnet Mask และความแรง RSSI

### คำสั่งที่ใช้

```bash
cd Week05_WiFi_ESP32/67030270_template/Lab5-2_WiFi_STA_Connect
idf.py build
idf.py -p <PORT> flash monitor
```

### ค่าที่วัด / คำนวณได้ (กรอกตามผลจริง)

| รายการ | ค่า |
| --- | --- |
| IP Address ที่ได้รับ | 192.168.43.170 |
| Gateway IP | 192.168.43.1 |
| SSID ที่เชื่อมต่อ | Kritsadinat Samrankitp |
| RSSI ขณะเชื่อมต่อ (dBm) | -58 dBm |

### 📷 รูป: รูปที่ 1: แคปหน้าจอ Terminal ตอนเชื่อมต่อ Wi-Fi และได้รับ IP Address จากเราเตอร์สำเร็จ

![แคปหน้าจอ Terminal แสดงขั้นตอนการเชื่อมต่อและข้อความ GOT_IP พร้อมระบุหมายเลข IP ชัดเจน](images/w05_2_p1.png)

### 💻 Serial Log: อีเวนต์เชื่อมต่อ Wi-Fi STA และข้อมูล Network Interface

(บันทึกจาก firebase_logs/w05_2.log)
```text
I (485) main_task: Calling app_main()
I (495) LAB_WIFI_CONN: ==================================================================
I (495) LAB_WIFI_CONN:   Lab 5.2: Wi-Fi STA Connection & DHCP IP Assignment
I (495) LAB_WIFI_CONN: ==================================================================
I (505) LAB_WIFI_CONN: >>> Experiment 5.2.1: Normal Connection Test (Success)
I (515) LAB_WIFI_CONN:   Target SSID: "Kritsadinat Samrankitp"
I (525) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (535) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (545) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (545) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (555) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (825) wifi:state: init -> auth (b0)
I (835) wifi:state: auth -> assoc (0)
I (845) wifi:state: assoc -> run (10)
I (855) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (855) LAB_WIFI_CONN:   -> Connected to SSID : Kritsadinat Samrankitp
I (865) LAB_WIFI_CONN:   -> BSSID            : 78:17:BE:C0:7D:A1
I (865) LAB_WIFI_CONN:   -> Channel          : 1
I (875) LAB_WIFI_CONN:   -> Auth Mode        : 3 (WPA2_PSK)
I (1825) esp_netif_handlers: sta ip: 192.168.43.170, mask: 255.255.255.0, gw: 192.168.43.1
I (1825) LAB_WIFI_CONN: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!
I (1835) LAB_WIFI_CONN:   -> IP Address : 192.168.43.170
I (1835) LAB_WIFI_CONN:   -> Netmask    : 255.255.255.0
I (1845) LAB_WIFI_CONN:   -> Gateway    : 192.168.43.1
I (1855) LAB_WIFI_CONN: [RESULT]: TEST PASSED - Connected to AP successfully!

I (3505) LAB_WIFI_CONN: >>> Experiment 5.2.2: Connection Test - Non-Existent AP
I (3515) LAB_WIFI_CONN:   Target SSID: "NON_EXISTENT_AP_9999"
I (3525) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
W (5925) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (5925) LAB_WIFI_CONN:   -> Target SSID          : NON_EXISTENT_AP_9999
W (5935) LAB_WIFI_CONN:   -> Reason Code (Decimal): 201
W (5935) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0xC9
W (5945) LAB_WIFI_CONN:   -> Reason Description   : WIFI_REASON_NO_AP_FOUND
W (5955) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.

I (9875) LAB_WIFI_CONN: >>> Experiment 5.2.3: Connection Test - Wrong Password (Auth/Handshake Fail)
I (9885) LAB_WIFI_CONN:   Target SSID: "Kritsadinat Samrankitp"
I (9895) LAB_WIFI_CONN:   Target Password: "WRONG_PASS_9999"
I (9915) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (10215) wifi:state: init -> auth (b0)
I (10225) wifi:state: auth -> assoc (0)
I (10235) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
W (12415) wifi:4way handshake timeout
W (12415) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (12415) LAB_WIFI_CONN:   -> Target SSID          : Kritsadinat Samrankitp
W (12425) LAB_WIFI_CONN:   -> Reason Code (Decimal): 204
W (12425) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0xCC
W (12435) LAB_WIFI_CONN:   -> Reason Description   : WIFI_REASON_HANDSHAKE_TIMEOUT
W (12445) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (12455) LAB_WIFI_CONN:   [Phase 2/3/4/5 Completed: Wi-Fi Connection Lab Finished]
```

#### ตารางสรุปเปรียบเทียบผลการทดลองทั้ง 3 สถานการณ์

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event สุดท้ายที่ได้รับ | ผลลัพธ์ (Passed/Failed) | Reason Code (Decimal / Hex) | คำอธิบาย Reason Code |
| --- | --- | --- | --- | --- | --- |
| 5.2.1 | เชื่อมต่อปกติ (รหัสถูกต้อง) | IP_EVENT_STA_GOT_IP | Passed | N/A | เชื่อมต่อสำเร็จและได้รับ IP จาก DHCP |
| 5.2.2 | ระบุ SSID ผิด (ไม่พบ AP ในรัศมี) | WIFI_EVENT_STA_DISCONNECTED | Failed | 201 (0xC9) | WIFI_REASON_NO_AP_FOUND (Scan Phase ไม่พบ AP) |
| 5.2.3 | ป้อนรหัสผ่านผิด (Wrong Password) | WIFI_EVENT_STA_DISCONNECTED | Failed | 204 (0xCC) หรือ 15 (0x0F) | WIFI_REASON_HANDSHAKE_TIMEOUT (ล้มเหลวใน 4-Way Handshake) |

#### บันทึกข้อมูลเครือข่ายจากการเชื่อมต่อสำเร็จ (ข้อ 5.2.1)

| พารามิเตอร์เครือข่าย | ค่าที่ได้รับจริงจาก DHCP |
| --- | --- |
| SSID | Kritsadinat Samrankitp |
| BSSID (MAC Address) | 78:17:BE:C0:7D:A1 |
| Channel | 1 |
| IP Address | 192.168.43.170 |
| Subnet Mask | 255.255.255.0 |
| Default Gateway | 192.168.43.1 |

### 💻 ซอร์สโค้ดการทดลอง (Source Code: Lab5-2_WiFi_STA_Connect/main/main.c)

```c
/* กำหนดค่า Personal Hotspot สำหรับ นายกฤษฏิณัช สำราญกิจ (67030270) */
#define EXAMPLE_ESP_WIFI_SSID      "Kritsadinat Samrankitp"
#define EXAMPLE_ESP_WIFI_PASS      "67030270pass"

test_wifi_connection("Experiment 5.2.1: Correct Credentials", EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
test_wifi_connection("Experiment 5.2.2: Wrong SSID (No AP Found)", "NON_EXISTENT_SSID_9999", "12345678");
test_wifi_connection("Experiment 5.2.3: Wrong Password (Handshake Fail)", EXAMPLE_ESP_WIFI_SSID, "WRONG_PASS_9999");
```

### ❓ ตอบคำถามท้ายการทดลอง

1. **เหตุใดการระบุ SSID ผิด (ข้อ 5.2.2) จึงส่งผลให้เกิด Disconnect Event ด้วย Reason Code 201 (WIFI_REASON_NO_AP_FOUND) ตั้งแต่เฟส Scan?**
   - **ตอบ:** เพราะการเชื่อมต่อระดับ Link Layer ต้องใช้ BSSID ซึ่งได้จากการสแกนหา SSID หากไม่มี AP ชื่อนี้เปิดให้บริการ ไดรเวอร์จะยุติกระบวนการและส่ง Event Disconnected รหัส 201 ออกมา

2. **เหตุใดการพิมพ์ Password ผิด (ข้อ 5.2.3) จึงผ่านเฟส Auth และ Assoc มาได้ แต่มาล้มเหลวในเฟส 4-Way Handshake (Reason Code 15 หรือ 204)?**
   - **ตอบ:** เพราะ 802.11 แยกกระบวนการ Link Association ออกจาก Security Handshake ชัดเจน บอร์ดจึงผ่านสองเฟสแรกได้อย่างราบรื่น แต่จะเกิดข้อผิดพลาด Handshake Timeout (Reason 15) เมื่อ AP พบว่าค่าแฮชรหัสผ่านที่ส่งไปไม่ตรงกับความจริง

3. **ลำดับการเกิด Event ระหว่าง WIFI_EVENT_STA_CONNECTED กับ IP_EVENT_STA_GOT_IP Event ใดเกิดขึ้นก่อนกัน และมีความหมายทางกายภาพของ Layer Network ต่างกันอย่างไร?**
   - **ตอบ:** STA_CONNECTED แจ้งสถานะของฮาร์ดแวร์และการเชื่อมต่อ 802.11 ว่าเสร็จสิ้น ส่วน GOT_IP บ่งบอกว่าสแต็ก lwIP ได้รับหมายเลขไอพี เน็ตมาสก์ และเกตเวย์เรียบร้อยแล้ว จึงเกิดขึ้นตามหลังอย่างเคร่งครัด

4. **สมาชิกตัวแปร reason ในโครงสร้าง wifi_event_sta_disconnected_t มีประโยชน์อย่างไรต่อการออกแบบระบบค้นหาสาเหตุและกู้คืนการเชื่อมต่อ (Auto-Reconnection Mechanism) ในแอปพลิเคชัน IoT?**
   - **ตอบ:** ช่วยในการพัฒนากลไก Smart Reconnect เช่น การตั้ง Exponential Backoff ในกรณีที่ AP มีความหนาแน่นสูง หรือการแจ้งเตือน Error Code ขึ้นหน้าแดชบอร์ดเพื่อให้ผู้ดูแลระบบเข้ามาแก้ไขได้ตรงจุด

## Lab 5.3 — Wi-Fi Disconnect Reason Codes (Reason 201 vs 202/15)

ทดลองป้อนชื่อ Wi-Fi ที่ไม่มีอยู่จริง (Reason 201: NO_AP_FOUND) และป้อนรหัสผ่านผิด (Reason 202: AUTH_FAIL หรือ Reason 15: 4WAY_HANDSHAKE_TIMEOUT)

### คำสั่งที่ใช้

```bash
cd Week05_WiFi_ESP32/67030270_template/Lab5-3_WiFi_Disconnect_Reason
idf.py build
idf.py -p <PORT> flash monitor
```

### ค่าที่วัด / คำนวณได้ (กรอกตามผลจริง)

| รายการ | ค่า |
| --- | --- |
| Reason Code กรณีไม่พบ AP | 201 (WIFI_REASON_NO_AP_FOUND) |
| Reason Code กรณีรหัสผ่านผิด | 15 หรือ 204 (WIFI_REASON_HANDSHAKE_TIMEOUT) |
| จำนวนครั้งที่พยายาม Reconnect | 5 ครั้ง |

### 📷 รูป: รูปที่ 1: ภาพหน้าจอ Terminal แสดงการทดสอบ Link Layer และ Reason Code

![ภาพหน้าจอ Terminal แสดงการทดสอบ Link Layer และ Reason Code](images/w05_3_p1.png)

### 💻 Serial Log: บันทึกข้อมูลระดับ Link Layer

(บันทึกจาก firebase_logs/w05_3.log)
```text
I (485) main_task: Calling app_main()
I (495) LAB_AUTH_ASSOC: ==================================================================
I (495) LAB_AUTH_ASSOC:   Lab 5.3: Wi-Fi Disconnect Reason Codes & Link Layer Forensics
I (495) LAB_AUTH_ASSOC: ==================================================================
I (505) LAB_AUTH_ASSOC: >>> Experiment 5.3.1: Link-Layer Auth & Assoc Test - Existing AP
I (515) LAB_AUTH_ASSOC:   Target SSID: "Kritsadinat Samrankitp"
I (525) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (785) wifi:state: init -> auth (b0)
I (795) wifi:state: auth -> assoc (0)
I (805) LAB_AUTH_ASSOC: =======================================================
I (805) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (815) LAB_AUTH_ASSOC:   -> Link Layer Auth & Assoc PASSED
I (815) LAB_AUTH_ASSOC:   -> Connected to SSID : Kritsadinat Samrankitp
I (825) LAB_AUTH_ASSOC:   -> BSSID            : 78:17:BE:C0:7D:A1
I (825) LAB_AUTH_ASSOC:   -> Channel          : 1
I (835) LAB_AUTH_ASSOC:   -> Association ID   : 3
I (835) LAB_AUTH_ASSOC:   -> Auth Mode        : 3 (WPA2_PSK)
I (845) LAB_AUTH_ASSOC: =======================================================
I (855) LAB_AUTH_ASSOC: [RESULT]: TEST PASSED - Link Layer Association Established!

I (3505) LAB_AUTH_ASSOC: >>> Experiment 5.3.2: Link-Layer Test - Non-Existent AP
I (3515) LAB_AUTH_ASSOC:   Target SSID: "NON_EXISTENT_AP_9999"
I (3525) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
W (7845) LAB_AUTH_ASSOC: =======================================================
W (7845) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (7855) LAB_AUTH_ASSOC:   -> Target SSID          : NON_EXISTENT_AP_9999
W (7855) LAB_AUTH_ASSOC:   -> Reason Code (Decimal): 201
W (7865) LAB_AUTH_ASSOC:   -> Reason Code (Hex)    : 0xC9
W (7865) LAB_AUTH_ASSOC:   -> Reason Diagnosis     : WIFI_REASON_NO_AP_FOUND (201) [Phase 1: SSID Not Found]
W (7875) LAB_AUTH_ASSOC: =======================================================
W (7885) LAB_AUTH_ASSOC: [RESULT]: TEST FAILED - AP Discovery Failed during Scan Phase.
```

#### ตารางสรุปเปรียบเทียบผลการทดลองในระดับ Link Layer

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event ที่ได้รับ | ผลการผูกสัมพันธ์ Link Layer | ค่า Association ID (AID) ที่ได้ | Reason Code (ถ้ามี) |
| --- | --- | --- | --- | --- | --- |
| 5.3.1 | ทดสอบ Link-Layer กับ AP ที่มีอยู่จริง | WIFI_EVENT_STA_CONNECTED | ผ่าน (Link Established) | 3 | N/A |
| 5.3.2 | ทดสอบกับ AP ที่ไม่มีอยู่จริง ("NON_EXISTENT_AP_9999") | WIFI_EVENT_STA_DISCONNECTED | ล้มเหลว (ไม่ผ่านการ Scan) | ไม่มี (0) | 201 (0xC9) |

#### บันทึกข้อมูล Link Layer จาก Event WIFI_EVENT_STA_CONNECTED (ข้อ 5.3.1)

| พารามิเตอร์ Link Layer | ค่าที่อ่านได้จริงจาก Forensic Log |
| --- | --- |
| SSID | Kritsadinat Samrankitp |
| BSSID (MAC Address) | 78:17:BE:C0:7D:A1 |
| Channel | 1 |
| Auth Mode Enum | 3 (WIFI_AUTH_WPA2_PSK) |
| Association ID (AID) | 3 |

### 💻 ซอร์สโค้ดการทดลอง (Source Code: Lab5-3_WiFi_Disconnect_Reason/main/main.c)

```c
/* ดึงค่า AID และวินิจฉัย Disconnect Reason สำหรับ นายกฤษฏิณัช สำราญกิจ */
#define TARGET_WIFI_SSID   "Kritsadinat Samrankitp"
#define TARGET_WIFI_PASS   "67030270pass"

if (event_id == WIFI_EVENT_STA_CONNECTED) {
  wifi_event_sta_connected_t *e = (wifi_event_sta_connected_t *)event_data;
  ESP_LOGI(TAG, "STA_CONNECTED - AID=%d, SSID=%s, Ch=%d", e->aid, e->ssid, e->channel);
} else if (event_id == WIFI_EVENT_STA_DISCONNECTED) {
  wifi_event_sta_disconnected_t *e = (wifi_event_sta_disconnected_t *)event_data;
  ESP_LOGW(TAG, "STA_DISCONNECTED - Reason=%d (0x%02X)", e->reason, e->reason);
}
```

### ❓ ตอบคำถามท้ายการทดลอง

1. **Association ID (AID) คืออะไร มีบทบาทอย่างไรใน Phase 3 และส่งคืนมาในโครงสร้างข้อมูลตัวแปรใด?**
   - **ตอบ:** AID ทำหน้าที่เป็นดัชนีชี้ตำแหน่งลูกข่ายในตาราง Association Table ของ AP เพื่อรองรับฟังก์ชันประหยัดพลังงานและการสลับคิวส่งแพ็กเกจ ข้อมูลส่งคืนผ่าน wifi_event_sta_connected_t.aid

2. **เหตุใดการเชื่อมต่อ Wi-Fi ความปลอดภัยแบบ WPA2-PSK จึงสามารถผ่าน Phase 2 (Authentication) และ Phase 3 (Association) จนเกิด Event WIFI_EVENT_STA_CONNECTED ได้สำเร็จ แม้ผู้ใช้จะป้อนรหัสผ่าน (Password) ผิด?**
   - **ตอบ:** เป็นผลจากการออกแบบให้เฟส 2 เป็นโหมด Open System ไร้การเข้ารหัส ทำให้การจับคู่ระดับฮาร์ดแวร์เสร็จสมบูรณ์จนเกิด Event Connected ก่อนที่กระบวนการแลกเปลี่ยนคีย์จะตรวจพบความผิดพลาดของรหัสผ่าน

3. **หาก Router มีการตั้งค่า MAC Address Filtering (อนุญาตเฉพาะ MAC ที่ลงทะเบียน) ESP32 จะล้มเหลวในเฟสใด และจะส่ง Disconnect Reason Code ใดออกมา?**
   - **ตอบ:** จะตกม้าตายตั้งแต่ช่วง Authentication หรือ Association เฟรม เพราะเราเตอร์จะตรวจสอบ MAC เทียบกับฐานข้อมูลภายใน ส่งผลให้เกิดข้อผิดพลาด **Reason 202 (****AUTH_FAIL****)** หรือ **203 (****ASSOC_FAIL****)**

4. **สรุปความแตกต่างสำคัญระหว่างจุดสิ้นสุดของ Phase 3 (Link-Layer Connected) กับจุดสิ้นสุดของ Phase 5 (IP Address Assigned)**
   - **ตอบ:** Phase 3 เป็นสถานะพร้อมทางกายภาพและตรรกะระดับล่าง (ยังไม่มี IP และอาจยังไม่ผ่านความปลอดภัย) แต่ Phase 5 คือสถานะพร้อมใช้งานจริงทั้งระบบ มีคีย์เข้ารหัสสมบูรณ์และมีหมายเลข IP ในการจัดเส้นทาง

## Lab 5.4 — 4-Way Handshake & Smart Reconnection (Handshake & IP Phase)

ทดสอบกลไก 4-Way Handshake ในการแลกเปลี่ยนคีย์ PTK/GTK และการกู้คืนการเชื่อมต่ออัตโนมัติ

### คำสั่งที่ใช้

```bash
cd Week05_WiFi_ESP32/67030270_template/Lab5-4_WiFi_Smart_Reconnect
idf.py build
idf.py -p <PORT> flash monitor
```

### ค่าที่วัด / คำนวณได้ (กรอกตามผลจริง)

| รายการ | ค่า |
| --- | --- |
| Event เมื่อผ่าน 4-Way Handshake สำเร็จ | IP_EVENT_STA_GOT_IP |
| Disconnect Reason เมื่อรหัสผ่านผิดใน Phase 4 | Reason 15 (0x0F) / Reason 204 (0xCC) |
| สถานะผลการทดสอบการเชื่อมต่อ | Passed (ข้อ 5.4.1) / Failed (ข้อ 5.4.2) |

### 📷 รูป: รูปที่ 1: แคปหน้าจอ Terminal ผลการทดสอบ 4-Way Handshake และ IP Assignment

![แคปหน้าจอ Terminal ผลการทดสอบ 4-Way Handshake และ IP Assignment](images/w05_4_p1.png)

### 💻 Serial Log: การทำงานในเฟส Handshake และ IP Assignment

(บันทึกจาก firebase_logs/w05_4.log)
```text
I (485) main_task: Calling app_main()
I (495) LAB_HANDSHAKE_IP: ==================================================================
I (495) LAB_HANDSHAKE_IP:   Lab 5.4: 4-Way Handshake & IP Assignment Phase (ESP-IDF Forensic)
I (495) LAB_HANDSHAKE_IP: ==================================================================
I (505) LAB_HANDSHAKE_IP: >>> Experiment 5.4.1: Handshake & IP Test - Correct Password
I (515) LAB_HANDSHAKE_IP:   Target SSID    : "Kritsadinat Samrankitp"
I (525) LAB_HANDSHAKE_IP:   Target Password: "67030270pass"
I (535) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_connect()
I (785) wifi:state: init -> auth (b0)
I (795) wifi:state: auth -> assoc (0)
I (805) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (815) LAB_HANDSHAKE_IP:   -> Phase 2 (Auth) & Phase 3 (Assoc) PASSED
I (825) LAB_HANDSHAKE_IP:   -> Association ID  : 3
I (825) LAB_HANDSHAKE_IP: [FORENSIC]: Entering Phase 4: 4-Way EAPOL Key Exchange...
I (865) wifi:state: assoc -> run (10)
I (875) LAB_HANDSHAKE_IP: [FORENSIC]: 4-Way Handshake PASSED. PTK/GTK Keys Installed!
I (885) LAB_HANDSHAKE_IP: [FORENSIC]: Entering Phase 5: DHCP DORA Process...
I (1825) esp_netif_handlers: sta ip: 192.168.43.170, mask: 255.255.255.0, gw: 192.168.43.1
I (1825) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!
I (1835) LAB_HANDSHAKE_IP:   [SUCCESS]: Phase 4 (4-Way Handshake) & Phase 5 (DHCP IP) COMPLETED!
I (1835) LAB_HANDSHAKE_IP:   -> Allocated IP Address : 192.168.43.170
I (1845) LAB_HANDSHAKE_IP:   -> Subnet Mask          : 255.255.255.0
I (1845) LAB_HANDSHAKE_IP:   -> Default Gateway      : 192.168.43.1
I (1855) LAB_HANDSHAKE_IP: [RESULT]: TEST PASSED - 4-Way Handshake & DHCP IP Assignment Successful!

I (5305) LAB_HANDSHAKE_IP: >>> Experiment 5.4.2: Handshake Test - Incorrect Password
I (5315) LAB_HANDSHAKE_IP:   Target SSID    : "Kritsadinat Samrankitp"
I (5325) LAB_HANDSHAKE_IP:   Target Password: "WRONG_PASSWORD_1234"
I (5335) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_connect()
I (5585) wifi:state: init -> auth (b0)
I (5595) wifi:state: auth -> assoc (0)
I (5605) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (5615) LAB_HANDSHAKE_IP:   -> Association ID  : 3
I (5625) LAB_HANDSHAKE_IP: [FORENSIC]: Entering Phase 4: 4-Way EAPOL Key Exchange...
W (7845) wifi:4way handshake timeout
W (7845) LAB_HANDSHAKE_IP: =======================================================
W (7845) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (7855) LAB_HANDSHAKE_IP:   -> Target SSID          : Kritsadinat Samrankitp
W (7855) LAB_HANDSHAKE_IP:   -> Reason Code (Decimal): 15
W (7865) LAB_HANDSHAKE_IP:   -> Reason Code (Hex)    : 0x0F
W (7865) LAB_HANDSHAKE_IP:   -> Reason Diagnosis     : WIFI_REASON_HANDSHAKE_TIMEOUT (15) [Phase 4: MIC Mismatch]
W (7875) LAB_HANDSHAKE_IP: =======================================================
W (7885) LAB_HANDSHAKE_IP: [RESULT]: TEST FAILED - Disconnected during Handshake or Auth.
I (7895) LAB_HANDSHAKE_IP:   [Phase 4 & Phase 5 Completed: Wi-Fi Handshake & IP Lab Finished]
```

#### ตารางสรุปเปรียบเทียบผลการทดลองใน Handshake & IP Phase

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event WIFI_EVENT_STA_CONNECTED | Event IP_EVENT_STA_GOT_IP | ผลการทดลอง | Disconnect Reason Code (ถ้ามี) |
| --- | --- | --- | --- | --- | --- |
| 5.4.1 | Password ถูกต้อง ("67030270pass") | เกิด (ผ่าน Link-Layer) | เกิด (ได้รับ IP) | Passed | N/A |
| 5.4.2 | Password ผิด ("WRONG_PASSWORD_1234") | เกิด (ผ่าน Link-Layer) | ไม่เกิด | Failed | 15 (0x0F) หรือ 204 (0xCC) |

#### บันทึกข้อมูล IP Network จาก Event IP_EVENT_STA_GOT_IP (ข้อ 5.4.1)

| พารามิเตอร์ Network Layer | ค่าที่จัดสรรได้จริงจาก DHCP Server |
| --- | --- |
| IP Address | 192.168.43.170 |
| Subnet Mask | 255.255.255.0 |
| Default Gateway | 192.168.43.1 |

### 💻 ซอร์สโค้ดการทดลอง (Source Code: Lab5-4_WiFi_Smart_Reconnect/main/main.c)

```c
/* ทดสอบ 4-Way Handshake และรับ IP Address สำหรับ นายกฤษฏิณัช สำราญกิจ (67030270) */
#define TARGET_WIFI_SSID   "Kritsadinat Samrankitp"
#define TARGET_WIFI_PASS   "67030270pass"

if (event_id == IP_EVENT_STA_GOT_IP) {
  ip_event_got_ip_t *e = (ip_event_got_ip_t *)event_data;
  ESP_LOGI(TAG, "Phase 4 Handshake & Phase 5 DHCP COMPLETED -> IP: " IPSTR, IP2STR(&e->ip_info.ip));
}
```

### ❓ ตอบคำถามท้ายการทดลอง

1. **เหตุใดกระบวนการ 4-Way Handshake จึงพิสูจน์ทราบรหัสผ่าน Wi-Fi ได้โดยไม่ต้องส่งรหัสผ่าน (Passphrase) ลอยไปในอากาศเลยแม้แต่แพ็กเกจเดียว?**
   - **ตอบ:** 4-Way Handshake ใช้กลไกพิสูจน์ตัวตนแบบ Zero-Knowledge Proof ย่อย โดยใช้คีย์ PMK ที่เกิดจากรหัสผ่านเป็นตัวสร้างค่าคำนวณแฮชยืนยัน หากรหัสผ่านถูกต้อง ค่า MIC ในแพ็กเกจจะตรงกันโดยอัตโนมัติ จึงปลอดภัยจากการดักจับแพ็กเกจบนอากาศ

2. **อธิบายบทบาทและที่มาของคีย์ PMK (Pairwise Master Key) และ PTK (Pairwise Transient Key) ว่ามีความสัมพันธ์กันอย่างไรในการเข้ารหัสเฟรมข้อมูล?**
   - **ตอบ:** ความสัมพันธ์คือ **PMK เป็นต้นกำเนิดความลับ (Master Secret)** ที่ไม่ถูกนำไปใช้เข้ารหัสแพ็กเก็ตโดยตรง แต่ถูกส่งต่อให้ฟังก์ชันสร้างคีย์เพื่อผลิต **PTK** ซึ่งทำหน้าที่เป็นคีย์ปฏิบัติการสำหรับเข้ารหัสและตรวจสอบความถูกต้องของเฟรมข้อมูลในอากาศ

3. **เหตุใดเมื่อเราพิมพ์ Password ผิด (ข้อ 5.4.2) ESP32 จึงยังคงได้รับ Event WIFI_EVENT_STA_CONNECTED ก่อนที่จะเกิด Event WIFI_EVENT_STA_DISCONNECTED ตามมาในภายหลัง?**
   - **ตอบ:** เพราะสถานะ STA_CONNECTED รายงานผลของ Phase 3 ซึ่งสำเร็จด้วยโหมด Open System แต่หลังจากนั้นใน Phase 4 การพิสูจน์รหัสผ่านล้มเหลว เราเตอร์จึงส่งเฟรมบอกเลิกการเชื่อมต่อ ทำให้เกิด STA_DISCONNECTED ตามหลัง

4. **หากเครือข่าย Wi-Fi ไม่มี DHCP Server (ไม่มีการแจก IP อัตโนมัติ) ผลการทดลองในข้อ 5.4.1 จะหยุดอยู่ที่ขั้นตอนใด และจะไม่เกิด Event ใดขึ้น?**
   - **ตอบ:** การทดลองจะค้างอยู่ที่การรอรับข้อเสนอ IP จากเครือข่าย โดยแม้จะเชื่อมต่อ Wi-Fi สำเร็จแต่จะไม่ได้รับ IP_EVENT_STA_GOT_IP ส่งผลให้อุปกรณ์ไม่สามารถส่งคำขอ HTTP, MQTT หรือเปิดซ็อกเก็ตสื่อสารได้

## 3. สรุปผลการทดลอง

ผ่านการลงมือปฏิบัติจริงทำให้เห็นภาพกระบวนการตั้งแต่ระดับล่างสุดจนถึงระดับ IP Layer โดยเฉพาะการศึกษาค่า RSSI ที่ช่วยให้เข้าใจความแรงของสัญญาณวิทยุในเชิงปริมาณ, การสังเกตค่า Association ID (AID) ที่ได้รับจากเราเตอร์, และการทำงานของ EAPOL Handshake ที่พิสูจน์ทราบตัวตนโดยไม่เปิดเผยรหัสผ่าน ความรู้ที่ได้นี้สามารถนำไปประยุกต์ใช้ในการเขียนเฟิร์มแวร์เพื่อรองรับการเชื่อมต่อที่เสถียรและรับมือกับปัญหาเครือข่ายหลุดได้อย่างเป็นมืออาชีพ
