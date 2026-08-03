# ใบงานที่ 5.3: การยืนยันตัวตนและการผูกสัมพันธ์ในระดับ Link Layer (Authentication & Association Phase)

```
rst:0x1 (POWERON_RESET),boot:0x12 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0030,len:6380
ho 0 tail 12 room 4
load:0x40078000,len:15916
load:0x40080400,len:3860
--- 0x40080400: _invalid_pc_placeholder at C:/Users/09677/esp/v5.5.1/esp-idf/components/xtensa/xtensa_vectors.S:2235
entry 0x40080638
--- 0x40080638: call_start_cpu0 at C:/Users/09677/esp/v5.5.1/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v5.5.1-dirty 2nd stage bootloader
I (29) boot: compile time Aug  3 2026 11:35:00
I (29) boot: Multicore bootloader
I (31) boot: chip revision: v3.1
I (34) boot.esp32: SPI Speed      : 40MHz
I (38) boot.esp32: SPI Mode       : DIO
I (41) boot.esp32: SPI Flash Size : 2MB
I (45) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (52) boot: ## Label            Usage          Type ST Offset   Length
I (58) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (65) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory          factory app      00 00 00010000 00100000
I (78) boot: End of partition table
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=19e48h (106056) map
I (125) esp_image: segment 1: paddr=00029e70 vaddr=3ffb0000 size=03eech ( 16108) load
I (131) esp_image: segment 2: paddr=0002dd64 vaddr=40080000 size=022b4h (  8884) load
I (135) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=860f4h (549108) map
I (324) esp_image: segment 4: paddr=000b611c vaddr=400822b4 size=15b58h ( 88920) load
I (359) esp_image: segment 5: paddr=000cbc7c vaddr=50000000 size=00020h (    32) load
I (370) boot: Loaded app from partition at offset 0x10000
I (371) boot: Disabling RNG early entropy source...
I (381) cpu_start: Multicore app
I (389) cpu_start: Pro cpu start user code
I (389) cpu_start: cpu freq: 160000000 Hz
I (390) app_init: Application information:
I (390) app_init: Project name:     wifi_auth_assoc_phase
I (395) app_init: App version:      37de524-dirty
I (399) app_init: Compile time:     Aug  3 2026 11:33:16
I (404) app_init: ELF file SHA256:  3c26c659d...
I (408) app_init: ESP-IDF:          v5.5.1-dirty
I (413) efuse_init: Min chip rev:     v0.0
I (417) efuse_init: Max chip rev:     v3.99 
I (421) efuse_init: Chip rev:         v3.1
I (425) heap_init: Initializing. RAM available for dynamic allocation:
I (431) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (436) heap_init: At 3FFB7FD0 len 00028030 (160 KiB): DRAM
I (441) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (447) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (452) heap_init: At 40097E0C len 000081F4 (32 KiB): IRAM
W (459) spi_flash: Detected boya flash chip but using generic driver. For optimal functionality, enable `SPI_FLASH_SUPPORT_BOYA_CHIP` in menuconfig
I (470) spi_flash: detected chip: generic
I (474) spi_flash: flash io: dio
W (477) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (490) main_task: Started on CPU0
I (500) main_task: Calling app_main()
I (500) LAB_AUTH_ASSOC: [FORENSIC]: Call nvs_flash_init()
I (530) LAB_AUTH_ASSOC: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (530) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_netif_init()
I (530) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_event_loop_create_default()
I (540) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (540) LAB_AUTH_ASSOC: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbd980
I (550) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_init(&cfg)
I (570) wifi:wifi driver task: 3ffc006c, prio:23, stack:6656, core=0
I (580) wifi:wifi firmware version: 14da9b7
I (580) wifi:wifi certification version: v7.0
I (580) wifi:config NVS flash: enabled
I (580) wifi:config nano formatting: disabled
I (590) wifi:Init data frame dynamic rx buffer num: 32
I (590) wifi:Init static rx mgmt buffer num: 5
I (590) wifi:Init management short buffer num: 32
I (600) wifi:Init dynamic tx buffer num: 32
I (600) wifi:Init static rx buffer size: 1600
I (610) wifi:Init static rx buffer num: 10
I (610) wifi:Init dynamic rx buffer num: 32
I (620) wifi_init: rx ba win: 6
I (620) wifi_init: accept mbox: 6
I (620) wifi_init: tcpip mbox: 32
I (620) wifi_init: udp mbox: 6
I (630) wifi_init: tcp mbox: 6
I (630) wifi_init: tcp tx win: 5760
I (630) wifi_init: tcp rx win: 5760
I (640) wifi_init: tcp mss: 1440
I (640) wifi_init: WiFi IRAM OP enabled
I (640) wifi_init: WiFi RX IRAM OP enabled
I (650) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (650) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (660) LAB_AUTH_ASSOC: ==================================================================
I (670) LAB_AUTH_ASSOC:   Lab 5.3: Wi-Fi Authentication & Association Phase (ESP-IDF Forensic)
I (680) LAB_AUTH_ASSOC: ==================================================================
I (680) LAB_AUTH_ASSOC: 

I (690) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (700) LAB_AUTH_ASSOC: >>> Experiment 5.3.1: Link-Layer Auth & Assoc Phase Test
I (700) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (710) LAB_AUTH_ASSOC:   Target SSID    : "eem_Luna"
I (720) LAB_AUTH_ASSOC:   Target Password: "123456789naeem"
I (720) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_stop()
I (730) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
W (730) wifi:Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2
I (790) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (790) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_start()
I (790) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (880) wifi:mode : sta (88:57:21:ad:64:98)
I (880) wifi:enable tsf
I (880) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (880) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (880) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (890) LAB_AUTH_ASSOC: [FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...
I (900) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (910) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (920) wifi:new:<1,0>, old:<1,0>, ap:<255,255>, sta:<1,0>, prof:1, snd_ch_cfg:0x0
I (920) wifi:state: init -> auth (0xb0)
I (1920) wifi:state: auth -> assoc (0x0)
I (1950) wifi:state: assoc -> run (0x10)
I (1980) wifi:connected with eem_Luna, aid = 2, channel 1, BW20, bssid = c6:f8:06:fe:7a:b0
I (1980) wifi:security: WPA3-SAE, phy: bgn, rssi: -39
I (1990) wifi:pm start, type: 1

I (1990) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (1990) LAB_AUTH_ASSOC: =======================================================
I (2000) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (2010) LAB_AUTH_ASSOC:   [SUCCESS]: Phase 2 (Auth) & Phase 3 (Assoc) COMPLETED!
I (2010) LAB_AUTH_ASSOC:   -> Connected SSID        : eem_Luna
I (2020) LAB_AUTH_ASSOC:   -> BSSID (MAC Address)   : C6:F8:06:FE:7A:B0
I (2020) LAB_AUTH_ASSOC:   -> Channel               : 1
I (2030) LAB_AUTH_ASSOC:   -> Auth Mode             : 6
I (2030) LAB_AUTH_ASSOC:   -> Association ID (AID)  : 3
I (2040) LAB_AUTH_ASSOC: =======================================================
I (2000) wifi:dp: 2, bi: 102400, li: 4, scale listen interval from 307200 us to 409600 us
I (2050) wifi:AP's beacon interval = 102400 us, DTIM period = 2
I (2060) wifi:<ba-add>idx:0 (ifx:0, c6:f8:06:fe:7a:b0), tid:0, ssn:0, winSize:64
I (2060) LAB_AUTH_ASSOC: [RESULT]: TEST PASSED - Phase 2 (Auth) & Phase 3 (Assoc) Successful!
I (3080) esp_netif_handlers: sta ip: 10.65.224.169, mask: 255.255.255.0, gw: 10.65.224.40
I (4080) LAB_AUTH_ASSOC: 

I (4080) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (4080) LAB_AUTH_ASSOC: >>> Experiment 5.3.2: Link-Layer Test - Non-Existent AP
I (4080) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (4090) LAB_AUTH_ASSOC:   Target SSID    : "NON_EXISTENT_AP_9999"
I (4100) LAB_AUTH_ASSOC:   Target Password: "12345678"
I (4100) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_stop()
I (4110) wifi:state: run -> init (0x0)
I (4120) wifi:pm stop, total sleep time: 1759942 us / 2128482 us

I (4120) wifi:<ba-del>idx:0, tid:0
I (4120) wifi:new:<1,0>, old:<1,0>, ap:<255,255>, sta:<1,0>, prof:1, snd_ch_cfg:0x0
W (4130) LAB_AUTH_ASSOC: =======================================================
W (4130) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (4140) LAB_AUTH_ASSOC:   -> Target SSID          : eem_Luna
W (4150) LAB_AUTH_ASSOC:   -> Reason Code (Decimal): 8
W (4150) LAB_AUTH_ASSOC:   -> Reason Code (Hex)    : 0x08
W (4160) LAB_AUTH_ASSOC:   -> Reason Diagnosis     : OTHER_DISCONNECT_REASON
W (4160) LAB_AUTH_ASSOC: =======================================================
I (4170) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (4180) wifi:flush txq
I (4180) wifi:stop sw txq
I (4180) wifi:lmac stop hw txq
I (4180) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
W (4190) wifi:Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2
I (4250) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (4250) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_start()
I (4250) wifi:mode : sta (88:57:21:ad:64:98)
I (4250) wifi:enable tsf
I (4260) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (4260) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (4270) LAB_AUTH_ASSOC: [FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...
I (4280) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (4280) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (4290) LAB_AUTH_ASSOC: [RESULT]: TEST FAILED - Disconnected event captured in Link-Layer.
I (4300) LAB_AUTH_ASSOC: ==================================================================
I (4300) LAB_AUTH_ASSOC:   [Phase 2 & Phase 3 Completed: Link-Layer Auth & Assoc Finished]
I (4310) LAB_AUTH_ASSOC: ==================================================================
I (4320) main_task: Returned from app_main()
W (6700) LAB_AUTH_ASSOC: =======================================================
W (6700) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (6700) LAB_AUTH_ASSOC:   -> Target SSID          : NON_EXISTENT_AP_9999
W (6710) LAB_AUTH_ASSOC:   -> Reason Code (Decimal): 201
W (6710) LAB_AUTH_ASSOC:   -> Reason Code (Hex)    : 0xC9
W (6720) LAB_AUTH_ASSOC:   -> Reason Diagnosis     : WIFI_REASON_NO_AP_FOUND (201) [Phase 1: SSID Not Found]
W (6730) LAB_AUTH_ASSOC: =======================================================

```


## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองในระดับ Link Layer

| ข้อการทดลอง | สถานการณ์ทดสอบ                           |        Event ที่ได้รับ        | ผลการผูกสัมพันธ์ Link Layer | ค่า Association ID (AID) ที่ได้ | Reason Code (ถ้ามี) |
| :---------: | :--------------------------------------- | :---------------------------: | :-------------------------: | :-----------------------------: | :------------------ |
|  **5.3.1**  | ร้องขอ Auth & Assoc กับ AP มีอยู่จริง    |  `WIFI_EVENT_STA_CONNECTED`   |           Passed            |                3                | -                   |
|  **5.3.2**  | ร้องขอ Auth & Assoc กับ AP ไม่มีอยู่จริง | `WIFI_EVENT_STA_DISCONNECTED` |           Failed            |                -                | 201 / 0xC9          |

### 6.2 บันทึกข้อมูล Link Layer จาก Event `WIFI_EVENT_STA_CONNECTED` (ข้อ 5.3.1)

| พารามิเตอร์ Link Layer   | ค่าที่อ่านได้จริงจาก Forensic Log |
| :----------------------- | :-------------------------------- |
| **SSID**                 | eem_Luna                          |
| **BSSID (MAC Address)**  | C6:F8:06:FE:7A:B0                 |
| **Channel**              | 1                                 |
| **Auth Mode Enum**       | 6                                 |
| **Association ID (AID)** | 3                                 |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. **Association ID (AID)** คืออะไร มีบทบาทอย่างไรใน Phase 3 และส่งคืนมาในโครงสร้างข้อมูลตัวแปรใด?
		Ans
		- **คือ:** หมายเลขระบุตัวตนชั่วคราว (1-2007) ที่ AP ออกให้กับ Station เพื่อแทนตัวอุปกรณ์หลังจากผูกสัมพันธ์สำเร็จ
    
		- **บทบาท:** ใช้สำหรับจัดการคิวส่งข้อมูล (Data Buffering) และ Power Saving (PS-Poll/TIM) ในระดับ Wi-Fi Frame
    
		- **โครงสร้างข้อมูล:** ส่งคืนมาใน struct `wifi_event_sta_connected_t` ผ่านสมาชิก `.aid`
2. เหตุใดการเชื่อมต่อ Wi-Fi ความปลอดภัยแบบ WPA2-PSK จึงสามารถผ่าน Phase 2 (Authentication) และ Phase 3 (Association) จนเกิด Event `WIFI_EVENT_STA_CONNECTED` ได้สำเร็จ แม้ผู้ใช้จะป้อนรหัสผ่าน (Password) ผิด?
		Ans
		เพราะ Phase 2 (Open Auth) และ Phase 3 (Association) เป็นเพียงกระบวนการเชื่อมต่อในระดับ Link Layer 802.11 ซึ่งไม่ได้ใช้นำ Passphrase มาตรวจสอบ
		การตรวจสอบ Password จริงจะเกิดขึ้นหลังจากนั้นใน Phase 4 (4-Way Handshake) หากใส่รหัสผิด จะเกิด Disconnect ตามมาภายหลังด้วย `Reason 202 (AUTH_FAIL)`
3. หาก Router มีการตั้งค่า **MAC Address Filtering** (อนุญาตเฉพาะ MAC ที่ลงทะเบียน) ESP32 จะล้มเหลวในเฟสใด และจะส่ง Disconnect Reason Code ใดออกมา?
		Ans
		**เฟสที่ล้มเหลว:** เฟส 3 (Association Phase) เนื่องจาก AP จะปฏิเสธกรอบคำขอ Association Response
		**Reason Code:** `Reason Code 15` (`WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT` หรือ `1` / `15` ตามการแสดงผลของ AP เมื่อถูก Reject ด้วยเหตุผล Unspecified / ACL)
4. สรุปความแตกต่างสำคัญระหว่างจุดสิ้นสุดของ **Phase 3 (Link-Layer Connected)** กับจุดสิ้นสุดของ **Phase 5 (IP Address Assigned)**
		Ans
		**Phase 3 (Link-Layer Connected):** บอร์ดจับคู่กับ AP ในระดับชั้น Data Link Layer (Layer 2) ได้แล้ว ได้รับค่า AID แต่ยังส่งข้อมูลผ่านอินเทอร์เน็ต/เครือข่าย IP ไม่ได้
		**Phase 5 (IP Address Assigned):** บอร์ดผ่านการตรวจรหัสผ่าน (Layer 2 Security) และเจรจาขอ IP จาก DHCP Server สำเร็จ (Layer 3) พร้อมส่งข้อมูลแบบ TCP/IP ออกสู่อินเทอร์เน็ตได้แล้ว