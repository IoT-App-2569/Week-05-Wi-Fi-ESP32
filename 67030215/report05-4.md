## 6. ตารางบันทึกผลการทดลอง (Experiment Results)
```c
der_start.c:25
I (29) boot: ESP-IDF v5.5.1 2nd stage bootloader
I (29) boot: compile time Aug  3 2026 10:06:14
I (29) boot: Multicore bootloader
I (31) boot: chip revision: v3.1
I (33) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode       : DIO
I (41) boot.esp32: SPI Flash Size : 2MB
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (58) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory          factory app      00 00 00010000 00100000
I (77) boot: End of partition table
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=19ee8h (106216) map
I (124) esp_image: segment 1: paddr=00029f10 vaddr=3ffb0000 size=03eech ( 16108) load
I (130) esp_image: segment 2: paddr=0002de04 vaddr=40080000 size=02214h (  8724) load
I (134) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=861f0h (549360) map
I (323) esp_image: segment 4: paddr=000b6218 vaddr=40082214 size=15bf8h ( 89080) load
I (358) esp_image: segment 5: paddr=000cbe18 vaddr=50000000 size=00020h (    32) load
I (370) boot: Loaded app from partition at offset 0x10000
I (370) boot: Disabling RNG early entropy source...
I (381) cpu_start: Multicore app
I (389) cpu_start: Pro cpu start user code
I (389) cpu_start: cpu freq: 160000000 Hz
I (389) app_init: Application information:
I (389) app_init: Project name:     LED_Blink
I (393) app_init: App version:      1
I (397) app_init: Compile time:     Aug  6 2026 12:20:13
I (402) app_init: ELF file SHA256:  7d5525158...
I (406) app_init: ESP-IDF:          v5.5.1
I (410) efuse_init: Min chip rev:     v0.0
I (414) efuse_init: Max chip rev:     v3.99 
I (418) efuse_init: Chip rev:         v3.1
I (422) heap_init: Initializing. RAM available for dynamic allocation:
I (428) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (433) heap_init: At 3FFB7FD0 len 00028030 (160 KiB): DRAM
I (438) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (444) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (449) heap_init: At 40097E0C len 000081F4 (32 KiB): IRAM
I (456) spi_flash: detected chip: generic
I (458) spi_flash: flash io: dio
W (461) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (474) main_task: Started on CPU0
I (484) main_task: Calling app_main()
I (484) LAB_HANDSHAKE_IP: [FORENSIC]: Call nvs_flash_init()
I (504) LAB_HANDSHAKE_IP: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (504) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_netif_init()
I (504) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_loop_create_default()
I (514) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (514) LAB_HANDSHAKE_IP: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbd8bc
I (524) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_init(&cfg)
I (544) wifi:wifi driver task: 3ffbffa8, prio:23, stack:6656, core=0
I (554) wifi:wifi firmware version: 14da9b7
I (554) wifi:wifi certification version: v7.0
I (554) wifi:config NVS flash: enabled
I (554) wifi:config nano formatting: disabled
I (564) wifi:Init data frame dynamic rx buffer num: 32
I (564) wifi:Init static rx mgmt buffer num: 5
I (564) wifi:Init management short buffer num: 32
I (574) wifi:Init dynamic tx buffer num: 32
I (574) wifi:Init static rx buffer size: 1600
I (584) wifi:Init static rx buffer num: 10
I (584) wifi:Init dynamic rx buffer num: 32
I (594) wifi_init: rx ba win: 6
I (594) wifi_init: accept mbox: 6
I (594) wifi_init: tcpip mbox: 32
I (594) wifi_init: udp mbox: 6
I (604) wifi_init: tcp mbox: 6
I (604) wifi_init: tcp tx win: 5760
I (604) wifi_init: tcp rx win: 5760
I (614) wifi_init: tcp mss: 1440
I (614) wifi_init: WiFi IRAM OP enabled
I (614) wifi_init: WiFi RX IRAM OP enabled
I (624) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (624) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_handler_instance_register(IP_EVENT)
I (634) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (644) LAB_HANDSHAKE_IP: ==================================================================
I (654) LAB_HANDSHAKE_IP:   Lab 5.4: 4-Way Handshake & IP Assignment Phase (ESP-IDF Forensic)
I (654) LAB_HANDSHAKE_IP: ==================================================================
I (664) LAB_HANDSHAKE_IP: 

I (674) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (674) LAB_HANDSHAKE_IP: >>> Experiment 5.4.1: Handshake & IP Test - Correct Password
I (684) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (694) LAB_HANDSHAKE_IP:   Target SSID    : "POCO X7 Pro"
I (694) LAB_HANDSHAKE_IP:   Target Password: "1122334455"
I (704) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_stop()
I (714) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (734) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (734) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_start()
I (744) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (824) wifi:mode : sta (14:33:5c:0d:cd:7c)
I (824) wifi:enable tsf
I (824) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (824) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (824) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (834) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_connect()
I (844) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (1124) wifi:new:<4,0>, old:<1,0>, ap:<255,255>, sta:<4,0>, prof:1, snd_ch_cfg:0x0
I (1124) wifi:state: init -> auth (0xb0)
I (1124) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (1144) wifi:state: auth -> assoc (0x0)
I (1174) wifi:state: assoc -> run (0x10)
I (1194) wifi:connected with POCO X7 Pro, aid = 7, channel 4, BW20, bssid = 76:da:a8:1e:2d:ae
I (1194) wifi:security: WPA2-PSK, phy: bgn, rssi: -28
I (1204) wifi:pm start, type: 1

I (1204) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (1214) LAB_HANDSHAKE_IP: =======================================================
I (1214) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (1224) LAB_HANDSHAKE_IP:   -> Phase 2 (Auth) & Phase 3 (Assoc) PASSED
I (1224) LAB_HANDSHAKE_IP:   -> Connected SSID  : POCO X7 Pro
I (1234) LAB_HANDSHAKE_IP:   -> BSSID           : 76:DA:A8:1E:2D:AE
I (1244) LAB_HANDSHAKE_IP:   -> Channel         : 4
I (1244) LAB_HANDSHAKE_IP:   -> Association ID  : 3
I (1244) LAB_HANDSHAKE_IP: [FORENSIC]: Entering Phase 4: 4-Way EAPOL Key Exchange...
I (1254) LAB_HANDSHAKE_IP: =======================================================
I (1284) wifi:dp: 2, bi: 102400, li: 4, scale listen interval from 307200 us to 409600 us
I (1284) wifi:AP's beacon interval = 102400 us, DTIM period = 2
I (2234) esp_netif_handlers: sta ip: 10.42.102.249, mask: 255.255.255.0, gw: 10.42.102.133
I (2234) LAB_HANDSHAKE_IP: =======================================================
I (2234) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!
I (2244) LAB_HANDSHAKE_IP:   [SUCCESS]: Phase 4 (4-Way Handshake) & Phase 5 (DHCP IP) COMPLETED!
I (2254) LAB_HANDSHAKE_IP:   -> Allocated IP Address : 10.42.102.249
I (2254) LAB_HANDSHAKE_IP:   -> Subnet Mask          : 255.255.255.0
I (2264) LAB_HANDSHAKE_IP:   -> Default Gateway      : 10.42.102.133
I (2264) LAB_HANDSHAKE_IP: =======================================================
I (2274) LAB_HANDSHAKE_IP: [RESULT]: TEST PASSED - 4-Way Handshake & DHCP IP Assignment Successful!
I (4284) LAB_HANDSHAKE_IP: 

I (4284) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (4284) LAB_HANDSHAKE_IP: >>> Experiment 5.4.2: Handshake Test - Incorrect Password
I (4284) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (4294) LAB_HANDSHAKE_IP:   Target SSID    : "POCO X7 Pro"
I (4304) LAB_HANDSHAKE_IP:   Target Password: "WRONG_PASSWORD_1234"
I (4304) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_stop()
I (4314) wifi:state: run -> init (0x0)
I (4324) wifi:pm stop, total sleep time: 2633114 us / 3117871 us

I (4324) wifi:new:<4,0>, old:<4,0>, ap:<255,255>, sta:<4,0>, prof:1, snd_ch_cfg:0x0
W (4334) LAB_HANDSHAKE_IP: =======================================================
W (4334) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (4344) LAB_HANDSHAKE_IP:   -> Target SSID          : POCO X7 Pro
W (4344) LAB_HANDSHAKE_IP:   -> Reason Code (Decimal): 8
W (4354) LAB_HANDSHAKE_IP:   -> Reason Code (Hex)    : 0x08
W (4364) LAB_HANDSHAKE_IP:   -> Reason Diagnosis     : OTHER_DISCONNECT_REASON
W (4364) LAB_HANDSHAKE_IP: =======================================================
I (4374) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (4384) wifi:flush txq
I (4384) wifi:stop sw txq
I (4384) wifi:lmac stop hw txq
I (4384) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (4414) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (4414) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_start()
I (4424) wifi:mode : sta (14:33:5c:0d:cd:7c)
I (4424) wifi:enable tsf
I (4424) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (4434) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (4434) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (4444) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_connect()
I (4454) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (4714) LAB_HANDSHAKE_IP: [RESULT]: TEST FAILED - Disconnected during Handshake or Auth.
I (4714) LAB_HANDSHAKE_IP: ==================================================================
I (4714) LAB_HANDSHAKE_IP:   [Phase 4 & Phase 5 Completed: Wi-Fi Handshake & IP Lab Finished]
I (4724) wifi:new:<4,0>, old:<1,0>, ap:<255,255>, sta:<4,0>, prof:1, snd_ch_cfg:0x0
I (4734) wifi:state: init -> auth (0xb0)
I (4744) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (4744) LAB_HANDSHAKE_IP: ==================================================================
I (4754) main_task: Returned from app_main()
I (4754) wifi:state: auth -> assoc (0x0)
I (4784) wifi:state: assoc -> run (0x10)
I (7814) wifi:state: run -> init (0xf00)
I (7824) wifi:new:<4,0>, old:<4,0>, ap:<255,255>, sta:<4,0>, prof:1, snd_ch_cfg:0x0
W (7824) LAB_HANDSHAKE_IP: =======================================================
W (7824) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (7834) LAB_HANDSHAKE_IP:   -> Target SSID          : POCO X7 Pro
W (7834) LAB_HANDSHAKE_IP:   -> Reason Code (Decimal): 15
W (7844) LAB_HANDSHAKE_IP:   -> Reason Code (Hex)    : 0x0F
W (7844) LAB_HANDSHAKE_IP:   -> Reason Diagnosis     : WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT (204) [Phase 4: Wrong Password]
W (7864) LAB_HANDSHAKE_IP: =======================================================

```
ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองใน Handshake & IP Phase

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event `WIFI_EVENT_STA_CONNECTED` (เกิด/ไม่เกิด) | Event `IP_EVENT_STA_GOT_IP` (เกิด/ไม่เกิด) | ผลการทดลอง | Disconnect Reason Code (ถ้ามี) |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.4.1** | Password ถูกต้อง |มี |มี |	TEST PASSED - 4-Way Handshake & DHCP IP Assignment Successful! |ไม่มี |
| **5.4.2** | Password ผิด |ไม่มี|ไม่มี |TEST FAILED - Disconnected during Handshake or Auth. |15 (0x0F) — WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT (204) |

### 6.2 บันทึกข้อมูล IP Network จาก Event `IP_EVENT_STA_GOT_IP` (ข้อ 5.4.1)

| พารามิเตอร์ Network Layer | ค่าที่จัดสรรได้จริงจาก DHCP Server |
| :--- | :--- |
| **IP Address** |	10.42.102.249 |
| **Subnet Mask** |255.255.255.0 |
| **Default Gateway** |10.42.102.133 |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดกระบวนการ **4-Way Handshake** จึงพิสูจน์ทราบรหัสผ่าน Wi-Fi ได้โดยไม่ต้องส่งรหัสผ่าน (Passphrase) ลอยไปในอากาศเลยแม้แต่แพ็กเกจเดียว?
```c
กระบวนการ 4-Way Handshake พิสูจน์รหัสผ่านได้โดยไม่ต้องส่งรหัสผ่านจริงออกไป เพราะทั้งฝั่ง Client และ AP ต่างคำนวณ PMK จากรหัสผ่าน (Passphrase) และ SSID อยู่แล้วในเครื่องของตัวเอง จากนั้นทั้งสองฝ่ายแลกเปลี่ยนค่า Nonce แบบสุ่ม (ANonce จาก AP และ SNonce จาก Client) แล้วนำไปคำนวณ PTK ร่วมกัน สุดท้ายใช้ PTK สร้างค่า MIC (Message Integrity Code) มาแนบใน EAPOL Frame ที่ 2 หากรหัสผ่านของ Client ตรงกับของ AP ค่า PMK และ PTK ที่คำนวณได้ทั้งสองฝั่งจะเท่ากัน ทำให้ MIC ตรวจสอบผ่าน แต่ถ้ารหัสผ่านผิด ค่า PMK/PTK จะต่างกัน ทำให้ MIC ไม่ตรงกัน AP จะปฏิเสธและตัดการเชื่อมต่อ จึงพิสูจน์รหัสผ่านได้โดยไม่ต้องส่งรหัสผ่านจริงผ่านอากาศเลย
```
2. อธิบายบทบาทและที่มาของคีย์ **PMK (Pairwise Master Key)** และ **PTK (Pairwise Transient Key)** ว่ามีความสัมพันธ์กันอย่างไรในการเข้ารหัสเฟรมข้อมูล?
```c
PMK คือคีย์หลักที่คำนวณจาก Passphrase ร่วมกับ SSID ผ่านฟังก์ชัน PBKDF2 มีอายุการใช้งานตลอด Session และไม่เคยถูกส่งผ่านเครือข่ายโดยตรง ส่วน PTK คือคีย์ที่สร้างขึ้นชั่วคราวเฉพาะแต่ละ Session จาก PMK บวกกับค่า ANonce, SNonce, MAC Address ของทั้งสองฝ่าย ผ่านฟังก์ชัน PRF โดย PTK จะถูกแบ่งย่อยเป็นคีย์ย่อยอีกหลายตัว เช่น KCK (ใช้ยืนยัน MIC), KEK (ใช้เข้ารหัส GTK ตอนส่ง) และ TK (ใช้เข้ารหัส-ถอดรหัสข้อมูลจริงระหว่างสื่อสาร ด้วย CCMP/AES) กล่าวคือ PMK เป็นแม่กุญแจถาวรที่ใช้สร้าง PTK ซึ่งเป็นกุญแจชั่วคราวสำหรับเข้ารหัสข้อมูลจริงในแต่ละ Session 
```
3. เหตุใดเมื่อเราพิมพ์ Password ผิด (ข้อ 5.4.2) ESP32 จึงยังคงได้รับ Event **`WIFI_EVENT_STA_CONNECTED`** ก่อนที่จะเกิด Event **`WIFI_EVENT_STA_DISCONNECTED`** ตามมาในภายหลัง?
```c
เพราะ Event WIFI_EVENT_STA_CONNECTED ถูกยิงออกมาทันทีที่ Phase 2 (Authentication) และ Phase 3 (Association) สำเร็จ ซึ่งเป็นเพียงขั้นตอนระดับ MAC Layer ที่ตรวจสอบแค่ SSID ถูกต้องและ AP ยอมรับการเชื่อมต่อเบื้องต้นเท่านั้น ยังไม่มีการตรวจสอบรหัสผ่านจริงในขั้นนี้ การตรวจสอบรหัสผ่านจะเกิดขึ้นในภายหลังที่ Phase 4 (4-Way EAPOL Handshake) ซึ่งเมื่อ MIC ไม่ตรงกันเนื่องจากรหัสผ่านผิด AP จะตัดการเชื่อมต่อ ทำให้เกิด Event WIFI_EVENT_STA_DISCONNECTED ตามมาทีหลัง
```
4. หากเครือข่าย Wi-Fi ไม่มี DHCP Server (ไม่มีการแจก IP อัตโนมัติ) ผลการทดลองในข้อ 5.4.1 จะหยุดอยู่ที่ขั้นตอนใด และจะไม่เกิด Event ใดขึ้น?
```c
หากไม่มี DHCP Server การทดลองในข้อ 5.4.1 จะผ่าน Phase 2, 3 และ 4 ได้ตามปกติ (Auth, Assoc และ 4-Way Handshake สำเร็จ เพราะรหัสผ่านถูกต้อง) และจะเกิด Event WIFI_EVENT_STA_CONNECTED แต่จะไปหยุดชะงักอยู่ที่ Phase 5 (DHCP Client ขอ IP) เนื่องจากไม่มี Server ตอบกลับคำขอ IP Address จึงไม่มีทางเกิด Event IP_EVENT_STA_GOT_IP และระบบจะรอจนครบ Timeout ที่กำหนดไว้ (10 วินาทีตามโค้ด) แล้วสรุปผลเป็น TEST TIMEOUT แทนที่จะเป็น TEST PASSED
```
