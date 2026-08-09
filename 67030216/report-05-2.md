## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:
```c
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (5�ets Jul 29 2019 12:21:46

rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0030,len:6380
ho 0 tail 12 room 4
load:0x40078000,len:15916
load:0x40080400,len:3860
--- 0x40080400: _invalid_pc_placeholder at C:/Users/hp/esp/v5.5.1/esp-idf/components/xtensa/xtensa_vectors.S:2235
entry 0x40080638
--- 0x40080638: call_start_cpu0 at C:/Users/hp/esp/v5.5.1/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
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
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=19e48h (106056) map
I (124) esp_image: segment 1: paddr=00029e70 vaddr=3ffb0000 size=03eech ( 16108) load
I (130) esp_image: segment 2: paddr=0002dd64 vaddr=40080000 size=022b4h (  8884) load
I (134) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=861fch (549372) map
I (323) esp_image: segment 4: paddr=000b6224 vaddr=400822b4 size=15b58h ( 88920) load
I (358) esp_image: segment 5: paddr=000cbd84 vaddr=50000000 size=00020h (    32) load
I (370) boot: Loaded app from partition at offset 0x10000
I (370) boot: Disabling RNG early entropy source...
I (381) cpu_start: Multicore app
I (389) cpu_start: Pro cpu start user code
I (389) cpu_start: cpu freq: 160000000 Hz
I (389) app_init: Application information:
I (389) app_init: Project name:     LED_Blink
I (393) app_init: App version:      1
I (397) app_init: Compile time:     Aug  3 2026 11:01:33
I (402) app_init: ELF file SHA256:  26cea039c...
I (406) app_init: ESP-IDF:          v5.5.1
I (410) efuse_init: Min chip rev:     v0.0
I (414) efuse_init: Max chip rev:     v3.99 
I (418) efuse_init: Chip rev:         v3.1
I (422) heap_init: Initializing. RAM available for dynamic allocation:
I (428) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (433) heap_init: At 3FFB7FD0 len 00028030 (160 KiB): DRAM
I (438) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (443) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (449) heap_init: At 40097E0C len 000081F4 (32 KiB): IRAM
I (456) spi_flash: detected chip: generic
I (458) spi_flash: flash io: dio
W (461) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (474) main_task: Started on CPU0
I (484) main_task: Calling app_main()
I (484) LAB_WIFI_CONN: [FORENSIC]: Call nvs_flash_init()
I (504) LAB_WIFI_CONN: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (504) LAB_WIFI_CONN: [FORENSIC]: Call esp_netif_init()
I (504) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_loop_create_default()
I (514) LAB_WIFI_CONN: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (514) LAB_WIFI_CONN: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbd838
I (524) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_init(&cfg)
I (544) wifi:wifi driver task: 3ffbff24, prio:23, stack:6656, core=0
I (554) wifi:wifi firmware version: 14da9b7
I (554) wifi:wifi certification version: v7.0
I (554) wifi:config NVS flash: enabled
I (554) wifi:config nano formatting: disabled
I (554) wifi:Init data frame dynamic rx buffer num: 32
I (564) wifi:Init static rx mgmt buffer num: 5
I (564) wifi:Init management short buffer num: 32
I (574) wifi:Init dynamic tx buffer num: 32
I (574) wifi:Init static rx buffer size: 1600
I (584) wifi:Init static rx buffer num: 10
I (584) wifi:Init dynamic rx buffer num: 32
I (584) wifi_init: rx ba win: 6
I (594) wifi_init: accept mbox: 6
I (594) wifi_init: tcpip mbox: 32
I (594) wifi_init: udp mbox: 6
I (604) wifi_init: tcp mbox: 6
I (604) wifi_init: tcp tx win: 5760
I (604) wifi_init: tcp rx win: 5760
I (604) wifi_init: tcp mss: 1440
I (614) wifi_init: WiFi IRAM OP enabled
I (614) wifi_init: WiFi RX IRAM OP enabled
I (614) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (624) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_handler_instance_register(IP_EVENT)
I (634) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (644) LAB_WIFI_CONN: ==================================================================
I (644) LAB_WIFI_CONN:   Lab 5.2: Wi-Fi Connection & IP Assignment (ESP-IDF Forensic)
I (654) LAB_WIFI_CONN: ==================================================================
I (664) LAB_WIFI_CONN: 

I (664) LAB_WIFI_CONN: ------------------------------------------------------------------
I (674) LAB_WIFI_CONN: >>> Experiment 5.2.1: Connection Test - Correct Credentials
I (684) LAB_WIFI_CONN: ------------------------------------------------------------------
I (694) LAB_WIFI_CONN:   Target SSID: "IG:PK_2302"
I (694) LAB_WIFI_CONN:   Target Password: "Petchkung2302"
I (704) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (704) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (754) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (754) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (754) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (834) wifi:mode : sta (14:33:5c:0d:cd:7c)
I (844) wifi:enable tsf
I (844) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (844) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (844) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (854) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (864) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (1164) wifi:new:<1,0>, old:<1,0>, ap:<255,255>, sta:<1,0>, prof:1, snd_ch_cfg:0x0
I (1164) wifi:state: init -> auth (0xb0)
I (1174) wifi:state: auth -> assoc (0x0)
I (1184) wifi:state: assoc -> run (0x10)
I (1274) wifi:connected with IG:PK_2302, aid = 1, channel 1, BW20, bssid = de:f7:ed:c6:b6:23
I (1274) wifi:security: WPA2-PSK, phy: bgn, rssi: -50
I (1284) wifi:pm start, type: 1

I (1294) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (1294) LAB_WIFI_CONN: =======================================================
I (1294) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (1304) LAB_WIFI_CONN:   -> Connected to SSID : IG:PK_2302
I (1304) LAB_WIFI_CONN:   -> BSSID            : DE:F7:ED:C6:B6:23
I (1314) LAB_WIFI_CONN:   -> Channel          : 1
I (1314) LAB_WIFI_CONN:   -> Auth Mode        : 3
I (1324) LAB_WIFI_CONN: =======================================================
I (1314) wifi:AP's beacon interval = 102400 us, DTIM period = 1
I (2674) esp_netif_handlers: sta ip: 172.20.10.2, mask: 255.255.255.240, gw: 172.20.10.1
I (2674) LAB_WIFI_CONN: =======================================================
I (2674) LAB_WIFI_CONN: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!
I (2684) LAB_WIFI_CONN:   -> IP Address : 172.20.10.2
I (2684) LAB_WIFI_CONN:   -> Netmask    : 255.255.255.240
I (2694) LAB_WIFI_CONN:   -> Gateway    : 172.20.10.1
I (2694) LAB_WIFI_CONN: =======================================================
I (2704) LAB_WIFI_CONN: [RESULT]: TEST PASSED - Connected to AP successfully!
I (4714) LAB_WIFI_CONN: 

I (4714) LAB_WIFI_CONN: ------------------------------------------------------------------
I (4714) LAB_WIFI_CONN: >>> Experiment 5.2.2: Connection Test - Wrong SSID (No AP Found)
I (4714) LAB_WIFI_CONN: ------------------------------------------------------------------
I (4724) LAB_WIFI_CONN:   Target SSID: "NON_EXISTENT_SSID_9999"
I (4734) LAB_WIFI_CONN:   Target Password: "12345678"
I (4734) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (4744) wifi:state: run -> init (0x0)
I (4754) wifi:pm stop, total sleep time: 2299233 us / 3461741 us

I (4754) wifi:new:<1,0>, old:<1,0>, ap:<255,255>, sta:<1,0>, prof:1, snd_ch_cfg:0x0
W (4764) LAB_WIFI_CONN: =======================================================
W (4764) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (4774) LAB_WIFI_CONN:   -> Target SSID          : IG:PK_2302
W (4774) LAB_WIFI_CONN:   -> Reason Code (Decimal): 8
W (4784) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0x08
W (4784) LAB_WIFI_CONN:   -> Reason Description   : OTHER_DISCONNECT_REASON
W (4794) LAB_WIFI_CONN: =======================================================
I (4804) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (4804) wifi:flush txq
I (4804) wifi:stop sw txq
I (4814) wifi:lmac stop hw txq
I (4814) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (4854) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (4854) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (4854) wifi:mode : sta (14:33:5c:0d:cd:7c)
I (4854) wifi:enable tsf
I (4864) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (4864) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (4874) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (4884) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (4884) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (6894) LAB_WIFI_CONN: 

I (6894) LAB_WIFI_CONN: ------------------------------------------------------------------
I (6894) LAB_WIFI_CONN: >>> Experiment 5.2.3: Connection Test - Wrong Password (Auth/Handshake Fail)
I (6894) LAB_WIFI_CONN: ------------------------------------------------------------------
I (6904) LAB_WIFI_CONN:   Target SSID: "IG:PK_2302"
I (6914) LAB_WIFI_CONN:   Target Password: "WRONG_PASS_9999"
I (6914) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (6924) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (6924) wifi:flush txq
I (6924) wifi:stop sw txq
I (6934) wifi:lmac stop hw txq
I (6934) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (6984) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (6984) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (6994) wifi:mode : sta (14:33:5c:0d:cd:7c)
I (6994) wifi:enable tsf
I (6994) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (7004) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (7004) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (6994) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (7294) wifi:new:<1,0>, old:<1,0>, ap:<255,255>, sta:<1,0>, prof:1, snd_ch_cfg:0x0
I (7294) wifi:state: init -> auth (0xb0)
I (7314) wifi:state: auth -> assoc (0x0)
I (7314) wifi:state: assoc -> run (0x10)
I (7384) wifi:state: run -> init (0x2c0)
I (7394) wifi:new:<1,0>, old:<1,0>, ap:<255,255>, sta:<1,0>, prof:1, snd_ch_cfg:0x0
W (7394) LAB_WIFI_CONN: =======================================================
W (7394) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (7404) LAB_WIFI_CONN:   -> Target SSID          : IG:PK_2302
W (7404) LAB_WIFI_CONN:   -> Reason Code (Decimal): 2
W (7414) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0x02
W (7414) LAB_WIFI_CONN:   -> Reason Description   : WIFI_REASON_AUTH_EXPIRE (2)
W (7424) LAB_WIFI_CONN: =======================================================
W (7434) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (7434) LAB_WIFI_CONN: ==================================================================
I (7444) LAB_WIFI_CONN:   [Phase 2/3/4/5 Completed: Wi-Fi Connection Lab Finished]
I (7454) LAB_WIFI_CONN: ==================================================================
I (7464) main_task: Returned from app_main()
```
### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองทั้ง 3 สถานการณ์

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event สุดท้ายที่ได้รับ | ผลลัพธ์ (Passed/Failed) | Reason Code (Decimal / Hex) | คำอธิบาย Reason Code |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.2.1** | SSID และ Password ถูกต้อง |IP_EVENT_STA_GOT_IP|Passed |	-|เชื่อมต่อ AP สำเร็จและได้รับ IP Address จาก DHCP |
| **5.2.2** | ระบุ SSID ผิด (ไม่มีในระบบ) |WIFI_EVENT_STA_DISCONNECTED|Failed |8 / 0x08 |OTHER_DISCONNECT_REASON |
| **5.2.3** | ระบุ SSID ถูกต้อง แต่ Password ผิด |WIFI_EVENT_STA_DISCONNECTED |Failed |2 / 0x02 | WIFI_REASON_AUTH_EXPIRE (2)|

### 6.2 บันทึกข้อมูลเครือข่ายจากการเชื่อมต่อสำเร็จ (ข้อ 5.2.1)

| พารามิเตอร์เครือข่าย | ค่าที่ได้รับจริงจาก DHCP |
| :--- | :--- |
| **SSID** |IG:PK_2302 |
| **BSSID (MAC Address)** |DE:F7:ED:C6:B6:23 |
| **Channel** | 1|
| **IP Address** |172.20.10.2|
| **Subnet Mask** |255.255.255.240 |
| **Default Gateway** |172.20.10.1 |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการระบุ SSID ผิด (ข้อ 5.2.2) จึงส่งผลให้เกิด Disconnect Event ด้วย Reason Code `201` (`WIFI_REASON_NO_AP_FOUND`) ตั้งแต่เฟส Scan?
```c
เมื่อ ESP32 ระบุ SSID ที่ไม่มีอยู่จริง ระบบจะไม่สามารถค้นหา Access Point ที่ตรงกับ SSID ที่กำหนดได้ จึงไม่สามารถดำเนินการเชื่อมต่อกับ AP ต่อไปได้และเกิด WIFI_EVENT_STA_DISCONNECTED ขึ้น อย่างไรก็ตาม จากผลการทดลองจริงใน Serial Console พบ Reason Code เป็น 8 (0x08) : OTHER_DISCONNECT_REASON ไม่ใช่ 201 (WIFI_REASON_NO_AP_FOUND) ตามที่ระบุในคำถาม ดังนั้นคำตอบควรอ้างอิงจากผลการทดลองจริงว่า ในการทดลองครั้งนี้ ESP32 รายงานการ Disconnect ด้วย Reason Code 8 เนื่องจากมีการระบุ SSID ที่ไม่มีอยู่ในระบบ
```
2. เหตุใดการพิมพ์ Password ผิด (ข้อ 5.2.3) จึงผ่านเฟส Auth และ Assoc มาได้ แต่มาล้มเหลวในเฟส 4-Way Handshake (Reason Code `15` หรือ `204`)?
```c
เนื่องจาก SSID ที่ระบุถูกต้อง ทำให้ ESP32 สามารถค้นหา Access Point และเริ่มกระบวนการเชื่อมต่อได้ โดยจาก Log พบว่าสถานะเปลี่ยนจาก init -> auth -> assoc -> run แต่เมื่อใช้ Password ที่ไม่ถูกต้อง การยืนยันตัวตนสำหรับเครือข่าย WPA2-PSK ไม่สามารถดำเนินการให้สำเร็จได้ จึงเกิด WIFI_EVENT_STA_DISCONNECTED ขึ้น อย่างไรก็ตาม จากผลการทดลองจริงพบ Reason Code เป็น 2 (0x02) : WIFI_REASON_AUTH_EXPIRE ไม่ใช่ Reason Code 15 หรือ 204 ตามที่ระบุในคำถาม โดยแสดงว่ากระบวนการ Authentication ไม่สามารถดำเนินการให้สำเร็จภายในเวลาที่กำหนด
```
3. ลำดับการเกิด Event ระหว่าง **`WIFI_EVENT_STA_CONNECTED`** กับ **`IP_EVENT_STA_GOT_IP`** Event ใดเกิดขึ้นก่อนกัน และมีความหมายทางกายภาพของ Layer Network ต่างกันอย่างไร?
```c
`WIFI_EVENT_STA_CONNECTED` เกิดขึ้นก่อน `IP_EVENT_STA_GOT_IP` โดยจากผลการทดลอง เมื่อเชื่อมต่อกับ AP สำเร็จจะพบ `WIFI_EVENT_STA_CONNECTED` ก่อน และหลังจากนั้นจึงได้รับ `IP_EVENT_STA_GOT_IP`

`WIFI_EVENT_STA_CONNECTED` หมายถึง ESP32 เชื่อมต่อกับ Access Point สำเร็จในระดับ **Layer 2 (Data Link Layer)** แล้ว แต่ยังไม่ได้รับ IP Address ส่วน `IP_EVENT_STA_GOT_IP` เกิดขึ้นหลังจาก ESP32 ได้รับ IP Address จาก DHCP ซึ่งแสดงว่าระบบพร้อมใช้งานในระดับ **Layer 3 (Network Layer)** และสามารถสื่อสารผ่านเครือข่าย IP ได้
```
4. สมาชิกตัวแปร `reason` ในโครงสร้าง `wifi_event_sta_disconnected_t` มีประโยชน์อย่างไรต่อการออกแบบระบบค้นหาสาเหตุและกู้คืนการเชื่อมต่อ (Auto-Reconnection Mechanism) ในแอปพลิเคชัน IoT?
```c
ตัวแปร `reason` ใช้บอกสาเหตุที่ ESP32 ถูกตัดการเชื่อมต่อจาก Wi-Fi ทำให้สามารถนำข้อมูลไปใช้ในการออกแบบระบบ Auto-Reconnection ได้อย่างเหมาะสม โดยระบบสามารถแยกการจัดการตามสาเหตุ เช่น หากเป็นปัญหาชั่วคราวของการเชื่อมต่อหรือสัญญาณ อาจให้ระบบพยายามเชื่อมต่อใหม่อัตโนมัติ แต่หากเป็นปัญหาจาก Password ไม่ถูกต้อง ควรหยุดการ Retry และแจ้งให้ผู้ใช้ตรวจสอบข้อมูลการเชื่อมต่อแทน ดังนั้น `reason` จึงช่วยให้ระบบไม่ต้องใช้วิธี Reconnect แบบเดียวกับทุกกรณี และสามารถกู้คืนการเชื่อมต่อได้อย่างมีประสิทธิภาพมากขึ้น
```
