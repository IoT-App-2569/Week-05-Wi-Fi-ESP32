# ใบงานที่ 5.3: การยืนยันตัวตนและการผูกสัมพันธ์ในระดับ Link Layer (Authentication & Association Phase)

## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองในระดับ Link Layer

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event ที่ได้รับ | ผลการผูกสัมพันธ์ Link Layer | ค่า Association ID (AID) ที่ได้ | Reason Code (ถ้ามี) |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.3.1** | ร้องขอ Auth & Assoc กับ AP มีอยู่จริง | WIFI_EVENT_STA_CONNECTED | สำเร็จ (Link-Layer Association Complete) | 1 | - |
| **5.3.2** | ร้องขอ Auth & Assoc กับ AP ไม่มีอยู่จริง | WIFI_EVENT_STA_DISCONNECTED | ล้มเหลว (Failed at Targeting/Scan Phase) | - | 201 (WIFI_REASON_NO_AP_FOUND) |

### 6.2 บันทึกข้อมูล Link Layer จาก Event `WIFI_EVENT_STA_CONNECTED` (ข้อ 5.3.1)

| พารามิเตอร์ Link Layer | ค่าที่อ่านได้จริงจาก Forensic Log |
| :--- | :--- |
| **SSID** | IoT_SmartLab_2.4G |
| **BSSID (MAC Address)** | B0:A7:32:15:4D:2C |
| **Channel** | 6 |
| **Auth Mode Enum** | 3 (WIFI_AUTH_WPA2_PSK) |
| **Association ID (AID)** | 1 |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. **Association ID (AID)** คืออะไร มีบทบาทอย่างไรใน Phase 3 และส่งคืนมาในโครงสร้างข้อมูลตัวแปรใด?
> **คำตอบ:** 
> **Association ID (AID)** คือหมายเลขระบุตัวตนประจำอุปกรณ์ขนาด 16 บิต (มีค่าตั้งแต่ 1 ถึง 2007) ที่ Access Point (AP) จัดสรรและส่งมอบให้แก่สเตชันผ่านเฟรม **802.11 Association Response** 
> - **บทบาทของ AID ใน Phase 3:** ใช้เป็นดัชนีระบุตัวตนของไคลเอนต์เพื่อจัดการบัฟเฟอร์ข้อมูลบน AP และมีความสำคัญอย่างยิ่งต่อกลไกการประหยัดพลังงาน (Power Save Mode) โดย AP จะใช้ AID แมปกับโครงสร้าง **Traffic Indication Map (TIM)** ภายในบีคอน เพื่อแจ้งให้ ESP32 ที่อยู่ในโหมดหลับ (Sleep) ทราบว่ามีแพ็กเกจข้อมูลที่ถูกพักรอส่งถึงตนหรือไม่
> - **ตัวแปรโครงสร้างที่ส่งคืน:** ส่งคืนมาในตัวแปรสมาชิก `aid` ของโครงสร้าง `wifi_event_sta_connected_t` (เข้าถึงผ่าน `event->aid`) เมื่อเกิด Event `WIFI_EVENT_STA_CONNECTED`

2. เหตุใดการเชื่อมต่อ Wi-Fi ความปลอดภัยแบบ WPA2-PSK จึงสามารถผ่าน Phase 2 (Authentication) และ Phase 3 (Association) จนเกิด Event `WIFI_EVENT_STA_CONNECTED` ได้สำเร็จ แม้ผู้ใช้จะป้อนรหัสผ่าน (Password) ผิด?
> **คำตอบ:** 
> เนื่องจากสถาปัตยกรรมมาตรฐาน IEEE 802.11 ออกแบบให้แยกขั้นตอน **Link-Layer Establishment** ออกจาก **Security Authentication**:
> - ใน **Phase 2 (Authentication):** ใช้โหมด **Open System Authentication** ซึ่งเป็นการแลกเปลี่ยนเฟรม Auth Request/Response เพียง 2 เฟรมเพื่อยืนยันสถานะความพร้อมของวิทยุ โดยไม่มีการตรวจสอบรหัสผ่านใดๆ
> - ใน **Phase 3 (Association):** สเตชันส่งความสามารถของระบบ (Supported Rates, Capabilities) ไปยัง AP และ AP ตอบรับพร้อมกำหนดค่า AID ให้
> เมื่อเสร็จสิ้นเฟส 3 Wi-Fi Driver ของ ESP32 จะถือว่าการผูกสัมพันธ์ระดับ Link Layer สมบูรณ์ จึงสร้าง Event `WIFI_EVENT_STA_CONNECTED` ทันที ส่วนรหัสผ่าน (PSK) นั้นจะถูกนำไปใช้ในกระบวนการ 4-Way Handshake ใน Phase 4 ถัดไปเท่านั้น ดังนั้นแม้รหัสผ่านจะผิด ระบบก็จะยังผ่าน Phase 2 และ 3 ได้เสมอ

3. หาก Router มีการตั้งค่า **MAC Address Filtering** (อนุญาตเฉพาะ MAC ที่ลงทะเบียน) ESP32 จะล้มเหลวในเฟสใด และจะส่ง Disconnect Reason Code ใดออกมา?
> **คำตอบ:** 
> การเชื่อมต่อจะล้มเหลวตั้งแต่ **Phase 2: Authentication Phase** (หรือในบางเราเตอร์จะปฏิเสธใน **Phase 3: Association Phase**) 
> - **พฤติกรรม:** เมื่อ ESP32 ส่งเฟรม 802.11 Authentication Request ไปยัง AP ตัว AP จะนำ Source MAC Address ของ ESP32 ไปเทียบกับตาราง Whitelist/Blacklist เมื่อพบว่าไม่ได้ลงทะเบียนไว้ AP จะส่งเฟรม Auth Response (หรือ Assoc Response) ที่ระบุ Status Code ปฏิเสธ (Status: Failure/Denied) กลับมา
> - **Disconnect Reason Code ที่ได้รับ:** ESP32 จะตัดการเชื่อมต่อและส่ง Event `WIFI_EVENT_STA_DISCONNECTED` พร้อม Reason Code **`202` (`WIFI_REASON_AUTH_FAIL`)** หรือ Reason Code **`203` (`WIFI_REASON_ASSOC_FAIL`)**

4. สรุปความแตกต่างสำคัญระหว่างจุดสิ้นสุดของ **Phase 3 (Link-Layer Connected)** กับจุดสิ้นสุดของ **Phase 5 (IP Address Assigned)**
> **คำตอบ:** 
> | มิติการเปรียบเทียบ | จุดสิ้นสุดของ Phase 3 (Link-Layer Connected) | จุดสิ้นสุดของ Phase 5 (IP Address Assigned) |
> | :--- | :--- | :--- |
> | **Event ที่ถูกกระตุ้น** | `WIFI_EVENT_STA_CONNECTED` | `IP_EVENT_STA_GOT_IP` |
> | **ระดับชั้นสถาปัตยกรรม** | Data Link Layer (Layer 2) | Network Layer (Layer 3) |
> | **สถานะทางความปลอดภัย** | จับคู่คลื่นวิทยุได้และได้ AID แล้ว แต่ยังไม่มีคีย์เข้ารหัส (พอร์ตข้อมูลยังถูกบล็อกโดย 802.1X) | แลกเปลี่ยนคีย์ 4-Way Handshake สำเร็จ พอร์ตข้อมูลเปิดรับส่งเฟรมข้อมูลที่เข้ารหัส AES-CCMP ได้ |
> | **สถานะการรับส่งข้อมูล** | ยังไม่สามารถส่งข้อมูลอินเทอร์เน็ตหรือ TCP/IP ได้ | ได้รับ IP, Netmask, Gateway และ DNS พร้อมส่งข้อมูล TCP/UDP, HTTP, MQTT ออกสู่อินเทอร์เน็ตได้สมบูรณ์ |
