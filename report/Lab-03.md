## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองในระดับ Link Layer

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event ที่ได้รับ | ผลการผูกสัมพันธ์ Link Layer | ค่า Association ID (AID) ที่ได้ | Reason Code (ถ้ามี) |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.3.1** | ร้องขอ Auth & Assoc กับ AP มีอยู่จริง | `WIFI_EVENT_STA_CONNECTED` | สำเร็จ (PASSED) | 34680 | - |
| **5.3.2** | ร้องขอ Auth & Assoc กับ AP ไม่มีอยู่จริง | `WIFI_EVENT_STA_DISCONNECTED` | ล้มเหลว (FAILED) | - | 201 / 0xC9 (WIFI_REASON_NO_AP_FOUND) |


### 6.2 บันทึกข้อมูล Link Layer จาก Event `WIFI_EVENT_STA_CONNECTED` (ข้อ 5.3.1)

| พารามิเตอร์ Link Layer | ค่าที่อ่านได้จริงจาก Forensic Log |
| :--- | :--- |
| **SSID** | Pornprom |
| **BSSID (MAC Address)** | 2E:FE:61:42:3D:24 |
| **Channel** | 6 |
| **Auth Mode Enum** | 3 |
| **Association ID (AID)** | 34680 |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. **Association ID (AID)** คืออะไร มีบทบาทอย่างไรใน Phase 3 และส่งคืนมาในโครงสร้างข้อมูลตัวแปรใด?

```
Association ID คือหมายเลขประจำตัวที่ Access Point กำหนดให้กับ Station แต่ละเครื่องเมื่อทำการ Association สำเร็จ เพื่อใช้ระบุตัวตนและจัดการการส่งข้อมูลภายในเครือข่าย BSS ค่านี้จะถูกส่งคืนมาในสมาชิกตัวแปรชื่อ `aid` ของโครงสร้างข้อมูล `wifi_event_sta_connected_t`
```

2. เหตุใดการเชื่อมต่อ Wi-Fi ความปลอดภัยแบบ WPA2-PSK จึงสามารถผ่าน Phase 2 (Authentication) และ Phase 3 (Association) จนเกิด Event WIFI_EVENT_STA_CONNECTED ได้สำเร็จ แม้ผู้ใช้จะป้อนรหัสผ่าน (Password) ผิด?

```
เพราะการเชื่อมต่อแบบ WPA2-PSK ในช่วง Phase 2 จะใช้การยืนยันตัวตนแบบ Open System Authentication ซึ่งเป็นการเปิดรับการเชื่อมต่อเบื้องต้นเสมอโดยไม่มีการถามรหัสผ่าน ส่วน Phase 3 ก็เป็นการตอบรับเข้าร่วมเครือข่ายระดับ Link-Layer เท่านั้น การตรวจสอบความถูกต้องของรหัสผ่านจริงๆ จะไปเกิดขึ้นในขั้นตอนการเข้ารหัส หรือ 4-Way Handshake ดังนั้นอุปกรณ์จึงสามารถผ่าน Phase 2 และ 3 จนเกิด Event เชื่อมต่อระดับ Link-Layer ได้สำเร็จแม้รหัสจะผิดก็ตาม
```

3. หาก Router มีการตั้งค่า MAC Address Filtering (อนุญาตเฉพาะ MAC ที่ลงทะเบียน) ESP32 จะล้มเหลวในเฟสใด และจะส่ง Disconnect Reason Code ใดออกมา?

```
ESP32 จะล้มเหลวในเฟส 2  ทันที เนื่องจาก AP จะทำการตรวจสอบ MAC Address ของอุปกรณ์ที่พยายามเข้ามาเกาะ และจะปฏิเสธการยืนยันตัวตน  โดยมักจะส่ง Disconnect Reason Code ออกมาเป็น WIFI_REASON_AUTH_FAIL
```

4. สรุปความแตกต่างสำคัญระหว่างจุดสิ้นสุดของ Phase 3 (Link-Layer Connected) กับจุดสิ้นสุดของ Phase 5 (IP Address Assigned)

```
จุดสิ้นสุดของ Phase 3 (เกิด Event WIFI_EVENT_STA_CONNECTED) หมายถึงอุปกรณ์สามารถเชื่อมต่อคลื่นวิทยุ และเป็นส่วนหนึ่งของเครือข่ายไร้สาย  สำเร็จแล้ว แต่จะยังไม่สามารถใช้อินเทอร์เน็ตได้
ส่วนจุดสิ้นสุดของ Phase 5 (เกิด Event IP_EVENT_STA_GOT_IP) หมายถึงอุปกรณ์ได้รับการแจกหมายเลข IP จาก DHCP
```