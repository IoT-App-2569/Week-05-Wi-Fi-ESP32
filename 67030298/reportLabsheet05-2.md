# ใบงานที่ 5.2: การยืนยันตัวตน การสถาปนาการเชื่อมต่อ และการรับหมายเลข IP Address (Wi-Fi Connection & IP Assignment)
## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองทั้ง 3 สถานการณ์

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event สุดท้ายที่ได้รับ | ผลลัพธ์ (Passed/Failed) | Reason Code (Decimal / Hex) | คำอธิบาย Reason Code |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.2.1** | SSID และ Password ถูกต้อง | `IP_EVENT_STA_GOT_IP` | Passed | - | - |
| **5.2.2** | ระบุ SSID ผิด (ไม่มีในระบบ) | `WIFI_EVENT_STA_DISCONNECTED` | Failed | 8 / 0x08 | OTHER_DISCONNECT_REASON (ตาม Log) / NO_AP_FOUND (ทฤษฎี) |
| **5.2.3** | ระบุ SSID ถูกต้อง แต่ Password ผิด | `WIFI_EVENT_STA_DISCONNECTED` | Failed | 15 / 0x0F | WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT |

### 6.2 บันทึกข้อมูลเครือข่ายจากการเชื่อมต่อสำเร็จ (ข้อ 5.2.1)

| พารามิเตอร์เครือข่าย | ค่าที่ได้รับจริงจาก DHCP |
| :--- | :--- |
| **SSID** | Redmi Note 10S |
| **BSSID (MAC Address)** | 66:34:B4:F7:03:8A |
| **Channel** | 5 |
| **IP Address** | 10.61.229.229 |
| **Subnet Mask** | 255.255.255.0 |
| **Default Gateway** | 10.61.229.63 |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการระบุ SSID ผิด (ข้อ 5.2.2) จึงส่งผลให้เกิด Disconnect Event ด้วย Reason Code `201` (`WIFI_REASON_NO_AP_FOUND`) ตั้งแต่เฟส Scan?
> เพราะไม่พบชื่อ SSID เป้าหมายตั้งแต่ขั้นตอนสแกน การเชื่อมต่อจึงถูกยกเลิกทันทีก่อนจะไปถึงเฟสถัดไป

2. เหตุใดการพิมพ์ Password ผิด (ข้อ 5.2.3) จึงผ่านเฟส Auth และ Assoc มาได้ แต่มาล้มเหลวในเฟส 4-Way Handshake (Reason Code `15` หรือ `204`)?
> เฟส Auth/Assoc เป็นเพียงการรับเครื่องเข้ามาคุยเบื้องต้น (Open System) ส่วนการตรวจรหัสผ่านจริงๆ เกิดขึ้นตอน 4-Way Handshake ถ้ารหัสผิดจึงมาล้มเหลวตรงจุดนี้

3. ลำดับการเกิด Event ระหว่าง **`WIFI_EVENT_STA_CONNECTED`** กับ **`IP_EVENT_STA_GOT_IP`** Event ใดเกิดขึ้นก่อนกัน และมีความหมายทางกายภาพของ Layer Network ต่างกันอย่างไร?
> `WIFI_EVENT_STA_CONNECTED` เกิดก่อน (ต่อ Wi-Fi ระดับ Layer 2 สำเร็จ) แล้วตามด้วย `IP_EVENT_STA_GOT_IP` (ได้หมายเลข IP ระดับ Layer 3 สำเร็จ)

4. สมาชิกตัวแปร `reason` ในโครงสร้าง `wifi_event_sta_disconnected_t` มีประโยชน์อย่างไรต่อการออกแบบระบบค้นหาสาเหตุและกู้คืนการเชื่อมต่อ (Auto-Reconnection Mechanism) ในแอปพลิเคชัน IoT?
> ช่วยให้โปรแกรมรู้สาเหตุการหลุดเพื่อจัดการได้ตรงจุด เช่น รหัสผิดให้หยุดต่อแล้วแจ้งผู้ใช้ แต่ถ้าหา AP ไม่เจอให้พยายามต่อใหม่ (Retry) ภายหลัง

---

## 8. Log ของการทดลอง (Serial Console Log)
```text
I (27) boot: ESP-IDF v6.0.2-dirty 2nd stage bootloader
I (27) boot: compile time Aug  3 2026 10:17:20
I (28) boot: Multicore bootloader
I (29) boot: chip revision: v3.1
I (32) boot.esp32: SPI Speed      : 40MHz
I (36) boot.esp32: SPI Mode       : DIO
I (39) boot.esp32: SPI Flash Size : 2MB
I (43) boot: Enabling RNG early entropy source...
I (47) boot: Partition Table:
I (50) boot: ## Label            Usage          Type ST Offset   Length
I (56) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (63) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (69) boot:  2 factory          factory app      00 00 00010000 00100000
I (76) boot: End of partition table
I (79) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1a5e8h (108008) map
I (125) esp_image: segment 1: paddr=0002a610 vaddr=3ffb0000 size=04528h ( 17704) load
I (132) esp_image: segment 2: paddr=0002eb40 vaddr=40080000 size=014d8h (  5336) load
I (135) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=86318h (549656) map
I (332) esp_image: segment 4: paddr=000b6340 vaddr=400814d8 size=14130h ( 82224) load
I (366) esp_image: segment 5: paddr=000ca478 vaddr=50000000 size=00028h (    40) load
I (377) boot: Loaded app from partition at offset 0x10000
I (377) boot: Disabling RNG early entropy source...
I (388) cpu_start: Multicore app
I (396) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (396) cpu_start: Pro cpu start user code
I (396) cpu_start: cpu freq: 160000000 Hz
I (398) app_init: Application information:
I (402) app_init: Project name:     02-Labsheet-05-2
I (407) app_init: App version:      f9372cb-dirty
I (411) app_init: Compile time:     Aug  3 2026 10:16:00
I (416) app_init: ELF file SHA256:  5d55476a9...
I (421) app_init: ESP-IDF:          v6.0.2-dirty
I (425) efuse_init: Min chip rev:     v0.0
I (429) efuse_init: Max chip rev:     v3.99
I (433) efuse_init: Chip rev:         v3.1
I (437) heap_init: Initializing. RAM available for dynamic allocation:
I (443) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (448) heap_init: At 3FFB8A40 len 000275C0 (157 KiB): DRAM
I (453) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (459) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (464) heap_init: At 40095608 len 0000A9F8 (42 KiB): IRAM
I (471) spi_flash: detected chip: generic
I (473) spi_flash: flash io: dio
W (476) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (490) main_task: Started on CPU0
I (490) main_task: Calling app_main()
I (490) LAB_WIFI_CONN: [FORENSIC]: Call nvs_flash_init()
I (520) LAB_WIFI_CONN: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (520) LAB_WIFI_CONN: [FORENSIC]: Call esp_netif_init()
I (520) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_loop_create_default()
I (530) LAB_WIFI_CONN: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (530) LAB_WIFI_CONN: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbdd38
I (540) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_init(&cfg)
I (560) wifi:wifi driver task: 3ffc0424, prio:23, stack:6656, core=0
I (570) wifi:wifi firmware version: 00ad238
I (570) wifi:wifi certification version: v7.0
I (570) wifi:config NVS flash: enabled
I (570) wifi:config nano formatting: disabled
I (580) wifi:Init data frame dynamic rx buffer num: 32
I (580) wifi:Init static rx mgmt buffer num: 5
I (580) wifi:Init management short buffer num: 32
I (590) wifi:Init dynamic tx buffer num: 32
I (590) wifi:Init static rx buffer size: 1600
I (600) wifi:Init static rx buffer num: 10
I (600) wifi:Init dynamic rx buffer num: 32
I (610) wifi_init: rx ba win: 6
I (610) wifi_init: accept mbox: 6
I (610) wifi_init: tcpip mbox: 32
I (610) wifi_init: udp mbox: 6
I (620) wifi_init: tcp mbox: 6
I (620) wifi_init: tcp tx win: 5760
I (620) wifi_init: tcp rx win: 5760
I (620) wifi_init: tcp mss: 1440
I (630) wifi_init: WiFi IRAM OP enabled
I (630) wifi_init: WiFi RX IRAM OP enabled
I (640) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (640) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_handler_instance_register(IP_EVENT)
I (650) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (660) LAB_WIFI_CONN: ==================================================================
I (660) LAB_WIFI_CONN:   Lab 5.2: Wi-Fi Connection & IP Assignment (ESP-IDF Forensic)
I (670) LAB_WIFI_CONN: ==================================================================
I (680) LAB_WIFI_CONN: 

I (680) LAB_WIFI_CONN: ------------------------------------------------------------------
I (690) LAB_WIFI_CONN: >>> Experiment 5.2.1: Connection Test - Correct Credentials
I (700) LAB_WIFI_CONN: ------------------------------------------------------------------
I (710) LAB_WIFI_CONN:   Target SSID: "Redmi Note 10S"
I (710) LAB_WIFI_CONN:   Target Password: "3832538325zzz"
I (720) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (720) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (750) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (750) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (760) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06
I (850) wifi:mode : sta (84:1f:e8:39:bd:64)
I (850) wifi:enable tsf
I (860) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (860) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (860) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (870) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (880) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (1690) wifi:new:<5,0>, old:<1,0>, ap:<255,255>, sta:<5,0>, prof:1, snd_ch_cfg:0x0
I (1690) wifi:state: init -> auth (0xb0)
I (1690) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (1720) wifi:state: auth -> assoc (0x0)
I (1730) wifi:state: assoc -> run (0x10)
I (1760) wifi:connected with Redmi Note 10S, aid = 2, channel 5, BW20, bssid = 66:34:b4:f7:03:8a
I (1760) wifi:security: WPA2-PSK, phy: bgn, rssi: -54, cipher(pairwise:0x3, group:0x3), pmf:0
I (1780) wifi:pm start, type: 1

I (1780) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (1790) LAB_WIFI_CONN: =======================================================
I (1790) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (1790) LAB_WIFI_CONN:   -> Connected to SSID : Redmi Note 10S
I (1800) LAB_WIFI_CONN:   -> BSSID            : 66:34:B4:F7:03:8A
I (1810) LAB_WIFI_CONN:   -> Channel          : 5
I (1810) LAB_WIFI_CONN:   -> Auth Mode        : 3
I (1820) LAB_WIFI_CONN: =======================================================
I (1830) wifi:dp: 2, bi: 102400, li: 4, scale listen interval from 307200 us to 409600 us
I (1830) wifi:AP's beacon interval = 102400 us, DTIM period = 2
I (2810) esp_netif_handlers: sta ip: 10.61.229.229, mask: 255.255.255.0, gw: 10.61.229.63
I (2810) LAB_WIFI_CONN: =======================================================
I (2810) LAB_WIFI_CONN: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!
I (2820) LAB_WIFI_CONN:   -> IP Address : 10.61.229.229
I (2820) LAB_WIFI_CONN:   -> Netmask    : 255.255.255.0
I (2830) LAB_WIFI_CONN:   -> Gateway    : 10.61.229.63
I (2830) LAB_WIFI_CONN: =======================================================
I (2840) LAB_WIFI_CONN: [RESULT]: TEST PASSED - Connected to AP successfully!
I (4850) LAB_WIFI_CONN: 

I (4850) LAB_WIFI_CONN: ------------------------------------------------------------------
I (4850) LAB_WIFI_CONN: >>> Experiment 5.2.2: Connection Test - Wrong SSID (No AP Found)
I (4850) LAB_WIFI_CONN: ------------------------------------------------------------------
I (4860) LAB_WIFI_CONN:   Target SSID: "NON_EXISTENT_SSID_9999"
I (4870) LAB_WIFI_CONN:   Target Password: "12345678"
I (4870) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (4880) wifi:state: run -> init (0x0)
I (4890) wifi:pm stop, total sleep time: 2517604 us / 3105691 us

W (4890) LAB_WIFI_CONN: =======================================================
W (4890) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (4900) LAB_WIFI_CONN:   -> Target SSID          : Redmi Note 10S
W (4910) LAB_WIFI_CONN:   -> Reason Code (Decimal): 8
W (4910) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0x08
W (4920) LAB_WIFI_CONN:   -> Reason Description   : OTHER_DISCONNECT_REASON
W (4920) LAB_WIFI_CONN: =======================================================
I (4930) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (4940) wifi:flush txq
I (4940) wifi:stop sw txq
I (4940) wifi:lmac stop hw txq
I (4940) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (4990) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (4990) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (4990) wifi:mode : sta (84:1f:e8:39:bd:64)
I (4990) wifi:enable tsf
I (4990) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (5000) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (5000) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (5010) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (5020) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (5020) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (7030) LAB_WIFI_CONN: 

I (7030) LAB_WIFI_CONN: ------------------------------------------------------------------
I (7030) LAB_WIFI_CONN: >>> Experiment 5.2.3: Connection Test - Wrong Password (Auth/Handshake Fail)
I (7030) LAB_WIFI_CONN: ------------------------------------------------------------------
I (7040) LAB_WIFI_CONN:   Target SSID: "Redmi Note 10S"
I (7050) LAB_WIFI_CONN:   Target Password: "WRONG_PASS_9999"
I (7050) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (7060) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (7060) wifi:flush txq
I (7070) wifi:stop sw txq
I (7070) wifi:lmac stop hw txq
I (7070) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (7100) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (7100) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (7110) wifi:mode : sta (84:1f:e8:39:bd:64)
I (7110) wifi:enable tsf
I (7110) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (7120) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (7130) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (7110) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (7400) wifi:new:<5,0>, old:<1,0>, ap:<255,255>, sta:<5,0>, prof:1, snd_ch_cfg:0x0
I (7400) wifi:state: init -> auth (0xb0)
I (7410) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (7410) wifi:state: auth -> assoc (0x0)
I (7420) wifi:state: assoc -> run (0x10)
I (10430) wifi:state: run -> init (0xf00)
W (10440) LAB_WIFI_CONN: =======================================================
W (10440) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (10440) LAB_WIFI_CONN:   -> Target SSID          : Redmi Note 10S
W (10450) LAB_WIFI_CONN:   -> Reason Code (Decimal): 15
W (10450) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0x0F
W (10460) LAB_WIFI_CONN:   -> Reason Description   : WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT (204)
W (10470) LAB_WIFI_CONN: =======================================================
W (10470) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (10480) LAB_WIFI_CONN: ==================================================================
I (10490) LAB_WIFI_CONN:   [Phase 2/3/4/5 Completed: Wi-Fi Connection Lab Finished]
I (10500) LAB_WIFI_CONN: ==================================================================
I (10500) main_task: Returned from app_main()
```