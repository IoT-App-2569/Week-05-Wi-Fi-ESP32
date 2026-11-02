### ผลลัพธ์จาก Serial Monitor (ESP-IDF Console)

```text
I (1300) LAB5_4_HANDSHAKE: ==================================================================
I (1300) LAB5_4_HANDSHAKE:   Lab 5.4: 4-Way Handshake & IP Assignment Phase (ESP-IDF Forensic)
I (1310) LAB5_4_HANDSHAKE: ==================================================================
I (1320) LAB5_4_HANDSHAKE: --- Experiment 5.4.1: Handshake & IP Test - Correct Password ---
I (1330) LAB5_4_HANDSHAKE: [FORENSIC]: Call esp_wifi_connect()
I (1850) LAB5_4_HANDSHAKE: [EVENT]: WIFI_EVENT_STA_CONNECTED (Phase 3 Completed)
I (1860) LAB5_4_HANDSHAKE: [FORENSIC]: Entering Phase 4: 4-Way Handshake (EAPOL Keys Exchange)
I (2120) LAB5_4_HANDSHAKE: [FORENSIC]: 4-Way Handshake Successful (PTK Installed to Hardware)
I (2130) LAB5_4_HANDSHAKE: [FORENSIC]: Entering Phase 5: DHCP Client IP Acquisition
I (3240) LAB5_4_HANDSHAKE: [EVENT]: IP_EVENT_STA_GOT_IP (IP: 192.168.1.105, GW: 192.168.1.1)
I (3250) LAB5_4_HANDSHAKE: Network Ready for TCP/IP Communication.
------------------------------------------------------------------
I (5300) LAB5_4_HANDSHAKE: --- Experiment 5.4.2: Handshake Test - Incorrect Password ---
I (5310) LAB5_4_HANDSHAKE: [FORENSIC]: Call esp_wifi_connect(PASS="WRONG_PASSWORD_1234")
I (5850) LAB5_4_HANDSHAKE: [EVENT]: WIFI_EVENT_STA_CONNECTED (Phase 3 Completed)
I (5860) LAB5_4_HANDSHAKE: [FORENSIC]: Entering Phase 4: 4-Way Handshake
W (8400) LAB5_4_HANDSHAKE: [EVENT]: WIFI_EVENT_STA_DISCONNECTED (Reason: 15 / 0x0F)
W (8410) LAB5_4_HANDSHAKE: Disconnect Reason: WIFI_REASON_HANDSHAKE_TIMEOUT (MIC Mismatch)
```

---

### ตารางบันทึกผลการทดลอง

#### 1. ตารางสรุปเปรียบเทียบผลการทดลองใน Handshake & IP Phase

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event `WIFI_EVENT_STA_CONNECTED` (เกิด/ไม่เกิด) | Event `IP_EVENT_STA_GOT_IP` (เกิด/ไม่เกิด) | ผลการทดลอง | Disconnect Reason Code (ถ้ามี) |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.4.1** | Password ถูกต้อง | เกิด | เกิด | สำเร็จ (Connected & Got IP) | - |
| **5.4.2** | Password ผิด | เกิด | ไม่เกิด | ล้มเหลวที่ Handshake | 15 / 0x0F (WIFI_REASON_HANDSHAKE_TIMEOUT) |

#### 2. บันทึกข้อมูล IP Network จาก Event `IP_EVENT_STA_GOT_IP` (ข้อ 5.4.1)

| พารามิเตอร์ Network Layer | ค่าที่จัดสรรได้จริงจาก DHCP Server |
| :--- | :--- |
| **IP Address** | 192.168.1.105 |
| **Subnet Mask** | 255.255.255.0 |
| **Default Gateway** | 192.168.1.1 |

---

### คำถามท้ายการทดลอง (Post-Lab Questions)

#### 1. เหตุใดกระบวนการ 4-Way Handshake จึงพิสูจน์ทราบรหัสผ่าน Wi-Fi ได้โดยไม่ต้องส่งรหัสผ่าน (Passphrase) ลอยไปในอากาศเลยแม้แต่แพ็กเกจเดียว?
**ตอบ:** เพราะใช้หลักการสร้างคีย์ร่วมกัน (Derived Keys):

ทั้งสองฝั่งมี PMK (คำนวณจาก Password + SSID) อยู่ในเครื่องตนเองอยู่แล้ว

ทั้งคู่แลกเปลี่ยนเฉพาะค่าสุ่ม (ANonce และ SNonce) ลอยผ่านอากาศเพื่อนำไปคำนวณเป็นคีย์ชั่วคราว PTK

การพิสูจน์ทำโดยส่งค่าแฮชตรวจสอบความถูกต้อง (MIC) แนบไปกับข้อความ หากรหัสผ่านตรงกัน ค่า MIC ที่คำนวณได้จะตรงกัน ทำให้ยืนยันความถูกต้องได้โดยไม่ต้องส่งรหัสผ่านจริงออกไปในอากาศ

#### 2. อธิบายบทบาทและที่มาของคีย์ PMK (Pairwise Master Key) และ PTK (Pairwise Transient Key) ว่ามีความสัมพันธ์กันอย่างไรในการเข้ารหัสเฟรมข้อมูล?
**ตอบ:** ที่มาและความสัมพันธ์:

PMK (Master Key): ได้มาจากการนำรหัสผ่าน (Passphrase) มารวมกับ SSID ผ่านฟังก์ชัน PBKDF2 เพื่อเป็นคีย์หลักตั้งต้น

PTK (Transient Key): ถูกสร้างขึ้นมาจาก PMK ผสมกับค่าสุ่ม (ANonce, SNonce) และ MAC Address ของทั้งสองฝั่งในกระบวนการ 4-Way Handshake

บทบาทในการเข้ารหัสเฟรม: PMK จะไม่ถูกนำไปใช้เข้ารหัสข้อมูลโดยตรง แต่ทำหน้าที่เป็นฐานเพื่อผลิต PTK ซึ่งจะถูกแบ่งส่วนย่อยไปใช้ยืนยันความถูกต้องของแพ็กเก็ต (KCK) และใช้เข้ารหัส/ถอดรหัสเฟรมข้อมูล (TK) ที่ส่งผ่าน Wi-Fi จริง

#### 3. เหตุใดเมื่อเราพิมพ์ Password ผิด (ข้อ 5.4.2) ESP32 จึงยังคงได้รับ Event `WIFI_EVENT_STA_CONNECTED` ก่อนที่จะเกิด Event `WIFI_EVENT_STA_DISCONNECTED` ตามมาในภายหลัง?
**ตอบ:** เพราะ Event WIFI_EVENT_STA_CONNECTED แจ้งเตือนเมื่อจบขั้นตอน Link Layer (Phase 2 & 3: Open Auth & Association) สำเร็จ ซึ่งขั้นตอนนี้ไม่ได้ใช้รหัสผ่านในการตรวจสอบ

หลังจากนั้นระบบจึงเข้าสู่ Phase 4 (4-Way Handshake) เพื่อนำรหัสผ่านไปคำนวณและยืนยันคีย์ เมื่อรหัสผ่านไม่ถูกต้อง ค่าตรวจสอบ (MIC) จึงไม่ตรงกันและเกิด Timeout ระบบจึงสั่งตัดการเชื่อมต่อและส่ง Event WIFI_EVENT_STA_DISCONNECTED ตามมาทีหลัง

#### 4. หากเครือข่าย Wi-Fi ไม่มี DHCP Server (ไม่มีการแจก IP อัตโนมัติ) ผลการทดลองในข้อ 5.4.1 จะหยุดอยู่ที่ขั้นตอนใด และจะไม่เกิด Event ใดขึ้น?
**ตอบ:** หยุดอยู่ที่ขั้นตอน: สิ้นสุดกระบวนการ 4-Way Handshake (Phase 4) และค้างอยู่ในสถานะรอรับ IP จาก DHCP Client (Phase 5)

จะไม่เกิด Event: IP_EVENT_STA_GOT_IP