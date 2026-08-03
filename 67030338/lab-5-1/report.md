### ใบงานที่ 5.1: การเชื่อมต่อ Wi-Fi และการค้นหาสัญญาณรอบข้าง (Wi-Fi Connection and Scanning)

```
I (799) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (799) LAB_WIFI_SCAN: ==================================================================
I (799) LAB_WIFI_SCAN:   Lab 5.1: Wi-Fi Connection and Scanning Phase (ESP-IDF Forensic)
I (809) LAB_WIFI_SCAN: ==================================================================
I (819) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (829) LAB_WIFI_SCAN: >>> Experiment 5.1.1: General AP Scan (All Channels)
I (829) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (839) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (3349) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2495 ms]
I (3349) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (3349) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=8
I (3359) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (3359) LAB_WIFI_SCAN: [AP COUNT]: 8 network(s) found
I (3369) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (3379) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=8

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | KMITL-Legacy             | 78:17:BE:C0:7D:A0 | -53  dBm | 1    | WPA2_ENTERPRISE     
2    | KMITL-WIFI               | 78:17:BE:C0:7D:A1 | -53  dBm | 1    | OPEN (No Password)  
3    | KMITL-IoT                | 78:17:BE:C0:7D:A2 | -53  dBm | 1    | WPA2_PSK            
4    | Test-WiFi                | 0A:8A:B4:BB:12:61 | -65  dBm | 6    | WPA2_WPA3_PSK       
5    | FUB                      | EA:67:85:97:BF:39 | -67  dBm | 10   | WPA2_PSK            
6    | PhuwishP                 | 82:CA:F7:29:29:6C | -71  dBm | 1    | WPA2_PSK            
7    | Redmi Note 10S           | 66:34:B4:F7:03:8A | -72  dBm | 5    | WPA2_PSK            
8    | KMITL-IoT                | 78:17:BE:A9:94:E2 | -85  dBm | 6    | WPA2_PSK            
--------------------------------------------------------------------------------------------------

I (4479) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (4479) LAB_WIFI_SCAN: >>> Experiment 5.1.2: Channel-Specific Scan (Channel 1)
I (4479) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (4489) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (4699) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 200 ms]
I (4699) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (4699) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=7
I (4709) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (4709) LAB_WIFI_SCAN: [AP COUNT]: 7 network(s) found
I (4719) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (4729) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=7

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | KMITL-Legacy             | 78:17:BE:C0:7D:A0 | -49  dBm | 1    | WPA2_ENTERPRISE     
2    | KMITL-IoT                | 78:17:BE:C0:7D:A2 | -49  dBm | 1    | WPA2_PSK            
3    | KMITL-WIFI               | 78:17:BE:C0:7D:A1 | -54  dBm | 1    | OPEN (No Password)  
4    | PhuwishP                 | 82:CA:F7:29:29:6C | -72  dBm | 1    | WPA2_PSK            
5    | KMITL-Legacy             | 78:17:BE:C0:66:20 | -79  dBm | 1    | WPA2_ENTERPRISE     
6    | KMITL-IoT                | 78:17:BE:C0:66:22 | -80  dBm | 1    | WPA2_PSK            
7    | KMITL-WIFI               | 78:17:BE:C0:66:21 | -85  dBm | 1    | OPEN (No Password)  
--------------------------------------------------------------------------------------------------

I (5829) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (5829) LAB_WIFI_SCAN: >>> Experiment 5.1.3: Targeted SSID Scan - Existing ("KMITL-Legacy")
I (5829) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (5839) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (8349) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2499 ms]
I (8349) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (8349) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=2
I (8359) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (8359) LAB_WIFI_SCAN: [AP COUNT]: 2 network(s) found
I (8369) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (8379) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=2

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | KMITL-Legacy             | 78:17:BE:C0:7D:A0 | -49  dBm | 1    | WPA2_ENTERPRISE     
2    | KMITL-Legacy             | 78:17:BE:C0:72:60 | -84  dBm | 11   | WPA2_ENTERPRISE     
--------------------------------------------------------------------------------------------------

I (9439) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (9439) LAB_WIFI_SCAN: >>> Experiment 5.1.4: Targeted SSID Scan - Non-Existent ("NON_EXISTENT_AP_9999")
I (9439) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (9449) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (11959) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 2498 ms]
I (11959) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (11959) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=0
I (11969) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (11969) LAB_WIFI_SCAN: [AP COUNT]: 0 network(s) found
W (11979) LAB_WIFI_SCAN: [NOTE]: No Access Point found matching the criteria.
I (11979) LAB_WIFI_SCAN: ==================================================================
I (11989) LAB_WIFI_SCAN:   [Phase 1 Completed: Wi-Fi Scan Finished]
I (11999) LAB_WIFI_SCAN:   Program stopped after scanning. Auth/Assoc Phase not started.
I (12009) LAB_WIFI_SCAN: ==================================================================
I (12009) main_task: Returned from app_main()
```

## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบการสแกนทั้ง 4 กรณี

| ข้อการทดลอง | เงื่อนไขการสแกน             | สถานะ (Success/Error Code) | จำนวน AP ที่พบ (เครือข่าย) | เวลาที่ใช้ในการสแกน (ms) |
| :---------: | :-------------------------- | :------------------------: | :------------------------: | :----------------------: |
|  **5.1.1**  | สแกนทั่วไปทุก Channel       |   Success (ESP_OK / 0x0)   |             8              |           2495           |
|  **5.1.2**  | กำหนดสแกนเฉพาะ Channel 1    |   Success (ESP_OK / 0x0)   |             7              |           200            |
|  **5.1.3**  | กำหนดสแกน SSID ที่มีจริง    |   Success (ESP_OK / 0x0)   |             2              |           2499           |
|  **5.1.4**  | กำหนดสแกน SSID ที่ไม่มีจริง |   Success (ESP_OK / 0x0)   |             0              |           2498           |

### 6.2 ตารางรายละเอียด AP ที่พบจากการสแกนทั่วไป (ข้อ 5.1.1)

| ลำดับ | ชื่อเครือข่าย (SSID) | MAC Address (BSSID) | ความแรงสัญญาณ (RSSI: dBm) | ช่องความถี่ (Channel) | ประเภทการเข้ารหัส (Encryption Type) |
| :---: | :------------------- | :------------------ | :-----------------------: | :-------------------: | :---------------------------------- |
|   1   | `<Hidden SSID>`      | A6:AE:BD:24:7B:30   |         -66  dBm          |           6           | WPA2_PSK                            |
|   2   | 😑                   | 62:DD:AB:3C:2D:A6   |         -67  dBm          |          11           | WPA2_PSK                            |
|   3   | Redmi Note 10S       | 66:34:B4:F7:03:8A   |       -71  dBm <br>       |           5           | WPA2_PSK                            |
|   4   | KMITL-IoT            | 78:17:BE:C0:72:62   |         -75  dBm          |          11           | WPA2_PSK                            |
|   5   | KMITL-Legacy         | 78:17:BE:C0:72:60   |         -77  dBm          |          11           | WPA2_ENTERPRISE                     |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. การกำหนดค่าในโครงสร้าง `wifi_scan_config_t` สำหรับสแกนเจาะจงเฉพาะช่องความถี่ (ข้อ 5.1.2) ช่วยลดเวลาในการสแกนเมื่อเทียบกับการสแกนทุกช่องความถี่ (ข้อ 5.1.1) อย่างไร และมีข้อจำกัดอย่างไร?
Ans  
	- **การลดเวลา:** ช่วยลดเวลาได้อย่างมากเนื่องจาก ESP32 ไม่ต้องเสียเวลาเปลี่ยนความถี่ (Channel Hop) และส่ง Probe Request ครบทั้ง 11–13 ช่องความถี่ สแกนเพียงช่องเดียวจึงใช้เวลาสั้นลงเหลือเพียงแค่หลักร้อย millisecond
    
	- **ข้อจำกัด:** จะไม่พบ AP/Wi-Fi ที่ปล่อยสัญญาณอยู่ในช่องความถี่อื่น (Channel อื่นๆ จะถูกมองข้ามทั้งหมด)
2. เมื่อสังเกตผล Forensic Log ในข้อ 5.1.4 (สแกนหา SSID ที่ไม่มีอยู่จริง) ฟังก์ชัน `esp_wifi_scan_start()`, `esp_wifi_scan_get_ap_num()` และ `esp_wifi_scan_get_ap_records()` ส่งคืนค่าอย่างไร?
Ans
		- `esp_wifi_scan_start()` ส่งคืน `ESP_OK (0x0)` (กระบวนการสแกนสำเร็จปกติ)
    
		- `esp_wifi_scan_get_ap_num()` ส่งคืน `ESP_OK (0x0)` โดยค่า `ap_count` จะได้ **0**
    
		- `esp_wifi_scan_get_ap_records()` ส่งคืน `ESP_OK (0x0)` โดยดึงข้อมูลออกมาได้ **0 records**
3. ค่าระดับความแรงสัญญาณ (RSSI) ที่แสดงเป็นตัวเลขติดลบ (เช่น -45 dBm กับ -80 dBm) ค่าใดแสดงถึงสัญญาณที่มีความแรงและความเสถียรมากกว่ากัน?
Ans
	- ค่า **-45 dBm** มีความแรงและความเสถียรมากกว่า **-80 dBm**
    
	- **เหตุผล:** RSSI เป็นค่าลบ ยิ่งเข้าใกล้ 0 มากเท่าไร แสดงว่าสัญญาณยิ่งแรงและมีคุณภาพดีเท่านั้น (ค่า -80 dBm ถือว่าสัญญาณจางมากและอาจหลุดได้ง่าย)
4. เหตุใดการดึงค่า `authmode` (`wifi_auth_mode_t`) จากโครงสร้าง `wifi_ap_record_t` จึงมีความสำคัญต่อการเตรียมการในเฟสถัดไป (Authentication & Association Phase)?
Ans
	เพื่อให้ ESP32 รู้ล่วงหน้าว่า AP เป้าหมายใช้รูปแบบความปลอดภัยประเภทใด (เช่น Open, WPA2-Personal, WPA2-Enterprise) จะได้เตรียมขั้นตอน Handshake, อัลกอริทึมเข้ารหัส (AES/TKIP) และส่งค่า Credentials (Password/Identity) ในเฟส Authentication & Association ได้ถูกต้องตรงตามข้อกำหนดของ AP นั้นๆ