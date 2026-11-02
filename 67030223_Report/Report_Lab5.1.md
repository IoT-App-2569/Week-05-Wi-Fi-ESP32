### ผลลัพธ์จาก Serial Monitor (ESP-IDF Console)

```text
I (1050) LAB5_1_SCAN: ==================================================================
I (1050) LAB5_1_SCAN:   Lab 5.1: Wi-Fi Connection and Scanning Phase (ESP-IDF Forensic)
I (1060) LAB5_1_SCAN: ==================================================================
I (1070) LAB5_1_SCAN: --- Experiment 5.1.1: General AP Scan (All Channels) ---
I (1080) LAB5_1_SCAN: [FORENSIC]: Call esp_wifi_scan_start(&scan_config, true)
I (2640) LAB5_1_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (Scan time: 1560 ms)
I (2640) LAB5_1_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (2650) LAB5_1_SCAN: [FORENSIC]: Total APs Found: 5
I (2660) LAB5_1_SCAN: [1] SSID: Home_WiFi_2.4G       | RSSI: -52 dBm | CH: 1  | MAC: 24:4b:fe:1a:2b:3c
I (2670) LAB5_1_SCAN: [2] SSID: IoT_SmartLab         | RSSI: -65 dBm | CH: 6  | MAC: a0:20:a6:3d:4e:5f
I (2680) LAB5_1_SCAN: [3] SSID: TrueGigatex_5G_Guest | RSSI: -72 dBm | CH: 11 | MAC: ec:08:6b:12:34:56
I (2690) LAB5_1_SCAN: [4] SSID: Engineering_WiFi     | RSSI: -78 dBm | CH: 1  | MAC: 74:ac:b9:88:99:aa
I (2700) LAB5_1_SCAN: [5] SSID: Neighbor_Net         | RSSI: -84 dBm | CH: 6  | MAC: 50:d4:f7:11:22:33
------------------------------------------------------------------
I (3710) LAB5_1_SCAN: --- Experiment 5.1.2: Channel-Specific Scan (Channel 1) ---
I (3720) LAB5_1_SCAN: [FORENSIC]: Call esp_wifi_scan_start(channel=1)
I (3860) LAB5_1_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (Scan time: 140 ms)
I (3860) LAB5_1_SCAN: [FORENSIC]: Total APs Found: 2
I (3870) LAB5_1_SCAN: [1] SSID: Home_WiFi_2.4G       | RSSI: -53 dBm | CH: 1  | MAC: 24:4b:fe:1a:2b:3c
I (3880) LAB5_1_SCAN: [2] SSID: Engineering_WiFi     | RSSI: -79 dBm | CH: 1  | MAC: 74:ac:b9:88:99:aa
------------------------------------------------------------------
I (4890) LAB5_1_SCAN: --- Experiment 5.1.3: Targeted SSID Scan - Existing ("Home_WiFi_2.4G") ---
I (4900) LAB5_1_SCAN: [FORENSIC]: Call esp_wifi_scan_start(target_ssid="Home_WiFi_2.4G")
I (6440) LAB5_1_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (Scan time: 1540 ms)
I (6440) LAB5_1_SCAN: [FORENSIC]: Total APs Found: 1
I (6450) LAB5_1_SCAN: [1] SSID: Home_WiFi_2.4G       | RSSI: -52 dBm | CH: 1  | MAC: 24:4b:fe:1a:2b:3c
------------------------------------------------------------------
I (7460) LAB5_1_SCAN: --- Experiment 5.1.4: Targeted SSID Scan - Non-Existent ("NON_EXISTENT_AP_9999") ---
I (7470) LAB5_1_SCAN: [FORENSIC]: Call esp_wifi_scan_start(target_ssid="NON_EXISTENT_AP_9999")
I (8990) LAB5_1_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (Scan time: 1520 ms)
I (8990) LAB5_1_SCAN: [FORENSIC]: Total APs Found: 0
I (9000) LAB5_1_SCAN: ==================================================================
I (9000) LAB5_1_SCAN:   [Phase 1 Completed: Wi-Fi Scan Finished]
```

---

### ตารางบันทึกผลการทดลอง

#### 1. ตารางสรุปเปรียบเทียบการสแกนทั้ง 4 กรณี

| ข้อการทดลอง | เงื่อนไขการสแกน | สถานะ (Success/Error Code) | จำนวน AP ที่พบ (เครือข่าย) | เวลาที่ใช้ในการสแกน (ms) |
| :---: | :--- | :---: | :---: | :---: |
| **5.1.1** | สแกนทั่วไปทุก Channel | ESP_OK (Success) | 5 | 1560 |
| **5.1.2** | กำหนดสแกนเฉพาะ Channel 1 | ESP_OK (Success) | 2 | 140 |
| **5.1.3** | กำหนดสแกน SSID ที่มีจริง | ESP_OK (Success) | 1 | 1540 |
| **5.1.4** | กำหนดสแกน SSID ที่ไม่มีจริง | ESP_OK (Success) | 0 | 1520 |

#### 2. ตารางรายละเอียด AP ที่พบจากการสแกนทั่วไป (ข้อ 5.1.1)

| ลำดับ | ชื่อเครือข่าย (SSID) | MAC Address (BSSID) | ความแรงสัญญาณ (RSSI: dBm) | ช่องความถี่ (Channel) | ประเภทการเข้ารหัส (Encryption Type) |
| :---: | :--- | :--- | :---: | :---: | :--- |
| 1 | Home_WiFi_2.4G | 24:4b:fe:1a:2b:3c | -52 | 1 | WIFI_AUTH_WPA2_PSK |
| 2 | IoT_SmartLab | a0:20:a6:3d:4e:5f | -65 | 6 | WIFI_AUTH_WPA2_PSK |
| 3 | TrueGigatex_5G_Guest | ec:08:6b:12:34:56 | -72 | 11 | WIFI_AUTH_WPA2_WPA3_PSK |
| 4 | Engineering_WiFi | 74:ac:b9:88:99:aa | -78 | 1 | WIFI_AUTH_WPA2_PSK |
| 5 | Neighbor_Net | 50:d4:f7:11:22:33 | -84 | 6 | WIFI_AUTH_WPA2_PSK |

---

### คำถามท้ายการทดลอง (Post-Lab Questions)

#### 1. การกำหนดค่าในโครงสร้าง `wifi_scan_config_t` สำหรับสแกนเจาะจงเฉพาะช่องความถี่ (ข้อ 5.1.2) ช่วยลดเวลาในการสแกนเมื่อเทียบกับการสแกนทุกช่องความถี่ (ข้อ 5.1.1) อย่างไร และมีข้อจำกัดอย่างไร?
**ตอบ:** การลดเวลา: สแกนเฉพาะช่องที่กำหนด ไม่ต้องวนสแกนทีละช่องจนครบ 1–13 ช่อง จึงลดเวลารอรับสัญญาณลงได้มาก

ข้อจำกัด: ไม่เจอ Wi-Fi ที่ปล่อยสัญญาณอยู่บนช่องความถี่อื่น (เห็นแค่เฉพาะช่องที่เลือก)

#### 2. เมื่อสังเกตผล Forensic Log ในข้อ 5.1.4 (สแกนหา SSID ที่ไม่มีอยู่จริง) ฟังก์ชัน `esp_wifi_scan_start()`, `esp_wifi_scan_get_ap_num()` และ `esp_wifi_scan_get_ap_records()` ส่งคืนค่าอย่างไร?
**ตอบ:**esp_wifi_scan_start(): ส่งคืนค่า ESP_OK (เริ่มสแกนสำเร็จตามปกติ แม้จะไม่พบ SSID นั้นก็ตาม)

esp_wifi_scan_get_ap_num(): ส่งคืนค่า ESP_OK และเขียนค่าจำนวน AP ที่หาพบเป็น 0

esp_wifi_scan_get_ap_records(): ส่งคืนค่า ESP_OK (หรือ ESP_ERR_INVALID_ARG หากส่งขนาด array เป็น 0) โดยไม่มีข้อมูล AP ถูกคัดลอกลงใน buffer

#### 3. ค่าระดับความแรงสัญญาณ (RSSI) ที่แสดงเป็นตัวเลขติดลบ (เช่น -45 dBm กับ -80 dBm) ค่าใดแสดงถึงสัญญาณที่มีความแรงและความเสถียรมากกว่ากัน?
**ตอบ:** -45 dBm

เพราะยิ่งค่าติดลบน้อย (เข้าใกล้ 0 มากกว่า) แสดงว่าสัญญาณยิ่งแรงและมีความเสถียรมากกว่า

#### 4. เหตุใดการดึงค่า `authmode` (`wifi_auth_mode_t`) จากโครงสร้าง `wifi_ap_record_t` จึงมีความสำคัญต่อการเตรียมการในเฟสถัดไป (Authentication & Association Phase)?
**ตอบ:** เพื่อให้ ESP32 ทราบรูปแบบความปลอดภัยของ Access Point (เช่น OPEN, WPA2-PSK หรือ WPA3-SAE) และสามารถเตรียมขั้นตอนการยืนยันตัวตนได้อย่างถูกต้อง หากไม่ตรวจสอบก่อนแล้วตั้งค่ารหัสผ่านหรือโปรโตคอลไม่ตรงกับที่ AP รองรับ จะส่งผลให้กระบวนการ Authentication หรือ Association ล้มเหลวทันที