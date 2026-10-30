# ใบงานที่ 5.2: การยืนยันตัวตน การสถาปนาการเชื่อมต่อ และการรับหมายเลข IP Address (Wi-Fi Connection & IP Assignment)

## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองทั้ง 3 สถานการณ์

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event สุดท้ายที่ได้รับ | ผลลัพธ์ (Passed/Failed) | Reason Code (Decimal / Hex) | คำอธิบาย Reason Code |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.2.1** | SSID และ Password ถูกต้อง | IP_EVENT_STA_GOT_IP | Passed | - | เชื่อมต่อสำเร็จครบทุกเฟส และได้รับ IP จาก DHCP Server เรียบร้อย |
| **5.2.2** | ระบุ SSID ผิด (ไม่มีในระบบ) | WIFI_EVENT_STA_DISCONNECTED | Failed | 201 / 0xC9 | WIFI_REASON_NO_AP_FOUND (สแกนหา SSID เป้าหมายไม่พบในทุกช่องสัญญาณ) |
| **5.2.3** | ระบุ SSID ถูกต้อง แต่ Password ผิด | WIFI_EVENT_STA_DISCONNECTED | Failed | 15 / 0x0F (หรือ 204 / 0xCC) | WIFI_REASON_HANDSHAKE_TIMEOUT / 4WAY_HANDSHAKE_TIMEOUT (ล้มเหลวในการตรวจสอบ MIC ในเฟส 4-Way Handshake) |

### 6.2 บันทึกข้อมูลเครือข่ายจากการเชื่อมต่อสำเร็จ (ข้อ 5.2.1)

| พารามิเตอร์เครือข่าย | ค่าที่ได้รับจริงจาก DHCP |
| :--- | :--- |
| **SSID** | IoT_SmartLab_2.4G |
| **BSSID (MAC Address)** | B0:A7:32:15:4D:2C |
| **Channel** | 6 |
| **IP Address** | 192.168.1.135 |
| **Subnet Mask** | 255.255.255.0 |
| **Default Gateway** | 192.168.1.1 |

### 6.3 ผลลัพธ์จาก Serial Monitor Console (Forensic Output Log)

```text
I (516) main_task: Calling app_main()
I (516) LAB_WIFI_CONN: [FORENSIC]: Call nvs_flash_init()
I (536) LAB_WIFI_CONN: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (536) LAB_WIFI_CONN: [FORENSIC]: Call esp_netif_init()
I (546) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_loop_create_default()
I (546) LAB_WIFI_CONN: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (556) LAB_WIFI_CONN: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbca10
I (566) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_init(&cfg)
I (586) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (586) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_handler_instance_register(IP_EVENT)
I (596) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (606) LAB_WIFI_CONN: ==================================================================
I (606) LAB_WIFI_CONN:   Lab 5.2: Wi-Fi Connection & IP Assignment (ESP-IDF Forensic)
I (616) LAB_WIFI_CONN: ==================================================================

I (616) LAB_WIFI_CONN: ------------------------------------------------------------------
I (626) LAB_WIFI_CONN: >>> Experiment 5.2.1: Connection Test - Correct Credentials
I (626) LAB_WIFI_CONN: ------------------------------------------------------------------
I (636) LAB_WIFI_CONN:   Target SSID: "IoT_SmartLab_2.4G"
I (636) LAB_WIFI_CONN:   Target Password: "Correct_Password_123"
I (646) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (656) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (666) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (666) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (736) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (746) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (746) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (756) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (2450) LAB_WIFI_CONN: =======================================================
I (2450) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (2450) LAB_WIFI_CONN:   -> Connected to SSID : IoT_SmartLab_2.4G
I (2460) LAB_WIFI_CONN:   -> BSSID            : B0:A7:32:15:4D:2C
I (2460) LAB_WIFI_CONN:   -> Channel          : 6
I (2470) LAB_WIFI_CONN:   -> Auth Mode        : 3
I (2470) LAB_WIFI_CONN: =======================================================
I (3210) LAB_WIFI_CONN: =======================================================
I (3210) LAB_WIFI_CONN: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!
I (3210) LAB_WIFI_CONN:   -> IP Address : 192.168.1.135
I (3220) LAB_WIFI_CONN:   -> Netmask    : 255.255.255.0
I (3220) LAB_WIFI_CONN:   -> Gateway    : 192.168.1.1
I (3230) LAB_WIFI_CONN: =======================================================
I (3230) LAB_WIFI_CONN: [RESULT]: TEST PASSED - Connected to AP successfully!

I (5240) LAB_WIFI_CONN: ------------------------------------------------------------------
I (5240) LAB_WIFI_CONN: >>> Experiment 5.2.2: Connection Test - Wrong SSID (No AP Found)
I (5250) LAB_WIFI_CONN: ------------------------------------------------------------------
I (5250) LAB_WIFI_CONN:   Target SSID: "NON_EXISTENT_SSID_9999"
I (5260) LAB_WIFI_CONN:   Target Password: "12345678"
I (5260) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (5270) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (5280) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (5350) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (5350) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
W (7890) LAB_WIFI_CONN: =======================================================
W (7890) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (7900) LAB_WIFI_CONN:   -> Target SSID          : NON_EXISTENT_SSID_9999
W (7900) LAB_WIFI_CONN:   -> Reason Code (Decimal): 201
W (7910) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0xC9
W (7910) LAB_WIFI_CONN:   -> Reason Description   : WIFI_REASON_NO_AP_FOUND (201)
W (7920) LAB_WIFI_CONN: =======================================================
W (7920) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.

I (9930) LAB_WIFI_CONN: ------------------------------------------------------------------
I (9930) LAB_WIFI_CONN: >>> Experiment 5.2.3: Connection Test - Wrong Password (Auth/Handshake Fail)
I (9940) LAB_WIFI_CONN: ------------------------------------------------------------------
I (9940) LAB_WIFI_CONN:   Target SSID: "IoT_SmartLab_2.4G"
I (9950) LAB_WIFI_CONN:   Target Password: "WRONG_PASS_9999"
I (9950) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (9960) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (9970) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (10040) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (10040) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (11480) LAB_WIFI_CONN: =======================================================
I (11480) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (11480) LAB_WIFI_CONN:   -> Connected to SSID : IoT_SmartLab_2.4G
I (11490) LAB_WIFI_CONN:   -> BSSID            : B0:A7:32:15:4D:2C
I (11490) LAB_WIFI_CONN:   -> Channel          : 6
I (11500) LAB_WIFI_CONN:   -> Auth Mode        : 3
I (11500) LAB_WIFI_CONN: =======================================================
W (13620) LAB_WIFI_CONN: =======================================================
W (13620) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (13620) LAB_WIFI_CONN:   -> Target SSID          : IoT_SmartLab_2.4G
W (13630) LAB_WIFI_CONN:   -> Reason Code (Decimal): 15
W (13630) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0x0F
W (13640) LAB_WIFI_CONN:   -> Reason Description   : WIFI_REASON_HANDSHAKE_TIMEOUT (15)
W (13640) LAB_WIFI_CONN: =======================================================
W (13650) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (13660) LAB_WIFI_CONN: ==================================================================
I (13660) LAB_WIFI_CONN:   [Phase 2/3/4/5 Completed: Wi-Fi Connection Lab Finished]
I (13670) LAB_WIFI_CONN: ==================================================================
```

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการระบุ SSID ผิด (ข้อ 5.2.2) จึงส่งผลให้เกิด Disconnect Event ด้วย Reason Code `201` (`WIFI_REASON_NO_AP_FOUND`) ตั้งแต่เฟส Scan?
> **คำตอบ:** 
> ในกระบวนการเชื่อมต่อของ ESP-IDF ก่อนที่สเตชันจะสามารถส่งเฟรม Authentication (Phase 2) ไปยัง AP ได้ สเตชันจำเป็นต้องทราบ BSSID (MAC Address ของ AP) และช่องความถี่ (Channel) ปัจจุบันของ AP นั้นก่อน โดยจะทำการส่ง Probe Request ค้นหาชื่อ SSID ดังกล่าวใน Phase 1 (Scan Phase) เมื่อกวาดครบทั้ง 13–14 ช่องสัญญาณแล้วไม่ได้รับ Probe Response หรือ Beacon ที่ตรงกับ SSID นั้น ตัวขับ Wi-Fi Driver จะสรุปว่าไม่มีเครือข่ายนี้อยู่จริง จึงยุติกระบวนการเชื่อมต่อทันทีและส่งสัญญาณ `WIFI_EVENT_STA_DISCONNECTED` พร้อมแจ้ง Reason Code `201` (`WIFI_REASON_NO_AP_FOUND`) ออกมาโดยไม่มีการเริ่ม Phase 2 แต่อย่างใด

2. เหตุใดการพิมพ์ Password ผิด (ข้อ 5.2.3) จึงผ่านเฟส Auth และ Assoc มาได้ แต่มาล้มเหลวในเฟส 4-Way Handshake (Reason Code `15` หรือ `204`)?
> **คำตอบ:** 
> เนื่องจากมาตรฐาน IEEE 802.11 แยกกลไกการผูกสัมพันธ์ทางกายภาพ (Link-Layer Association) ออกจากกลไกการยืนยันรหัสผ่านความปลอดภัย (Security Handshake):
> - ใน **Phase 2 (Authentication)** สำหรับเครือข่าย WPA2-PSK จะใช้กระบวนการ **Open System Authentication** ซึ่งเป็นการตรวจสอบความพร้อมการสื่อสารระดับ L2 โดยไม่มีการส่งหรือตรวจสอบรหัสผ่าน
> - ใน **Phase 3 (Association)** เป็นเพียงการส่งคุณสมบัติฮาร์ดแวร์และขอรับหมายเลข AID ทำให้ระบบผ่านเฟส 2 และ 3 ได้สำเร็จและเกิด Event `WIFI_EVENT_STA_CONNECTED`
> - การตรวจสอบรหัสผ่านที่แท้จริงจะเริ่มขึ้นใน **Phase 4 (4-Way Handshake)** ผ่านเฟรม EAPOL โดยอาศัยคีย์ PMK ที่คำนวณจากรหัสผ่าน เมื่อป้อนรหัสผ่านผิด ค่า PMK และ PTK ของ ESP32 จะไม่ตรงกับ AP ส่งผลให้ค่า **MIC (Message Integrity Code)** ในเฟรม 2/4 ตรวจสอบไม่ผ่าน AP จึงไม่ส่งเฟรม 3/4 ตอบกลับ และตัดการเชื่อมต่อเมื่อหมดเวลา (Handshake Timeout) ด้วย Reason Code `15` หรือ `204`

3. ลำดับการเกิด Event ระหว่าง **`WIFI_EVENT_STA_CONNECTED`** กับ **`IP_EVENT_STA_GOT_IP`** Event ใดเกิดขึ้นก่อนกัน และมีความหมายทางกายภาพของ Layer Network ต่างกันอย่างไร?
> **คำตอบ:** 
> **`WIFI_EVENT_STA_CONNECTED` เกิดขึ้นก่อนเสมอ** ตามด้วย `IP_EVENT_STA_GOT_IP`
> - **`WIFI_EVENT_STA_CONNECTED` (Data Link Layer - Layer 2):** หมายถึงสเตชันสามารถสถาปนาการเชื่อมต่อทางคลื่นวิทยุกับ AP ได้สำเร็จในระดับเฟรม 802.11 (ผ่าน Phase 3 Association) แต่ในขณะนี้พอร์ตข้อมูลยังถูกควบคุม พอร์ต IP ยังไม่เปิด และอุปกรณ์ยังไม่มีหมายเลข IP ประจำตัว จึงยังไม่สามารถส่งแพ็กเกจอินเทอร์เน็ตได้
> - **`IP_EVENT_STA_GOT_IP` (Network Layer - Layer 3):** เกิดขึ้นหลังจากผ่านการยืนยันตัวตน Phase 4 (แลกเปลี่ยนคีย์สำเร็จ) และเข้าสู่ Phase 5 โดยโมดูล DHCP Client (lwIP) สามารถขอและได้รับจัดสรร IP Address, Subnet Mask และ Gateway จาก DHCP Server เรียบร้อยแล้ว ณ จุดนี้อุปกรณ์จึงจะพร้อมสื่อสารผ่านโพรโทคอลระดับสูง เช่น TCP/UDP, HTTP, MQTT และอินเทอร์เน็ตได้อย่างสมบูรณ์

4. สมาชิกตัวแปร `reason` ในโครงสร้าง `wifi_event_sta_disconnected_t` มีประโยชน์อย่างไรต่อการออกแบบระบบค้นหาสาเหตุและกู้คืนการเชื่อมต่อ (Auto-Reconnection Mechanism) ในแอปพลิเคชัน IoT?
> **คำตอบ:** 
> มีประโยชน์อย่างยิ่งในการสร้าง State Machine สำหรับการกู้คืนการเชื่อมต่อแบบชาญฉลาด (Smart Auto-Recovery):
> 1. **กรณี `WIFI_REASON_NO_AP_FOUND` (201):** แสดงว่าเร้าเตอร์ดับหรืออยู่นอกระยะ ไม่ควรสั่ง Reconnect ถี่เกินไป ควรใช้กลยุทธ์ **Exponential Backoff** (เช่น หน่วงเวลา 5s, 15s, 30s, 60s) เพื่อลดการใช้พลังงานของอุปกรณ์ที่ใช้แบตเตอรี่
> 2. **กรณี `WIFI_REASON_HANDSHAKE_TIMEOUT` (15) หรือ `4WAY_HANDSHAKE_TIMEOUT` (204):** แสดงว่ารหัสผ่านผิด การ Reconnect ซ้ำจะไม่ช่วยอะไร ระบบควรแจ้งเตือนผู้ใช้ หรือเปิดโหมด SoftAP / BLE Provisioning เพื่อให้ผู้ใช้เข้ามาตั้งค่ารหัสผ่านใหม่
> 3. **กรณี `WIFI_REASON_BEACON_TIMEOUT` (200) หรือ `AUTH_EXPIRE` (2):** แสดงว่าเป็นปัญหาจากสัญญาณรบกวนชั่วคราวหรือระยะทาง อุปกรณ์สามารถสั่ง `esp_wifi_connect()` ทันทีเพื่อกู้คืนการเชื่อมต่อได้อย่างรวดเร็ว
