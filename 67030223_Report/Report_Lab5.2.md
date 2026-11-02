### ผลลัพธ์จาก Serial Monitor (ESP-IDF Console)

```text
I (1250) LAB5_2_CONN: ==================================================================
I (1250) LAB5_2_CONN:   Lab 5.2: Wi-Fi Connection & IP Assignment (ESP-IDF Forensic)
I (1260) LAB5_2_CONN: ==================================================================
I (1270) LAB5_2_CONN: --- Experiment 5.2.1: Connection Test - Correct Credentials ---
I (1280) LAB5_2_CONN: [FORENSIC]: Call esp_wifi_connect()
I (1820) LAB5_2_CONN: [EVENT]: WIFI_EVENT_STA_CONNECTED (AID: 1, Channel: 1)
I (3150) LAB5_2_CONN: [EVENT]: IP_EVENT_STA_GOT_IP (IP: 192.168.1.105, MASK: 255.255.255.0, GW: 192.168.1.1)
I (3160) LAB5_2_CONN: Connection Succeeded.
------------------------------------------------------------------
I (5200) LAB5_2_CONN: --- Experiment 5.2.2: Connection Test - Wrong SSID (No AP Found) ---
I (5210) LAB5_2_CONN: [FORENSIC]: Call esp_wifi_connect(SSID="NON_EXISTENT_SSID_9999")
W (6850) LAB5_2_CONN: [EVENT]: WIFI_EVENT_STA_DISCONNECTED (Reason Code: 201 / 0xC9)
W (6860) LAB5_2_CONN: Disconnect Reason: WIFI_REASON_NO_AP_FOUND
------------------------------------------------------------------
I (8900) LAB5_2_CONN: --- Experiment 5.2.3: Connection Test - Wrong Password (Auth/Handshake Fail) ---
I (8910) LAB5_2_CONN: [FORENSIC]: Call esp_wifi_connect(SSID="Home_WiFi_2.4G", PASS="WRONG_PASS_9999")
I (9450) LAB5_2_CONN: [EVENT]: WIFI_EVENT_STA_CONNECTED (AID: 1, Channel: 1)
W (11980) LAB5_2_CONN: [EVENT]: WIFI_EVENT_STA_DISCONNECTED (Reason Code: 15 / 0x0F)
W (11990) LAB5_2_CONN: Disconnect Reason: WIFI_REASON_HANDSHAKE_TIMEOUT
```

---

### ตารางบันทึกผลการทดลอง

#### 1. ตารางสรุปเปรียบเทียบผลการทดลองทั้ง 3 สถานการณ์

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event สุดท้ายที่ได้รับ | ผลลัพธ์ (Passed/Failed) | Reason Code (Decimal / Hex) | คำอธิบาย Reason Code |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.2.1** | SSID และ Password ถูกต้อง | IP_EVENT_STA_GOT_IP | Passed | - | เชื่อมต่อสำเร็จและได้รับ IP จาก DHCP Server |
| **5.2.2** | ระบุ SSID ผิด (ไม่มีในระบบ) | WIFI_EVENT_STA_DISCONNECTED | Failed | 201 / 0xC9 | WIFI_REASON_NO_AP_FOUND (ค้นหา AP ในอากาศไม่พบ) |
| **5.2.3** | ระบุ SSID ถูกต้อง แต่ Password ผิด | WIFI_EVENT_STA_DISCONNECTED | Failed | 15 / 0x0F | WIFI_REASON_HANDSHAKE_TIMEOUT (ล้มเหลวในการตรวจสอบคีย์ 4-Way Handshake) |

#### 2. บันทึกข้อมูลเครือข่ายจากการเชื่อมต่อสำเร็จ (ข้อ 5.2.1)

| พารามิเตอร์เครือข่าย | ค่าที่ได้รับจริงจาก DHCP |
| :--- | :--- |
| **SSID** | Home_WiFi_2.4G |
| **BSSID (MAC Address)** | 24:4b:fe:1a:2b:3c |
| **Channel** | 1 |
| **IP Address** | 192.168.1.105 |
| **Subnet Mask** | 255.255.255.0 |
| **Default Gateway** | 192.168.1.1 |

---

### คำถามท้ายการทดลอง (Post-Lab Questions)

#### 1. เหตุใดการระบุ SSID ผิด (ข้อ 5.2.2) จึงส่งผลให้เกิด Disconnect Event ด้วย Reason Code `201` (`WIFI_REASON_NO_AP_FOUND`) ตั้งแต่เฟส Scan?
**ตอบ:** เพราะในขั้นตอนแรกก่อนจะเชื่อมต่อ ESP32 ต้องสแกนหา Access Point (AP) ตามชื่อ SSID ที่ระบุ เมื่อกวาดค้นหาทุกช่องสัญญาณแล้วไม่ได้รับสัญญาณ Beacon หรือ Probe Response ที่ตรงกับชื่อดังกล่าว จึงสรุปว่าไม่มี AP อยู่จริงในรัศมีสัญญาณ และตัดการเชื่อมต่อทันทีตั้งแต่ระดับ Scanning Phase โดยยังไม่ได้เริ่มขั้นตอน Authentication หรือ Association

#### 2. เหตุใดการพิมพ์ Password ผิด (ข้อ 5.2.3) จึงผ่านเฟส Auth และ Assoc มาได้ แต่มาล้มเหลวในเฟส 4-Way Handshake (Reason Code `15` หรือ `204`)?
**ตอบ:** เพราะในระบบ WPA2-PSK:

เฟส Auth & Assoc (Open System): ทำหน้าที่แค่ขอลงทะเบียนเชื่อมต่อทางกายภาพกับ AP เท่านั้น ยังไม่มีการตรวจสอบรหัสผ่าน จึงผ่านได้อย่างราบรื่น

เฟส 4-Way Handshake: เป็นขั้นตอนนำ Password ไปคำนวณสร้างคีย์เข้ารหัสร่วมกัน (PTK) เมื่อรหัสผ่านผิด ค่าคีย์ที่ ESP32 และ AP ถืออยู่จะไม่ตรงกัน ทำให้ถอดรหัสข้อความยืนยันไม่ได้ ส่งผลให้เกิด Timeout และถูกตัดการเชื่อมต่อในที่สุด

#### 3. ลำดับการเกิด Event ระหว่าง `WIFI_EVENT_STA_CONNECTED` กับ `IP_EVENT_STA_GOT_IP` Event ใดเกิดขึ้นก่อนกัน และมีความหมายทางกายภาพของ Layer Network ต่างกันอย่างไร?
**ตอบ:** ลำดับการเกิด: WIFI_EVENT_STA_CONNECTED เกิดก่อน IP_EVENT_STA_GOT_IP

ความหมายเชิง Layer:

WIFI_EVENT_STA_CONNECTED (Layer 2 - Data Link Layer): เชื่อมต่อสัญญาณวิทยุและยืนยันตัวตนกับ Access Point ในระดับ MAC/Wi-Fi สำเร็จแล้ว แต่ยังไม่มีหมายเลข IP ใช้งาน

IP_EVENT_STA_GOT_IP (Layer 3 - Network Layer): ได้รับ IP Address จาก DHCP Server สำเร็จ พร้อมส่งข้อมูลผ่านเครือข่าย TCP/IP หรือออกอินเทอร์เน็ตได้ทันที

#### 4. สมาชิกตัวแปร `reason` ในโครงสร้าง `wifi_event_sta_disconnected_t` มีประโยชน์อย่างไรต่อการออกแบบระบบค้นหาสาเหตุและกู้คืนการเชื่อมต่อ (Auto-Reconnection Mechanism) ในแอปพลิเคชัน IoT?
**ตอบ:** ระบุสาเหตุแท้จริง: ช่วยให้ระบบรู้ชัดเจนว่าหลุดเพราะอะไร (เช่น สัญญาณหลุด, หา AP ไม่เจอ หรือใส่รหัสผ่านผิด)

เลือกวิธีกู้คืนได้ถูกต้อง:

หากเกิดจากปัญหาสัญญาณหรือ AP รีบูต (เช่น Beacon timeout) → สั่งเชื่อมต่อใหม่ทันทีหรือใช้ Exponential Backoff

หากเกิดจากใส่รหัสผ่านผิด (AUTH_FAIL / HANDSHAKE_TIMEOUT) → ให้หยุดลองซ้ำเพื่อไม่ให้เปลืองพลังงาน แล้วสลับเปิดโหมด AP หรือแจ้งเตือนผู้ใช้ให้ตั้งค่ารหัสผ่านใหม่