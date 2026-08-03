## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองในระดับ Link Layer

| ข้อการทดลอง | สถานการณ์ทดสอบ                           |       Event ที่ได้รับ       |                ผลการผูกสัมพันธ์ Link Layer                 | ค่า Association ID (AID) ที่ได้ | Reason Code (ถ้ามี) |
| :---------: | :--------------------------------------- | :-------------------------: | :--------------------------------------------------------: | :-----------------------------: | :------------------ |
|  **5.3.1**  | ร้องขอ Auth & Assoc กับ AP มีอยู่จริง    |  WIFI_EVENT_STA_CONNECTED   | TEST PASSED - Phase 2 (Auth) & Phase 3 (Assoc) Successful! |              34756              |                     |
|  **5.3.2**  | ร้องขอ Auth & Assoc กับ AP ไม่มีอยู่จริง | WIFI_EVENT_STA_DISCONNECTED |                    <br>TEST FAILED<br>                     |                                 | 0xC9                |

### 6.2 บันทึกข้อมูล Link Layer จาก Event `WIFI_EVENT_STA_CONNECTED` (ข้อ 5.3.1)

| พารามิเตอร์ Link Layer   | ค่าที่อ่านได้จริงจาก Forensic Log |
| :----------------------- | :-------------------------------- |
| **SSID**                 | hello_world                       |
| **BSSID (MAC Address)**  | 96:44:8A:D9:7E:63                 |
| **Channel**              | 6                                 |
| **Auth Mode Enum**       | 3                                 |
| **Association ID (AID)** | 34756                             |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. **Association ID (AID)** คืออะไร มีบทบาทอย่างไรใน Phase 3 และส่งคืนมาในโครงสร้างข้อมูลตัวแปรใด?
   ```
   AID คือหมายเลขประจำตัว ที่ AP กำหนดให้ STA แต่ละตัวตอน Association สำเร็จ ใช้เพื่อระบุตัวตนของ client ในการจัดการ เช่น buffer ข้อมูลตอน power-save mode และแยกแยะ client แต่ละตัวในเครือข่ายเดียวกัน 
   ```
2. เหตุใดการเชื่อมต่อ Wi-Fi ความปลอดภัยแบบ WPA2-PSK จึงสามารถผ่าน Phase 2 (Authentication) และ Phase 3 (Association) จนเกิด Event `WIFI_EVENT_STA_CONNECTED` ได้สำเร็จ แม้ผู้ใช้จะป้อนรหัสผ่าน (Password) ผิด?
	```
	เพราะ Phase 2 ของ WPA2-PSK ใช้ Open System Authentication ซึ่งเป็นแค่การแลกเฟรมรับรู้กันเฉยๆ ไม่ตรวจสอบ credential ใดๆ ส่วน Phase 3 ก็เป็นการตกลง capability การเชื่อมต่อ ยังไม่เกี่ยวกับ PSK รหัสผ่านจะถูกใช้ตรวจสอบจริงในขั้น 4-Way Handshake เท่านั้น ซึ่งเป็นเฟสหลังจาก WIFI_EVENT_STA_CONNECTED เกิดขึ้นแล้ว ดังนั้นถ้ารหัสผ่านผิด event connected ก็ยังเกิดได้ตามปกติ แต่จะหลุดในภายหลังตอน handshake ล้มเหลว
	```
3. หาก Router มีการตั้งค่า **MAC Address Filtering** (อนุญาตเฉพาะ MAC ที่ลงทะเบียน) ESP32 จะล้มเหลวในเฟสใด และจะส่ง Disconnect Reason Code ใดออกมา?
	```
	จะล้มเหลวใน Phase 3 เพราะ Open Authentication ยังผ่านได้ปกติ แต่พอ AP ตรวจสอบ MAC Address ในขั้น Association Request แล้วพบว่าไม่อยู่ใน whitelist AP จะปฏิเสธคำขอ Association ส่ง reason code ที่เกี่ยวข้องออกมา คือ WIFI_REASON_ASSOC_FAIL 203 เเต่ในบางกรณี AP อาจตอบเป็น WIFI_REASON_ASSOC_NOT_AUTHED rejectขึ้นอยู่กับ firmware ของ AP นั้นๆ
	```
4. สรุปความแตกต่างสำคัญระหว่างจุดสิ้นสุดของ **Phase 3 (Link-Layer Connected)** กับจุดสิ้นสุดของ **Phase 5 (IP Address Assigned)**
	```
	- Phase 3 สิ้นสุด Link-Layer Connected เป็น Event`WIFI_EVENT_STA_CONNECTED`​ อยู่ใน Layer 2  คือ Auth + Assoc (+ 4-way handshake) เสร็จสมบูรณ์ มี "ลิงก์วิทยุ" ที่ปลอดภัยระดับ MAC ยังส่งข้อมูลผ่าน TCP/IP ไม่ได้เพราะไม่มี IP
	
	- Phase 5 สิ้นสุด IP Assigned เป็ร event `IP_EVENT_STA_GOT_IP`​ อยู่ใน Layer 3 ได้ IP Address, Netmask, Gateway จาก DHCP Server แล้ว พร้อมสื่อสารผ่านเครือข่าย IP
	```

## Log
```
ets Jul 29 2019 12:21:46

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0040,len:6272
load:0x40078000,len:15848
load:0x40080400,len:3920
--- 0x40080400: _invalid_pc_placeholder at /Users/ittikorntongsima/My-Library/esp-idf/components/xtensa/xtensa_vectors.S:2259
entry 0x40080644
--- 0x40080644: call_start_cpu0 at /Users/ittikorntongsima/My-Library/esp-idf/components/bootloader/subproject/main/bootloader_start.c:27
I (27) boot: ESP-IDF v6.1-dev-3480-g44c77cbf46 2nd stage bootloader
I (27) boot: compile time Aug  4 2026 02:40:09
I (28) boot: Multicore bootloader
I (30) boot: chip revision: v3.1
I (33) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode       : DIO
I (40) boot.esp32: SPI Flash Size : 2MB
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (57) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory          factory app      00 00 00010000 00100000
I (77) boot: End of partition table
I (80) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1a5e4h (108004) map
I (126) esp_image: segment 1: paddr=0002a60c vaddr=3ffb0000 size=045a8h ( 17832) load
I (133) esp_image: segment 2: paddr=0002ebbc vaddr=40080000 size=0145ch (  5212) load
I (136) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=8559ch (546204) map
I (332) esp_image: segment 4: paddr=000b55c4 vaddr=4008145c size=141b0h ( 82352) load
I (366) esp_image: segment 5: paddr=000c977c vaddr=50000000 size=00028h (    40) load
I (377) boot: Loaded app from partition at offset 0x10000
I (377) boot: Disabling RNG early entropy source...
I (388) cpu_start: Multicore app
I (396) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (396) cpu_start: Pro cpu start user code
I (396) cpu_start: cpu freq: 160000000 Hz
I (398) app_init: Application information:
I (402) app_init: Project name:     lab3
I (406) app_init: App version:      1
I (409) app_init: Compile time:     Aug  4 2026 02:35:31
I (414) app_init: ELF file SHA256:  15a381385...
I (418) app_init: ESP-IDF:          v6.1-dev-3480-g44c77cbf46
I (424) efuse_init: Min chip rev:     v0.0
I (428) efuse_init: Max chip rev:     v3.99
I (432) efuse_init: Chip rev:         v3.1
I (436) heap_init: Initializing. RAM available for dynamic allocation:
I (442) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (447) heap_init: At 3FFB8A90 len 00027570 (157 KiB): DRAM
I (452) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (457) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (463) heap_init: At 4009560C len 0000A9F4 (42 KiB): IRAM
I (470) spi_flash: detected chip: generic
I (472) spi_flash: flash io: dio
W (475) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (489) main_task: Started on CPU0
I (499) main_task: Calling app_main()
I (499) LAB_AUTH_ASSOC: [FORENSIC]: Call nvs_flash_init()
I (549) LAB_AUTH_ASSOC: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (549) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_netif_init()
I (549) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_event_loop_create_default()
I (549) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (559) LAB_AUTH_ASSOC: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbdecc
I (569) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_init(&cfg)
I (579) wifi:wifi driver task: 3ffc05a8, prio:23, stack:6656, core=0
I (609) wifi:wifi firmware version: 5d0a58b
I (609) wifi:wifi certification version: v7.0
I (609) wifi:config NVS flash: enabled
I (609) wifi:config nano formatting: disabled
I (609) wifi:Init data frame dynamic rx buffer num: 32
I (619) wifi:Init static rx mgmt buffer num: 5
I (619) wifi:Init management short buffer num: 32
I (629) wifi:Init dynamic tx buffer num: 32
I (629) wifi:Init static rx buffer size: 1600
I (629) wifi:Init static rx buffer num: 10
I (639) wifi:Init dynamic rx buffer num: 32
I (639) wifi_init: rx ba win: 6
I (639) wifi_init: accept mbox: 6
I (649) wifi_init: tcpip mbox: 32
I (649) wifi_init: udp mbox: 6
I (649) wifi_init: tcp mbox: 6
I (659) wifi_init: tcp tx win: 5760
I (659) wifi_init: tcp rx win: 5760
I (659) wifi_init: tcp mss: 1440
I (669) wifi_init: WiFi IRAM OP enabled
I (669) wifi_init: WiFi RX IRAM OP enabled
I (669) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (679) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (689) LAB_AUTH_ASSOC: ==================================================================
I (689) LAB_AUTH_ASSOC:   Lab 5.3: Wi-Fi Authentication & Association Phase (ESP-IDF Forensic)
I (699) LAB_AUTH_ASSOC: ==================================================================
I (709) LAB_AUTH_ASSOC:

I (709) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (719) LAB_AUTH_ASSOC: >>> Experiment 5.3.1: Link-Layer Auth & Assoc Phase Test
I (729) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (739) LAB_AUTH_ASSOC:   Target SSID    : "hello_world"
I (739) LAB_AUTH_ASSOC:   Target Password: "qwertyuiop"
I (749) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_stop()
I (749) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
W (759) wifi:Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2
I (799) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (799) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_start()
I (799) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06
I (889) wifi:mode : sta (8c:94:df:45:93:e4)
I (889) wifi:enable tsf
I (889) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (899) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (899) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (909) LAB_AUTH_ASSOC: [FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...
I (909) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (919) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (929) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
I (929) wifi:state: init -> auth (0xb0)
I (939) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (949) wifi:state: auth -> assoc (0x0)
I (969) wifi:state: assoc -> run (0x10)
I (1439) wifi:connected with hello_world, aid = 3, channel 6, BW20, bssid = 96:44:8a:d9:7e:63
I (1439) wifi:security: WPA2-PSK, phy: bgn, rssi: -54, cipher(pairwise:0x3, group:0x3), pmf:0
I (1459) wifi:pm start, type: 1

I (1459) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (1459) LAB_AUTH_ASSOC: =======================================================
I (1469) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (1469) LAB_AUTH_ASSOC:   [SUCCESS]: Phase 2 (Auth) & Phase 3 (Assoc) COMPLETED!
I (1479) LAB_AUTH_ASSOC:   -> Connected SSID        : hello_world
I (1489) LAB_AUTH_ASSOC:   -> BSSID (MAC Address)   : 96:44:8A:D9:7E:63
I (1489) LAB_AUTH_ASSOC:   -> Channel               : 6
I (1499) LAB_AUTH_ASSOC:   -> Auth Mode             : 3
I (1499) LAB_AUTH_ASSOC:   -> Association ID (AID)  : 34756
I (1509) LAB_AUTH_ASSOC: =======================================================
I (1489) wifi:AP's beacon interval = 102400 us, DTIM period = 1
I (1519) LAB_AUTH_ASSOC: [RESULT]: TEST PASSED - Phase 2 (Auth) & Phase 3 (Assoc) Successful!
I (2539) esp_netif_handlers: sta ip: 172.20.10.2, mask: 255.255.255.240, gw: 172.20.10.1
I (3529) LAB_AUTH_ASSOC:

I (3529) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (3529) LAB_AUTH_ASSOC: >>> Experiment 5.3.2: Link-Layer Test - Non-Existent AP
I (3529) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (3539) LAB_AUTH_ASSOC:   Target SSID    : "NON_EXISTENT_AP_9999"
I (3549) LAB_AUTH_ASSOC:   Target Password: "12345678"
I (3549) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_stop()
I (3559) wifi:state: run -> init (0x0)
I (3569) wifi:pm stop, total sleep time: 1576997 us / 2106466 us

I (3569) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
W (3579) LAB_AUTH_ASSOC: =======================================================
W (3579) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (3589) LAB_AUTH_ASSOC:   -> Target SSID          : hello_world
W (3589) LAB_AUTH_ASSOC:   -> Reason Code (Decimal): 8
W (3599) LAB_AUTH_ASSOC:   -> Reason Code (Hex)    : 0x08
W (3599) LAB_AUTH_ASSOC:   -> Reason Diagnosis     : OTHER_DISCONNECT_REASON
W (3609) LAB_AUTH_ASSOC: =======================================================
I (3619) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (3659) wifi:flush txq
I (3659) wifi:stop sw txq
I (3659) wifi:lmac stop hw txq
I (3659) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
W (3659) wifi:Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2
I (3699) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (3699) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_start()
I (3699) wifi:mode : sta (8c:94:df:45:93:e4)
I (3699) wifi:enable tsf
I (3709) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (3709) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (3709) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (3729) LAB_AUTH_ASSOC: [FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...
I (3729) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (3739) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (3749) LAB_AUTH_ASSOC: [RESULT]: TEST FAILED - Disconnected event captured in Link-Layer.
I (3749) LAB_AUTH_ASSOC: ==================================================================
I (3759) LAB_AUTH_ASSOC:   [Phase 2 & Phase 3 Completed: Link-Layer Auth & Assoc Finished]
I (3769) LAB_AUTH_ASSOC: ==================================================================
I (3779) main_task: Returned from app_main()
W (6159) LAB_AUTH_ASSOC: =======================================================
W (6159) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (6159) LAB_AUTH_ASSOC:   -> Target SSID          : NON_EXISTENT_AP_9999
W (6169) LAB_AUTH_ASSOC:   -> Reason Code (Decimal): 201
W (6169) LAB_AUTH_ASSOC:   -> Reason Code (Hex)    : 0xC9
W (6179) LAB_AUTH_ASSOC:   -> Reason Diagnosis     : WIFI_REASON_NO_AP_FOUND (201) [Phase 1: SSID Not Found]
W (6189) LAB_AUTH_ASSOC: =======================================================
```