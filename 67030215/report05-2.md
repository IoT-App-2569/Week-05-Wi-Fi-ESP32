6. ตารางบันทึกผลการทดลอง (Experiment Results)
ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

6.1 ตารางสรุปเปรียบเทียบผลการทดลองทั้ง 3 สถานการณ์
ข้อการทดลอง	สถานการณ์ทดสอบ	Event สุดท้ายที่ได้รับ	ผลลัพธ์ (Passed/Failed)	Reason Code (Decimal / Hex)	คำอธิบาย Reason Code
5.2.1	SSID และ Password ถูกต้อง				
5.2.2	ระบุ SSID ผิด (ไม่มีในระบบ)				
5.2.3	ระบุ SSID ถูกต้อง แต่ Password ผิด				
6.2 บันทึกข้อมูลเครือข่ายจากการเชื่อมต่อสำเร็จ (ข้อ 5.2.1)
พารามิเตอร์เครือข่าย	ค่าที่ได้รับจริงจาก DHCP
SSID	
BSSID (MAC Address)	
Channel	
IP Address	
Subnet Mask	
Default Gateway	
7. คำถามท้ายการทดลอง (Post-Lab Questions)
เหตุใดการระบุ SSID ผิด (ข้อ 5.2.2) จึงส่งผลให้เกิด Disconnect Event ด้วย Reason Code 201 (WIFI_REASON_NO_AP_FOUND) ตั้งแต่เฟส Scan?
เหตุใดการพิมพ์ Password ผิด (ข้อ 5.2.3) จึงผ่านเฟส Auth และ Assoc มาได้ แต่มาล้มเหลวในเฟส 4-Way Handshake (Reason Code 15 หรือ 204)?
ลำดับการเกิด Event ระหว่าง WIFI_EVENT_STA_CONNECTED กับ IP_EVENT_STA_GOT_IP Event ใดเกิดขึ้นก่อนกัน และมีความหมายทางกายภาพของ Layer Network ต่างกันอย่างไร?
สมาชิกตัวแปร reason ในโครงสร้าง wifi_event_sta_disconnected_t มีประโยชน์อย่างไรต่อการออกแบบระบบค้นหาสาเหตุและกู้คืนการเชื่อมต่อ (Auto-Reconnection Mechanism) ในแอปพลิเคชัน IoT?
