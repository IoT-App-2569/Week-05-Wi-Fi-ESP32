
---
## 01-Phase-of-WiFi-Connection.md
## คำถามทบทวนความเข้าใจ (Checkpoints)
1. เหตุใดการเกิด Event `WIFI_EVENT_STA_CONNECTED` จึงยัง**ไม่เพียงพอ**ที่จะเริ่มส่งข้อมูลไปยังเว็บเซิร์ฟเวอร์ภายนอกได้?
	- Event WIFI_EVENT_STA_CONNECTED เสร็จแค่ในเฟสที่ 4 คือ ต่อสำเร็จในระดับ Link Layer ตัวอุปกรณ์และ AP สามารถตกลงคีย์เข้ารหัสกันได้แล้ว เเต่ยังขาด IP Address  Subnet Mask เเละ Default Gateway ที่ได้จาก DHCP Server  ทำให้ TCP/IP Stack ไม่สามารถค้นหาชื่อโดเมน  เพื่อส่งข้อมูลออกไปยังเว็บเซิร์ฟเวอร์ภายนอกได้ ต้องรอให้เกิด Event IP_EVENT_STA_GOT_IP ก่อน 
2. หากพิมพ์รหัสผ่าน Wi-Fi ผิด กระบวนการเชื่อมต่อจะหลุดและแจ้ง Error ในเฟสใด?
	- เฟสที่ 4: Four-way Handshake Phase
3. ระบบ Event Loop มีข้อดีอย่างไรเมื่อเทียบกับการเขียนโค้ดแบบวนลูปเช็กสถานะ (Polling loop)?
	- CPU ไม่ต้องรอวนลูปเช็กค่าว่างๆ สามารถนำเวลาไปวิ่ง Task อื่นๆหรือเข้าโหมดประหยัดพลังงานได้ หรือเมื่อเกิด event ในระดับฮาร์ดแวร์หรือเครือข่าย ระบบจะเรียก Handler ขึ้นมาทำงานทันที ไม่ต้องรอครบรอบเวลาสแกนแบบ Polling

---

## 02-1-Scan-phase.md
---
##  คำถามทบทวนความเข้าใจ (Checkpoints)

1. การสแกนแบบ **Active Scanning** กับ **Passive Scanning** ต่างกันอย่างไรในแง่ของปริมาณ Traffic บนอากาศและเวลาที่ใช้?
	- Traffic
	    - Active Scanning สูงกว่า เพราะ จะต้อง Probe Request Frame ออกไปทุก Channel
	    - Passive Scanning ต่ำกว่า เพราะ ไม่ส่ง Frame ออกอากาศเลย ทำแค่ Listen สัญญาณ
	- เวลา
		- Active Scanning เร็วกว่า เพราะส่ง Probe Request Fram ออกไปและรอ Probe Response จาก AP ได้ทันทีโดยไม่ต้องรอกรอบเวลา
		- Passive Scanning นานกว่า เพราะต้องคอยสลับ Channel แล้วรอเฟรมประกาศ ที่ AP จะส่งออกมาตามรอบเวลา
2. หาก ESP32 รองรับเฉพาะความถี่ 2.4GHz แต่เราพยายามเชื่อมต่อกับ Router 5GHz จะเกิด Event ใด และได้ Reason Code อะไร?
	เกิด Event WIFI_EVENT_STA_DISCONNECTED ได้รับรหัส WIFI_REASON_NO_AP_FOUND (0x201 / Value 201)

---

