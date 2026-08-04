# สถาปัตยกรรมและขั้นตอนย่อยในการเชื่อมต่อ Wi-Fi ของ ESP32

ในการพัฒนาแอปพลิเคชัน IoT บน ESP32 การเข้าใจกระบวนการสถาปนาการเชื่อมต่อไร้สาย (Wi-Fi Connection Lifecycle) ถือเป็นพื้นฐานสำคัญอย่างยิ่ง เมื่อเราสั่งให้ ESP32 เชื่อมต่อกับ Access Point (AP) ไดรเวอร์ Wi-Fi ของ ESP32 จะไม่ได้เชื่อมต่อทันทีในขั้นตอนเดียว แต่จะดำเนินงานผ่าน **เฟสย่อย (Sub-phases)** ตามมาตรฐาน IEEE 802.11 และกระบวนการขอ IP Address ผ่าน TCP/IP Stack

---

## 0. บทบาททาง Hardware และประเภทข้อมูลในระบบ (Hardware Roles & Taxonomy)

ก่อนที่จะเข้าสู่ขั้นตอนการสื่อสาร ผู้เรียนควรแยกแยะบทบาทของอุปกรณ์และโปรโตคอลออกเป็น 3 ส่วนหลัก:

1. **Hardware / Device Role (อุปกรณ์และบทบาทในระบบ)**:
   - **Access Point (AP)**: อุปกรณ์แม่ข่าย/จุดเชื่อมต่อไร้สาย (เช่น Wi-Fi Router) ทำหน้าที่กระจายสัญญาณ ประกาศตัวตน และจัดสรรทรัพยากร
   - **Station (STA)**: อุปกรณ์ลูกข่ายที่ขอเชื่อมต่อเข้ากับ AP (ในที่นี้คือไมโครคอนโทรลเลอร์ **ESP32**, สมาร์ตโฟน, หรือโน้ตบุ๊ก)
2. **Protocol & Standard (ข้อกำหนดและกฎเกณฑ์การสื่อสาร)**:
   - **IEEE 802.11**: มาตรฐานการสื่อสาร Wi-Fi ระดับ Physical (PHY) และ Link Layer (MAC)
   - **WPA2 / WPA3 & EAPOL**: โปรโตคอลแลกเปลี่ยนคีย์ความปลอดภัย
   - **TCP/IP & DHCP**: โปรโตคอลการรับส่งข้อมูลและการจัดสรร IP Address ในระดับ Layer 3
3. **Data / Frame & Key (ข้อมูลที่ส่งผ่านคลื่นวิทยุ)**:
   - **Identifiers**: SSID (ชื่อ Wi-Fi), BSSID (MAC ของ AP), MAC Address (ประจำเครื่อง ESP32)
   - **Management Frames**: Beacon Frame, Probe Request/Response, Auth Frame, Assoc Frame
   - **Encryption Keys**: PSK (รหัสผ่าน), PMK, PTK, GTK

---

## 1. แผนผังลำดับขั้นตอนการทำงาน (Wi-Fi Connection State Machine)

กระบวนการเชื่อมต่อทั้งหมดสามารถสรุปเป็น State Diagram ได้ดังนี้:

```mermaid
stateDiagram-v2
    [*] --> Idle: Init Wi-Fi Driver
    Idle --> Scanning: esp_wifi_connect()
    
    state "1. Scan Phase" as Scanning
    Scanning --> Auth: พบ AP ตรงตาม Config
    Scanning --> Disconnected: หา AP ไม่พบ

    state "2. Auth Phase" as Auth
    Auth --> Association: Auth Success (802.11)
    Auth --> Disconnected: Auth Fail / Timeout

    state "3. Association Phase" as Association
    Association --> Handshake: Association Success
    Association --> Disconnected: Assoc Fail / Timeout

    state "4. Four-way Handshake Phase" as Handshake
    Handshake --> Connected: 4/4 EAPOL Completed
    Handshake --> Disconnected: Handshake Timeout / Wrong Password

    state "5. IP Assignment (DHCP)" as Connected
    Connected --> GotIP: DHCP Server แจก IP สำเร็จ (`IP_EVENT_STA_GOT_IP`)
    Connected --> Disconnected: DHCP Timeout / IP Conflict

    Disconnected --> Scanning: Retry Policy (ถ้าตั้งค่าไว้)
    GotIP --> [*]: พร้อมรับส่งข้อมูลบน Internet (Ready)
```

---

## 2. สรุปรายละเอียดของทั้ง 5 เฟสหลัก

| เฟสย่อย | คำอธิบายสั้น | สัญญาณตอบรับสำเร็จ (Success Event) | Event/Reason เมื่อล้มเหลว |
| :--- | :--- | :--- | :--- |
| **1. Scan Phase** | ไดรเวอร์ทำการสแกนหา SSID/BSSID ตามที่กำหนดใน Configuration | พบ AP Target ที่มีสัญญาณ | `WIFI_EVENT_STA_DISCONNECTED` (NO_AP_FOUND) |
| **2. Auth Phase** | เริ่มขั้นตอนตกลงสิทธิ์ (Authentication) ระหว่าง ESP32 กับ AP ในระดับ Link Layer | AP ตอบรับ Auth Frame | `WIFI_REASON_AUTH_EXPIRE` / `WIFI_REASON_AUTH_FAIL` |
| **3. Association Phase** | ส่งคำร้องขอผูกสัมพันธ์ (Association Request) เพื่อตกลง Capability และ Data Rates | AP ตอบรับ Association Response | `WIFI_REASON_ASSOC_EXPIRE` / `WIFI_REASON_ASSOC_FAIL` |
| **4. Four-way Handshake** | ทำการแลกเปลี่ยนคีย์ความปลอดภัย WPA2/WPA3 (EAPOL 1/4 ถึง 4/4) | `WIFI_EVENT_STA_CONNECTED` | `WIFI_REASON_HANDSHAKE_TIMEOUT` |
| **5. IP Assignment (DHCP)** | ขอหมายเลข IP Address, Subnet Mask, Gateway จาก DHCP Server บน AP | `IP_EVENT_STA_GOT_IP` | DHCP Timeout / Lease Failed |

---

## 3. สถาปัตยกรรม ESP-IDF Event Loop Architecture

การทำงานของ Wi-Fi บน ESP32 ขับเคลื่อนด้วยระบบ **Event-driven** ผ่าน `esp_event` loop ซึ่งแยกเป็น 2 กลุ่ม Event หลัก:

1. **`WIFI_EVENT`**: เกิดจาก Wi-Fi Driver ในระดับ H/W และ Link Layer (เช่น `STA_START`, `STA_CONNECTED`, `STA_DISCONNECTED`)
2. **`IP_EVENT`**: เกิดจาก TCP/IP Stack (lwIP) ในระดับ Network Layer (เช่น `STA_GOT_IP`, `STA_LOST_IP`)

### ตัวอย่างโครงสร้างโค้ดการจัดการ Event (Event Handler Concept)

```c
// ตัวอย่างโค้ดในรูปแบบ ESP-IDF C Conceptual Code
static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data) 
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect(); // เริ่มต้นกระบวนการ Scan & Connect
    } 
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_CONNECTED) {
        printf("Wi-Fi Link Layer Connected! Waiting for IP...\n");
    } 
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        wifi_event_sta_disconnected_t* event = (wifi_event_sta_disconnected_t*) event_data;
        printf("Disconnected! Reason code: %d\n", event->reason);
    } 
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        printf("Got IP Address: " IPSTR "\n", IP2STR(&event->ip_info.ip));
    }
}
```

---

## 4. คำถามทบทวนความเข้าใจ (Checkpoints)

1. เหตุใดการเกิด Event `WIFI_EVENT_STA_CONNECTED` จึงยัง**ไม่เพียงพอ**ที่จะเริ่มส่งข้อมูลไปยังเว็บเซิร์ฟเวอร์ภายนอกได้?

เพราะ Event นี้บ่งบอกเพียงว่าอุปกรณ์เชื่อมต่อสำเร็จใน **Layer 2 (Data Link Layer)** เท่านั้น คือผ่านขั้นตอน Authentication, Association และ 4-Way Handshake เรียบร้อยแล้ว ทำให้ส่ง/รับเฟรมข้อมูลที่เข้ารหัสกับ AP ได้ แต่อุปกรณ์ยัง**ไม่มี IP Address** ที่จะใช้สื่อสารระดับ **Layer 3 (Network Layer)** เลย จึงยังสร้าง Socket, ทำ DNS Resolution หรือส่ง Packet ไปยังเว็บเซิร์ฟเวอร์ภายนอกไม่ได้ ต้องรอจนกว่าจะได้รับ Event `IP_EVENT_STA_GOT_IP` ซึ่งยืนยันว่า DHCP จัดสรร IP Address, Subnet Mask และ Default Gateway ให้แล้ว การสื่อสารระดับ Application จึงจะเริ่มต้นได้จริง

2. หากพิมพ์รหัสผ่าน Wi-Fi ผิด กระบวนการเชื่อมต่อจะหลุดและแจ้ง Error ในเฟสใด?

จะหลุดใน **Phase 4: 4-Way EAPOL Key Exchange (Handshake)** เนื่องจากขั้นตอน Authentication และ Association (Phase 2-3) ไม่ตรวจสอบรหัสผ่าน จึงผ่านไปได้ตามปกติ แต่เมื่อเข้าสู่ 4-Way Handshake ค่า PMK ที่คำนวณจากรหัสผ่านผิดจะทำให้ PTK และ MIC ที่ ESP32 คำนวณไม่ตรงกับที่ AP คำนวณ AP จึงปฏิเสธและสั่งตัดการเชื่อมต่อ ทำให้เกิด `WIFI_EVENT_STA_DISCONNECTED` พร้อม Reason Code ที่เกี่ยวข้องกับ Auth/Handshake ล้มเหลว (เช่น `WIFI_REASON_AUTH_EXPIRE`) โดยจะไม่เกิด Event `WIFI_EVENT_STA_CONNECTED` เลยในกรณีนี้

3. ระบบ Event Loop มีข้อดีอย่างไรเมื่อเทียบกับการเขียนโค้ดแบบวนลูปเช็กสถานะ (Polling loop)?

- **ประหยัดทรัพยากร CPU**: Event Loop จะ block รอจนกว่าจะมี event เกิดขึ้นจริง ต่างจาก Polling ที่ต้องวนลูปเช็กสถานะซ้ำๆ ตลอดเวลา กิน CPU cycle โดยไม่จำเป็น (busy-waiting)
- **ตอบสนองได้ทันที (Responsive)**: เมื่อมี Event เกิดขึ้น (connect สำเร็จ, ได้ IP, disconnect) callback function ถูกเรียกทันที ไม่ต้องรอรอบถัดไปของ loop เหมือน Polling ที่อาจมี delay ตาม interval ที่ตั้งไว้
- **โครงสร้างโค้ดสะอาดและขยายง่าย (Decoupled/Scalable)**: แยก Logic การจัดการแต่ละ Event ออกจากกันชัดเจน (handler สำหรับ WIFI_EVENT กับ IP_EVENT แยกกัน) เพิ่ม/ลบ handler ได้โดยไม่กระทบส่วนอื่น ต่างจาก Polling ที่มักต้องเขียน if-else ซ้อนกันจำนวนมากในลูปเดียว
- **ประหยัดพลังงาน (Power Efficient)**: สำคัญสำหรับอุปกรณ์ Embedded/IoT ที่ใช้แบตเตอรี่ เพราะ CPU เข้าสู่โหมดประหยัดพลังงาน (idle/sleep) ได้เมื่อไม่มี Event ค้างอยู่ ต่างจาก Polling ที่ CPU ต้องทำงานตลอดเวลาแม้ไม่มีอะไรเปลี่ยนแปลง