### ผลลัพธ์จาก Serial Monitor (ESP-IDF Console)

```text
I (1200) LAB5_3_AUTH_ASSOC: ==================================================================
I (1200) LAB5_3_AUTH_ASSOC:   Lab 5.3: Wi-Fi Authentication & Association Phase (ESP-IDF Forensic)
I (1210) LAB5_3_AUTH_ASSOC: ==================================================================
I (1220) LAB5_3_AUTH_ASSOC: --- Experiment 5.3.1: Link-Layer Auth & Assoc Phase Test ---
I (1230) LAB5_3_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (1750) LAB5_3_AUTH_ASSOC: [EVENT]: WIFI_EVENT_STA_CONNECTED
I (1750) LAB5_3_AUTH_ASSOC: [FORENSIC]: Connected AP SSID: Home_WiFi_2.4G
I (1760) LAB5_3_AUTH_ASSOC: [FORENSIC]: Connected BSSID: 24:4b:fe:1a:2b:3c
I (1760) LAB5_3_AUTH_ASSOC: [FORENSIC]: Assigned AID: 1
I (1770) LAB5_3_AUTH_ASSOC: [FORENSIC]: Channel: 1, Auth Mode: 3 (WIFI_AUTH_WPA2_PSK)
------------------------------------------------------------------
I (3800) LAB5_3_AUTH_ASSOC: --- Experiment 5.3.2: Link-Layer Test - Non-Existent AP ---
I (3810) LAB5_3_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect(SSID="NON_EXISTENT_AP_9999")
W (5350) LAB5_3_AUTH_ASSOC: [EVENT]: WIFI_EVENT_STA_DISCONNECTED (Reason: 201)
W (5360) LAB5_3_AUTH_ASSOC: Disconnect Reason: WIFI_REASON_NO_AP_FOUND
```

---

### ตารางบันทึกผลการทดลอง

#### 1. ตารางสรุปเปรียบเทียบผลการทดลองในระดับ Link Layer

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event ที่ได้รับ | ผลการผูกสัมพันธ์ Link Layer | ค่า Association ID (AID) ที่ได้ | Reason Code (ถ้ามี) |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.3.1** | ร้องขอ Auth & Assoc กับ AP มีอยู่จริง | WIFI_EVENT_STA_CONNECTED | สำเร็จ | 1 | - |
| **5.3.2** | ร้องขอ Auth & Assoc กับ AP ไม่มีอยู่จริง | WIFI_EVENT_STA_DISCONNECTED | ไม่สำเร็จ | - | 201 (WIFI_REASON_NO_AP_FOUND) |

#### 2. บันทึกข้อมูล Link Layer จาก Event `WIFI_EVENT_STA_CONNECTED` (ข้อ 5.3.1)

| พารามิเตอร์ Link Layer | ค่าที่อ่านได้จริงจาก Forensic Log |
| :--- | :--- |
| **SSID** | Home_WiFi_2.4G |
| **BSSID (MAC Address)** | 24:4b:fe:1a:2b:3c |
| **Channel** | 1 |
| **Auth Mode Enum** | 3 (WIFI_AUTH_WPA2_PSK) |
| **Association ID (AID)** | 1 |

---

### คำถามท้ายการทดลอง (Post-Lab Questions)

#### 1. Association ID (AID) คืออะไร มีบทบาทอย่างไรใน Phase 3 และส่งคืนมาในโครงสร้างข้อมูลตัวแปรใด?
**ตอบ:** AID คืออะไร: หมายเลขประจำตัว 16-bit ที่ Access Point (AP) ออกให้กับ Station (ESP32) แต่ละตัวแบบเฉพาะเจาะจง

บทบาทใน Phase 3: ใช้ระบุตัวตนของลูกข่ายในระดับ Link Layer เพื่อจัดการบัฟเฟอร์ข้อมูล และใช้ในระบบประหยัดพลังงาน (Traffic Indication Map: TIM) เพื่อบอกว่า AP มีแพ็กเก็ตฝากไว้ให้ลูกข่ายตัวนี้หรือไม่

โครงสร้างตัวแปรที่ส่งคืน: สมาชิก aid ในโครงสร้าง wifi_event_sta_connected_t (รับผ่าน Event Data ของ WIFI_EVENT_STA_CONNECTED)

#### 2. เหตุใดการเชื่อมต่อ Wi-Fi ความปลอดภัยแบบ WPA2-PSK จึงสามารถผ่าน Phase 2 (Authentication) และ Phase 3 (Association) จนเกิด Event `WIFI_EVENT_STA_CONNECTED` ได้สำเร็จ แม้ผู้ใช้จะป้อนรหัสผ่าน (Password) ผิด?
**ตอบ:** เพราะในมาตรฐาน WPA2-PSK:

Phase 2 & 3 (Open System): ใช้ระบบ Open System Authentication ซึ่งทำหน้าที่เพียงแค่ลงทะเบียนเชื่อมต่อทางกายภาพในระดับ Link Layer (MAC Layer) โดยไม่มีการนำรหัสผ่าน (PSK) มาตรวจสอบในขั้นตอนนี้ จึงเชื่อมต่อสำเร็จและส่งผลให้เกิด Event WIFI_EVENT_STA_CONNECTED ทันที

การตรวจรหัสผ่านทำใน Phase 4 (4-Way Handshake): การนำรหัสผ่านไปคำนวณและตรวจสอบคีย์เข้ารหัสร่วมกัน (PTK) จะเกิดขึ้นหลังจาก Phase 3 เสร็จสิ้นแล้วเท่านั้น หากใส่รหัสผ่านผิดจึงจะไปล้มเหลวและถูกตัดการเชื่อมต่อในขั้นตอน 4-Way Handshake ในภายหลัง

#### 3. หาก Router มีการตั้งค่า MAC Address Filtering (อนุญาตเฉพาะ MAC ที่ลงทะเบียน) ESP32 จะล้มเหลวในเฟสใด และจะส่ง Disconnect Reason Code ใดออกมา?
**ตอบ:** ล้มเหลวในเฟส: Phase 3 (Association Phase) หรือ Phase 2 (Authentication Phase) ขึ้นอยู่กับการตั้งค่าและการตอบสนองของ Router แต่ส่วนใหญ่ Router จะปฏิเสธตั้งแต่การส่งคำขอเชื่อมโยงเครือข่าย (Association Request)

Disconnect Reason Code ที่ส่งออกมา:

Reason Code 12 (WIFI_REASON_ASSOC_DENIED_TOOMANY หรือ WIFI_REASON_ASSOC_NOT_AUTHED / AP ปฏิเสธการจับคู่) หรือ

Reason Code 15 (WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT) ในกรณีที่ Router เลือกดรอปเฟรมเงียบๆ ไม่ตอบรับกลับมาจนระบบหมดเวลา

#### 4. สรุปความแตกต่างสำคัญระหว่างจุดสิ้นสุดของ Phase 3 (Link-Layer Connected) กับจุดสิ้นสุดของ Phase 5 (IP Address Assigned)
**ตอบ:** สิ้นสุด Phase 3 (Link-Layer Connected): ทำงานในระดับ Layer 2 (Data Link Layer) โดยเชื่อมโยงสัญญาณวิทยุและผูกสัมพันธ์ (Association) กับ AP สำเร็จ ได้รับค่า AID แต่ยังส่งข้อมูลอินเทอร์เน็ตไม่ได้เพราะยังไม่มีหมายเลข IP

สิ้นสุด Phase 5 (IP Address Assigned): ทำงานในระดับ Layer 3 (Network Layer) โดยได้รับค่า IP Address, Subnet Mask และ Gateway จาก DHCP Server เรียบร้อยแล้ว ทำให้ระบบเครือข่าย TCP/IP สมบูรณ์และเริ่มส่งข้อมูลออกสู่อินเทอร์เน็ตได้ทันที

