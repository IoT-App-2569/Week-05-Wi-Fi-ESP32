# ใบงานที่ 5.1: การเชื่อมต่อ Wi-Fi และการค้นหาสัญญาณรอบข้าง (Wi-Fi Connection and Scanning)

## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบการสแกนทั้ง 4 กรณี

| ข้อการทดลอง | เงื่อนไขการสแกน | สถานะ (Success/Error Code) | จำนวน AP ที่พบ (เครือข่าย) | เวลาที่ใช้ในการสแกน (ms) |
| :---: | :--- | :---: | :---: | :---: |
| **5.1.1** | สแกนทั่วไปทุก Channel | ESP_OK (0x0) | 12 | 1,582 |
| **5.1.2** | กำหนดสแกนเฉพาะ Channel 1 | ESP_OK (0x0) | 3 | 134 |
| **5.1.3** | กำหนดสแกน SSID ที่มีจริง | ESP_OK (0x0) | 1 | 1,564 |
| **5.1.4** | กำหนดสแกน SSID ที่ไม่มีจริง | ESP_OK (0x0) | 0 | 1,551 |

### 6.2 ตารางรายละเอียด AP ที่พบจากการสแกนทั่วไป (ข้อ 5.1.1)

| ลำดับ | ชื่อเครือข่าย (SSID) | MAC Address (BSSID) | ความแรงสัญญาณ (RSSI: dBm) | ช่องความถี่ (Channel) | ประเภทการเข้ารหัส (Encryption Type) |
| :---: | :--- | :--- | :---: | :---: | :--- |
| 1 | KMITL-WiFi | 34:2C:C4:8A:12:F0 | -48 dBm | 1 | WPA2_ENTERPRISE |
| 2 | IoT_SmartLab_2.4G | B0:A7:32:15:4D:2C | -54 dBm | 6 | WPA2_PSK |
| 3 | TrueGigatex_2.4G_A1 | 70:D9:23:6B:88:94 | -66 dBm | 11 | WPA2_WPA3_PSK |
| 4 | AIS_SUPER_WiFi | 2C:39:96:4E:91:02 | -73 dBm | 1 | WPA2_PSK |
| 5 | &lt;Hidden SSID&gt; | E8:65:D4:A0:18:7E | -81 dBm | 6 | WPA2_PSK |

### 6.3 ผลลัพธ์จาก Serial Monitor Console (Forensic Output Log)

```text
I (516) main_task: Calling app_main()
I (516) LAB_WIFI_SCAN: [FORENSIC]: Call nvs_flash_init()
I (536) LAB_WIFI_SCAN: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (536) LAB_WIFI_SCAN: [FORENSIC]: Call esp_netif_init()
I (546) LAB_WIFI_SCAN: [FORENSIC]: esp_netif_init() returned ESP_OK (0x0)
I (546) LAB_WIFI_SCAN: [FORENSIC]: Call esp_event_loop_create_default()
I (556) LAB_WIFI_SCAN: [FORENSIC]: esp_event_loop_create_default() returned ESP_OK (0x0)
I (556) LAB_WIFI_SCAN: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (566) LAB_WIFI_SCAN: [FORENSIC]: esp_netif_create_default_wifi_sta() returned pointer 0x3ffbca10
I (576) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_init(&cfg)
I (586) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_init() returned ESP_OK (0x0)
I (586) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (596) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_set_mode() returned ESP_OK (0x0)
I (596) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_start()
I (676) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (676) LAB_WIFI_SCAN: ==================================================================
I (676) LAB_WIFI_SCAN:   Lab 5.1: Wi-Fi Connection and Scanning Phase (ESP-IDF Forensic)
I (686) LAB_WIFI_SCAN: ==================================================================
I (686) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (696) LAB_WIFI_SCAN: >>> Experiment 5.1.1: General AP Scan (All Channels)
I (696) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (706) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (2288) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 1582 ms]
I (2288) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (2298) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=12
I (2298) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (2308) LAB_WIFI_SCAN: [AP COUNT]: 12 network(s) found
I (2308) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_records(&number, ap_info)
I (2318) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_records() returned ESP_OK (0x0), records=12

--------------------------------------------------------------------------------------------------
No.  | SSID                     | MAC Address (BSSID) | RSSI   | Chan | Encryption Type     
--------------------------------------------------------------------------------------------------
1    | KMITL-WiFi               | 34:2C:C4:8A:12:F0   | -48 dBm| 1    | WPA2_ENTERPRISE     
2    | IoT_SmartLab_2.4G        | B0:A7:32:15:4D:2C   | -54 dBm| 6    | WPA2_PSK            
3    | TrueGigatex_2.4G_A1      | 70:D9:23:6B:88:94   | -66 dBm| 11   | WPA2_WPA3_PSK       
4    | AIS_SUPER_WiFi           | 2C:39:96:4E:91:02   | -73 dBm| 1    | WPA2_PSK            
5    | <Hidden SSID>            | E8:65:D4:A0:18:7E   | -81 dBm| 6    | WPA2_PSK            
--------------------------------------------------------------------------------------------------

I (3328) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (3328) LAB_WIFI_SCAN: >>> Experiment 5.1.2: Channel-Specific Scan (Channel 1)
I (3338) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (3338) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (3472) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 134 ms]
I (3472) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (3482) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=3
I (3482) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (3492) LAB_WIFI_SCAN: [AP COUNT]: 3 network(s) found

I (4502) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (4502) LAB_WIFI_SCAN: >>> Experiment 5.1.3: Targeted SSID Scan - Existing ("KMITL-WiFi")
I (4512) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (4512) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (6076) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 1564 ms]
I (6076) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (6086) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=1
I (6086) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (6096) LAB_WIFI_SCAN: [AP COUNT]: 1 network(s) found

I (7106) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (7106) LAB_WIFI_SCAN: >>> Experiment 5.1.4: Targeted SSID Scan - Non-Existent ("NON_EXISTENT_AP_9999")
I (7116) LAB_WIFI_SCAN: ------------------------------------------------------------------
I (7116) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)
I (8667) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_start() returned ESP_OK (0x0) [Duration: 1551 ms]
I (8667) LAB_WIFI_SCAN: [FORENSIC]: Call esp_wifi_scan_get_ap_num(&ap_count)
I (8677) LAB_WIFI_SCAN: [FORENSIC]: esp_wifi_scan_get_ap_num() returned ESP_OK (0x0), ap_count=0
I (8677) LAB_WIFI_SCAN: [STATUS]: Scan SUCCESS
I (8687) LAB_WIFI_SCAN: [AP COUNT]: 0 network(s) found
W (8687) LAB_WIFI_SCAN: [NOTE]: No Access Point found matching the criteria.
I (8697) LAB_WIFI_SCAN: ==================================================================
I (8697) LAB_WIFI_SCAN:   [Phase 1 Completed: Wi-Fi Scan Finished]
I (8707) LAB_WIFI_SCAN:   Program stopped after scanning. Auth/Assoc Phase not started.
I (8707) LAB_WIFI_SCAN: ==================================================================
```

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. การกำหนดค่าในโครงสร้าง `wifi_scan_config_t` สำหรับสแกนเจาะจงเฉพาะช่องความถี่ (ข้อ 5.1.2) ช่วยลดเวลาในการสแกนเมื่อเทียบกับการสแกนทุกช่องความถี่ (ข้อ 5.1.1) อย่างไร และมีข้อจำกัดอย่างไร?
> **คำตอบ:** 
> การกำหนด `.channel = 1` ช่วยลดเวลาในการสแกนได้อย่างมีนัยสำคัญจากประมาณ 1,582 ms เหลือเพียง 134 ms (ลดลงกว่า 90%) เนื่องจากตัวรับส่งคลื่นวิทยุ (Wi-Fi Radio) ของ ESP32 จะส่ง Probe Request และดักฟังสัญญาณ Beacon เฉพาะในความถี่ 2.412 GHz (Channel 1) เพียงช่องเดียว โดยไม่ต้องเสียเวลาสลับช่องความถี่ (Channel Hopping) และไม่ต้องรอค่า `passive_ms` หรือ `active_max_ms` ครบทั้ง 13–14 ช่องสัญญาณ
> 
> **ข้อจำกัด:** หาก Access Point เป้าหมายถูกย้ายช่องสัญญาณ หรือตัว Router เปิดใช้งานฟังก์ชัน Dynamic Frequency Selection / Auto-Channel Optimization จนเปลี่ยนไปทำงานใน Channel อื่น (เช่น Channel 6 หรือ 11) สเตชันจะไม่สามารถค้นหา AP เป้าหมายพบได้เลย

2. เมื่อสังเกตผล Forensic Log ในข้อ 5.1.4 (สแกนหา SSID ที่ไม่มีอยู่จริง) ฟังก์ชัน `esp_wifi_scan_start()`, `esp_wifi_scan_get_ap_num()` และ `esp_wifi_scan_get_ap_records()` ส่งคืนค่าอย่างไร?
> **คำตอบ:**
> - `esp_wifi_scan_start()`: ส่งคืนค่า `ESP_OK` (0x0) สำเร็จตามปกติ เนื่องจากกระบวนการสแกนทางกายภาพ (Physical Scanning) สามารถกวาดค้นหาคลื่นวิทยุและส่ง Probe Request ได้ครบถ้วนตามขั้นตอนของระบบ
> - `esp_wifi_scan_get_ap_num(&ap_count)`: ส่งคืนค่า `ESP_OK` (0x0) โดยตัวแปร `ap_count` จะได้รับค่าเป็น `0` เนื่องจากไม่มี AP ตัวใดในบริเวณดังกล่าวที่ส่ง SSID ตรงกับชื่อที่ระบุ
> - `esp_wifi_scan_get_ap_records(&number, ap_info)`: ภายในโปรแกรมมีเงื่อนไขตรวจสอบ `if (ap_count == 0)` จึงไม่ได้เรียกฟังก์ชันนี้เพื่อจองหน่วยความจำ แต่หากมีการเรียกใช้งาน ฟังก์ชันจะคืนค่า `ESP_OK` พร้อมค่า `number = 0` และไม่มีการเขียนทับข้อมูลลงในโครงสร้างหน่วยความจำ

3. ค่าระดับความแรงสัญญาณ (RSSI) ที่แสดงเป็นตัวเลขติดลบ (เช่น -45 dBm กับ -80 dBm) ค่าใดแสดงถึงสัญญาณที่มีความแรงและความเสถียรมากกว่ากัน?
> **คำตอบ:**
> ค่า **-45 dBm** แสดงถึงสัญญาณที่มีความแรงและความเสถียรมากกว่าอย่างชัดเจน เนื่องจากหน่วย dBm เป็นสเกลลอการิทึมที่อ้างอิงเทียบกับกำลังไฟฟ้า 1 มิลลิวัตต์ ) ค่าตัวเลขติดลบที่เข้าใกล้ 0 มากกว่า ย่อมหมายถึงกำลังคลื่นวิทยุที่ภาครับวัดได้มีความแรงสูงกว่า
> - ค่า **-45 dBm** จัดอยู่ในเกณฑ์ "สัญญาณดีเยี่ยม" (Excellent Signal) ค่า Packet Loss ต่ำมาก และได้ Throughput สูงสุด
> - ค่า **-80 dBm** จัดอยู่ในเกณฑ์ "สัญญาณอ่อนมาก" (Very Poor Signal) เข้าใกล้ Noise Floor มีโอกาสเกิด Packet Drop สัญญาณหลุดบ่อย และอัตราความเร็วตกฮวบ

4. เหตุใดการดึงค่า `authmode` (`wifi_auth_mode_t`) จากโครงสร้าง `wifi_ap_record_t` จึงมีความสำคัญต่อการเตรียมการในเฟสถัดไป (Authentication & Association Phase)?
> **คำตอบ:**
> มีความสำคัญอย่างยิ่งในการเตรียมคอนฟิกกูเรชันเพื่อเชื่อมต่อกับ AP ให้ถูกต้องและปลอดภัย:
> 1. ทำให้สเตชันทราบโหมดความปลอดภัยล่วงหน้า (เช่น Open, WPA2-PSK หรือ WPA3-SAE) เพื่อนำไปกำหนดค่า `threshold.authmode` ในโครงสร้าง `wifi_config_t` ให้ตรงกัน ป้องกันข้อผิดพลาดจากการจับคู่โหมดไม่ตรงกัน
> 2. ป้องกันการโจมตีแบบ Downgrade Attack หรือ AP ปลอม (Evil Twin) โดยหากระบบตั้งใจจะต่อกับ AP ที่มีความปลอดภัยสูง แต่ตรวจพบว่า AP กลายเป็น `WIFI_AUTH_OPEN` สเตชันสามารถยกเลิกการเชื่อมต่อได้ทันที
> 3. ช่วยให้ตัวประมวลผลความปลอดภัยเตรียมอัลกอริทึมเข้ารหัสและเตรียมโครงสร้างสำหรับเฟส 4-Way Handshake ได้อย่างเหมาะสม
