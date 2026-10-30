# ใบงานที่ 5.4: กระบวนการแลกเปลี่ยนคีย์ความปลอดภัยและการจัดสรรหมายเลข IP Address (4-Way Handshake & IP Assignment Phase)

## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองใน Handshake & IP Phase

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event `WIFI_EVENT_STA_CONNECTED` (เกิด/ไม่เกิด) | Event `IP_EVENT_STA_GOT_IP` (เกิด/ไม่เกิด) | ผลการทดลอง | Disconnect Reason Code (ถ้ามี) |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.4.1** | Password ถูกต้อง | เกิดขึ้น | เกิดขึ้น | ผ่านสมบูรณ์ (Handshake & DHCP IP Success) | - |
| **5.4.2** | Password ผิด | เกิดขึ้น | ไม่เกิดขึ้น | ล้มเหลว (4-Way Handshake Failed / MIC Mismatch) | 15 (WIFI_REASON_HANDSHAKE_TIMEOUT) หรือ 204 (WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT) |

### 6.2 บันทึกข้อมูล IP Network จาก Event `IP_EVENT_STA_GOT_IP` (ข้อ 5.4.1)

| พารามิเตอร์ Network Layer | ค่าที่จัดสรรได้จริงจาก DHCP Server |
| :--- | :--- |
| **IP Address** | 192.168.1.135 |
| **Subnet Mask** | 255.255.255.0 |
| **Default Gateway** | 192.168.1.1 |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดกระบวนการ **4-Way Handshake** จึงพิสูจน์ทราบรหัสผ่าน Wi-Fi ได้โดยไม่ต้องส่งรหัสผ่าน (Passphrase) ลอยไปในอากาศเลยแม้แต่แพ็กเกจเดียว?
> **คำตอบ:** 
> กระบวนการ 4-Way Handshake ใช้หลักการ **Zero-Knowledge Proof** ร่วมกับการเข้ารหัสทางเดียว (Cryptographic Hash):
> 1. ทั้ง AP และ ESP32 จะนำรหัสผ่าน (PSK) ร่วมกับ SSID ไปแปลงเป็นคีย์หลัก **PMK (Pairwise Master Key)** ล่วงหน้าผ่านอัลกอริทึม PBKDF2
> 2. ในระหว่างเชื่อมต่อ AP จะส่งค่าสุ่ม **ANonce** มาให้ ESP32 และ ESP32 จะสร้างค่าสุ่ม **SNonce**
> 3. ESP32 นำ PMK + ANonce + SNonce + MAC Addresses มารวมกันเพื่อสร้างคีย์ **PTK (Pairwise Transient Key)** ซึ่งจะมีคีย์ย่อย KCK ใช้สร้างค่าแฮชตรวจสอบความสมบูรณ์ที่เรียกว่า **MIC (Message Integrity Code)**
> 4. ESP32 ส่งเฉพาะ SNonce และค่า MIC กลับไปในเฟรมที่ 2/4 ให้ AP ตรวจสอบ
> 5. เมื่อ AP ได้รับ จะนำ PMK ของตนมาคำนวณค่า MIC เทียบกัน หากรหัสผ่านตรงกัน ค่า MIC จะตรงกันทันที ส่งผลให้ทั้งสองฝ่ายยืนยันได้ว่าอีกฝ่ายรู้รหัสผ่านจริงโดยไม่ต้องส่งรหัสผ่านดิบออกไปในอากาศเลย

2. อธิบายบทบาทและที่มาของคีย์ **PMK (Pairwise Master Key)** และ **PTK (Pairwise Transient Key)** ว่ามีความสัมพันธ์กันอย่างไรในการเข้ารหัสเฟรมข้อมูล?
> **คำตอบ:** 
> - **PMK (Pairwise Master Key):** เป็นคีย์คงที่ขนาด 256 บิต มีที่มาจากการคำนวณฟังก์ชัน $PBKDF2(Passphrase, SSID, 4096, 256)$ ทำหน้าที่เป็น "คีย์ต้นแบบ (Master Key)" ที่เก็บเป็นความลับในตัวอุปกรณ์เพื่อใช้เป็นสารตั้งต้นในการคำนวณคีย์เซสชัน โดย PMK จะไม่ถูกนำไปใช้เข้ารหัสแพ็กเกจข้อมูลจริงโดยตรง
> - **PTK (Pairwise Transient Key):** เป็นคีย์ชั่วคราวแบบไดนามิกขนาด 512 บิตที่สร้างขึ้นใหม่ในทุกๆ เซสชันการเชื่อมต่อ ผ่านฟังก์ชัน $PRF(PMK, ANonce, SNonce, AP\_MAC, STA\_MAC)$
> - **ความสัมพันธ์ในการเข้ารหัสเฟรมข้อมูล:** PTK ถูกสร้างขึ้นโดยมี PMK เป็นตัวแปรตั้งต้น และภายในโครงสร้าง PTK จะประกอบด้วยคีย์ย่อย 3 ส่วน คือ:
>   1. **KCK (Key Confirmation Key):** ใช้คำนวณค่า MIC เพื่อยืนยันความถูกต้องในเฟรม Handshake
>   2. **KEK (Key Encryption Key):** ใช้ถอดรหัส Group Key (GTK) สำหรับมัลติคาสต์
>   3. **TK (Temporal Key):** คีย์ส่วนนี้จะถูกติดตั้งลงใน Hardware Crypto Engine เพื่อใช้เป็นกุญแจในการเข้ารหัสและถอดรหัสเฟรมข้อมูลจริง (Unicast Data Frames) ระหว่าง ESP32 กับ AP ด้วยโพรโทคอล AES-CCMP

3. เหตุใดเมื่อเราพิมพ์ Password ผิด (ข้อ 5.4.2) ESP32 จึงยังคงได้รับ Event **`WIFI_EVENT_STA_CONNECTED`** ก่อนที่จะเกิด Event **`WIFI_EVENT_STA_DISCONNECTED`** ตามมาในภายหลัง?
> **คำตอบ:** 
> เพราะกระบวนการเชื่อมต่อถูกแบ่งออกเป็น 2 ชั้นอย่างชัดเจน:
> 1. ในช่วงแรก ESP32 ส่งคำร้องขอใน **Phase 2 (Open Authentication)** และ **Phase 3 (Association)** ซึ่งกระบวนการทั้งสองนี้ทำหน้าที่เพียงตรวจสอบการสื่อสารคลื่นวิทยุระดับ L2 และกำหนด AID เท่านั้น โดยยังไม่มีการตรวจสอบรหัสผ่าน เมื่อ AP ตอบรับในเฟส 3 ตัว Wi-Fi Driver ของ ESP-IDF จึงปล่อย Event **`WIFI_EVENT_STA_CONNECTED`** ออกมาตามลำดับขั้นตอน
> 2. จากนั้นระบบจึงก้าวเข้าสู่ **Phase 4 (4-Way Handshake)** เมื่อ ESP32 ได้รับ ANonce จากเฟรม 1/4 แต่เนื่องจากรหัสผ่านผิด ทำให้ค่า PMK ผิด จึงส่งผลให้ค่า **MIC (Message Integrity Code)** ในเฟรม 2/4 ที่ส่งกลับไปคำนวณออกมาไม่ถูกต้อง
> 3. เมื่อ AP ตรวจพบว่า MIC ไม่ตรงกัน AP จะไม่ส่งเฟรม 3/4 และปฏิเสธการติดตั้งคีย์ เมื่อรอจนหมดเวลา (Timeout) AP หรือ ESP32 จะส่งเฟรมตัดการเชื่อมต่อ (Deauthentication) ออกมา ทำให้ระบบได้รับ Event **`WIFI_EVENT_STA_DISCONNECTED`** (Reason Code `15` หรือ `204`) ตามมาในภายหลัง

4. หากเครือข่าย Wi-Fi ไม่มี DHCP Server (ไม่มีการแจก IP อัตโนมัติ) ผลการทดลองในข้อ 5.4.1 จะหยุดอยู่ที่ขั้นตอนใด และจะไม่เกิด Event ใดขึ้น?
> **คำตอบ:** 
> - กระบวนการเชื่อมต่อจะ **สำเร็จสมบูรณ์จนจบ Phase 4 (4-Way Handshake)** โดยเกิด Event `WIFI_EVENT_STA_CONNECTED` และติดตั้งคีย์ PTK เข้ารหัสพอร์ตข้อมูลเรียบร้อยแล้ว
> - แต่การทำงานจะ **หยุดชะงักอยู่ที่จุดเริ่มต้นของ Phase 5 (IP Assignment Phase)** โดยตัวโปรแกรมลูกข่าย DHCP Client (lwIP) ของ ESP32 จะส่งแพ็กเกจบรอดคาสต์ `DHCP Discover` ออกไปตามรอบเวลาเพื่อค้นหา DHCP Server แต่จะไม่ได้รับการตอบกลับแพ็กเกจ `DHCP Offer` ใดๆ
> - **Event ที่จะไม่เกิดขึ้นเลยคือ `IP_EVENT_STA_GOT_IP`** ส่งผลให้อุปกรณ์ไม่ได้รับ IP Address, Subnet Mask และ Gateway และฟังก์ชัน `xEventGroupWaitBits` จะติดค้างรอจนหมดเวลา Timeout 
> *(ในการแก้ปัญหาสำหรับเครือข่ายที่ไม่มี DHCP ผู้พัฒนาจะต้องปิด DHCP Client และกำหนดหมายเลข Static IP Address ให้กับ Network Interface ด้วยฟังก์ชัน `esp_netif_set_ip_info()` แทน)*
