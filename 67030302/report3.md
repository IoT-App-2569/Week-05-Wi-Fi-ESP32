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

### 6.3 ผลลัพธ์จาก Serial Monitor Console (Forensic Output Log)

```text
I (516) main_task: Calling app_main()
I (516) LAB_AUTH_ASSOC: [FORENSIC]: Call nvs_flash_init()
I (536) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_netif_init()
I (546) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_event_loop_create_default()
I (546) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (556) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_init(&cfg)
I (576) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (586) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (596) LAB_AUTH_ASSOC: ==================================================================
I (596) LAB_AUTH_ASSOC:   Lab 5.3: Wi-Fi Authentication & Association Phase (ESP-IDF Forensic)
I (606) LAB_AUTH_ASSOC: ==================================================================

I (606) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (616) LAB_AUTH_ASSOC: >>> Experiment 5.3.1: Link-Layer Auth & Assoc Phase Test
I (616) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (626) LAB_AUTH_ASSOC:   Target SSID    : "IoT_SmartLab_2.4G"
I (626) LAB_AUTH_ASSOC:   Target Password: "Correct_Password_123"
I (636) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_stop()
I (646) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (656) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_start()
I (726) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (726) LAB_AUTH_ASSOC: [FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...
I (736) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (746) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (2480) LAB_AUTH_ASSOC: =======================================================
I (2480) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (2480) LAB_AUTH_ASSOC:   [SUCCESS]: Phase 2 (Auth) & Phase 3 (Assoc) COMPLETED!
I (2490) LAB_AUTH_ASSOC:   -> Connected SSID        : IoT_SmartLab_2.4G
I (2490) LAB_AUTH_ASSOC:   -> BSSID (MAC Address)   : B0:A7:32:15:4D:2C
I (2500) LAB_AUTH_ASSOC:   -> Channel               : 6
I (2500) LAB_AUTH_ASSOC:   -> Auth Mode             : 3
I (2510) LAB_AUTH_ASSOC:   -> Association ID (AID)  : 1
I (2510) LAB_AUTH_ASSOC: =======================================================
I (2520) LAB_AUTH_ASSOC: [RESULT]: TEST PASSED - Phase 2 (Auth) & Phase 3 (Assoc) Successful!

I (4530) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (4530) LAB_AUTH_ASSOC: >>> Experiment 5.3.2: Link-Layer Test - Non-Existent AP
I (4540) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (4540) LAB_AUTH_ASSOC:   Target SSID    : "NON_EXISTENT_AP_9999"
I (4550) LAB_AUTH_ASSOC:   Target Password: "12345678"
I (4550) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_stop()
I (4560) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (4570) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_start()
I (4640) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (4640) LAB_AUTH_ASSOC: [FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...
I (4650) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
W (7180) LAB_AUTH_ASSOC: =======================================================
W (7180) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (7190) LAB_AUTH_ASSOC:   -> Target SSID          : NON_EXISTENT_AP_9999
W (7190) LAB_AUTH_ASSOC:   -> Reason Code (Decimal): 201
W (7200) LAB_AUTH_ASSOC:   -> Reason Code (Hex)    : 0xC9
W (7200) LAB_AUTH_ASSOC:   -> Reason Diagnosis     : WIFI_REASON_NO_AP_FOUND (201) [Phase 1: SSID Not Found]
W (7210) LAB_AUTH_ASSOC: =======================================================
W (7210) LAB_AUTH_ASSOC: [RESULT]: TEST FAILED - Link-Layer connection failed.
I (7220) LAB_AUTH_ASSOC: ==================================================================
I (7220) LAB_AUTH_ASSOC:   [Phase 2 & Phase 3 Completed: Link-Layer Auth & Assoc Finished]
I (7230) LAB_AUTH_ASSOC: ==================================================================
```

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
