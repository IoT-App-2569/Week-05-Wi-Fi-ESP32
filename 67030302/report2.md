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
