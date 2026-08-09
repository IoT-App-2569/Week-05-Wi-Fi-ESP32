## 6. ตารางบันทึกผลการทดลอง (Experiment Results)
---

```c
rst:0x1 (POWERON_RE�H(
B��J���� Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (58�ets Jul 29 2019 12:21:46

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
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=19e28h (106024) map
I (124) esp_image: segment 1: paddr=00029e50 vaddr=3ffb0000 size=03eech ( 16108) load
I (130) esp_image: segment 2: paddr=0002dd44 vaddr=40080000 size=022d4h (  8916) load
I (134) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=860f0h (549104) map
I (323) esp_image: segment 4: paddr=000b6118 vaddr=400822d4 size=15b38h ( 88888) load
I (358) esp_image: segment 5: paddr=000cbc58 vaddr=50000000 size=00020h (    32) load
I (370) boot: Loaded app from partition at offset 0x10000
I (370) boot: Disabling RNG early entropy source...
I (380) cpu_start: Multicore app
I (389) cpu_start: Pro cpu start user code
I (389) cpu_start: cpu freq: 160000000 Hz
I (389) app_init: Application information:
I (389) app_init: Project name:     LED_Blink
I (393) app_init: App version:      1
I (396) app_init: Compile time:     Aug  6 2026 10:54:55
I (402) app_init: ELF file SHA256:  bea199af4...
I (406) app_init: ESP-IDF:          v5.5.1
I (410) efuse_init: Min chip rev:     v0.0
I (413) efuse_init: Max chip rev:     v3.99 
I (417) efuse_init: Chip rev:         v3.1
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
I (484) LAB_AUTH_ASSOC: [FORENSIC]: Call nvs_flash_init()
I (504) LAB_AUTH_ASSOC: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (504) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_netif_init()
I (504) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_event_loop_create_default()
I (514) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (514) LAB_AUTH_ASSOC: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbd8bc
I (524) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_init(&cfg)
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
I (624) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (624) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (634) LAB_AUTH_ASSOC: ==================================================================
I (644) LAB_AUTH_ASSOC:   Lab 5.3: Wi-Fi Authentication & Association Phase (ESP-IDF Forensic)
I (654) LAB_AUTH_ASSOC: ==================================================================
I (654) LAB_AUTH_ASSOC: 

I (664) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (664) LAB_AUTH_ASSOC: >>> Experiment 5.3.1: Link-Layer Auth & Assoc Phase Test
I (674) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (684) LAB_AUTH_ASSOC:   Target SSID    : "POCO X7 Pro"
I (684) LAB_AUTH_ASSOC:   Target Password: "1122334455"
I (694) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_stop()
I (704) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
W (704) wifi:Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2
I (744) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (744) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_start()
I (744) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (824) wifi:mode : sta (14:33:5c:0d:cd:7c)
I (824) wifi:enable tsf
I (834) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (834) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (834) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (844) LAB_AUTH_ASSOC: [FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...
I (854) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (854) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (864) wifi:new:<13,0>, old:<1,0>, ap:<255,255>, sta:<13,0>, prof:1, snd_ch_cfg:0x0
I (874) wifi:state: init -> auth (0xb0)
I (874) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (924) wifi:state: auth -> assoc (0x0)
I (954) wifi:state: assoc -> run (0x10)
I (984) wifi:connected with POCO X7 Pro, aid = 2, channel 13, BW20, bssid = 16:fb:5d:e5:3d:c7
I (984) wifi:security: WPA2-PSK, phy: bgn, rssi: -39
I (994) wifi:pm start, type: 1

I (994) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (994) LAB_AUTH_ASSOC: =======================================================
I (1004) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (1004) LAB_AUTH_ASSOC:   [SUCCESS]: Phase 2 (Auth) & Phase 3 (Assoc) COMPLETED!
I (1014) LAB_AUTH_ASSOC:   -> Connected SSID        : POCO X7 Pro
I (1024) LAB_AUTH_ASSOC:   -> BSSID (MAC Address)   : 16:FB:5D:E5:3D:C7
I (1024) LAB_AUTH_ASSOC:   -> Channel               : 13
I (1034) LAB_AUTH_ASSOC:   -> Auth Mode             : 3
I (1034) LAB_AUTH_ASSOC:   -> Association ID (AID)  : 3
I (1044) LAB_AUTH_ASSOC: =======================================================
I (1054) LAB_AUTH_ASSOC: [RESULT]: TEST PASSED - Phase 2 (Auth) & Phase 3 (Assoc) Successful!
I (1064) wifi:dp: 2, bi: 102400, li: 4, scale listen interval from 307200 us to 409600 us
I (1064) wifi:AP's beacon interval = 102400 us, DTIM period = 2
I (2024) esp_netif_handlers: sta ip: 10.42.102.249, mask: 255.255.255.0, gw: 10.42.102.133
I (3054) LAB_AUTH_ASSOC: 

I (3054) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (3054) LAB_AUTH_ASSOC: >>> Experiment 5.3.2: Link-Layer Test - Non-Existent AP
I (3054) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (3064) LAB_AUTH_ASSOC:   Target SSID    : "POCO X7 Pro"
I (3074) LAB_AUTH_ASSOC:   Target Password: "1122334455"
I (3074) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_stop()
I (3084) wifi:state: run -> init (0x0)
I (3094) wifi:pm stop, total sleep time: 1808801 us / 2098044 us

I (3094) wifi:new:<13,0>, old:<13,0>, ap:<255,255>, sta:<13,0>, prof:1, snd_ch_cfg:0x0
W (3104) LAB_AUTH_ASSOC: =======================================================
W (3104) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (3114) LAB_AUTH_ASSOC:   -> Target SSID          : POCO X7 Pro
W (3114) LAB_AUTH_ASSOC:   -> Reason Code (Decimal): 8
W (3124) LAB_AUTH_ASSOC:   -> Reason Code (Hex)    : 0x08
W (3124) LAB_AUTH_ASSOC:   -> Reason Diagnosis     : OTHER_DISCONNECT_REASON
W (3134) LAB_AUTH_ASSOC: =======================================================
I (3144) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (3174) wifi:flush txq
I (3174) wifi:stop sw txq
I (3174) wifi:lmac stop hw txq
I (3174) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
W (3174) wifi:Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2
I (3184) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (3194) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_start()
I (3194) wifi:mode : sta (14:33:5c:0d:cd:7c)
I (3194) wifi:enable tsf
I (3204) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (3204) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (3204) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (3224) LAB_AUTH_ASSOC: [FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...
I (3224) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (3234) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (3244) LAB_AUTH_ASSOC: [RESULT]: TEST FAILED - Disconnected event captured in Link-Layer.
I (3244) LAB_AUTH_ASSOC: ==================================================================
I (3254) LAB_AUTH_ASSOC:   [Phase 2 & Phase 3 Completed: Link-Layer Auth & Assoc Finished]
I (3264) LAB_AUTH_ASSOC: ==================================================================
I (3274) main_task: Returned from app_main()
I (3324) wifi:new:<13,0>, old:<1,0>, ap:<255,255>, sta:<13,0>, prof:1, snd_ch_cfg:0x0
I (3324) wifi:state: init -> auth (0xb0)
I (3324) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (3344) wifi:state: auth -> assoc (0x0)
I (3374) wifi:state: assoc -> run (0x10)
I (3394) wifi:connected with POCO X7 Pro, aid = 3, channel 13, BW20, bssid = 16:fb:5d:e5:3d:c7
I (3394) wifi:security: WPA2-PSK, phy: bgn, rssi: -39
I (3394) wifi:pm start, type: 1

I (3404) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (3414) LAB_AUTH_ASSOC: =======================================================
I (3414) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (3424) LAB_AUTH_ASSOC:   [SUCCESS]: Phase 2 (Auth) & Phase 3 (Assoc) COMPLETED!
I (3424) LAB_AUTH_ASSOC:   -> Connected SSID        : POCO X7 Pro
I (3434) LAB_AUTH_ASSOC:   -> BSSID (MAC Address)   : 16:FB:5D:E5:3D:C7
I (3444) LAB_AUTH_ASSOC:   -> Channel               : 13
I (3444) LAB_AUTH_ASSOC:   -> Auth Mode             : 3
I (3454) LAB_AUTH_ASSOC:   -> Association ID (AID)  : 3
I (3454) LAB_AUTH_ASSOC: =======================================================
I (3424) wifi:dp: 2, bi: 102400, li: 4, scale listen interval from 307200 us to 409600 us
I (3474) wifi:AP's beacon interval = 102400 us, DTIM period = 2
I (4484) esp_netif_handlers: sta ip: 10.42.102.249, mask: 255.255.255.0, gw: 10.42.102.133

```
---

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองในระดับ Link Layer

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event ที่ได้รับ | ผลการผูกสัมพันธ์ Link Layer | ค่า Association ID (AID) ที่ได้ | Reason Code (ถ้ามี) |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.3.1** | ร้องขอ Auth & Assoc กับ AP มีอยู่จริง |WIFI_EVENT_STA_CONNECTED | TEST PASSED |3 |ไม่มี |
| **5.3.2** | ร้องขอ Auth & Assoc กับ AP ไม่มีอยู่จริง |WIFI_EVENT_STA_CONNECTED | TEST PASSED |3 |ไม่มี |

### 6.2 บันทึกข้อมูล Link Layer จาก Event `WIFI_EVENT_STA_CONNECTED` (ข้อ 5.3.1)

| พารามิเตอร์ Link Layer | ค่าที่อ่านได้จริงจาก Forensic Log |
| :--- | :--- |
| **SSID** |	POCO X7 Pro |
| **BSSID (MAC Address)** |16:FB:5D:E5:3D:C7 |
| **Channel** |	13 |
| **Auth Mode Enum** |3 (WPA2_PSK) |
| **Association ID (AID)** |	3 |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. **Association ID (AID)** คืออะไร มีบทบาทอย่างไรใน Phase 3 และส่งคืนมาในโครงสร้างข้อมูลตัวแปรใด?
```c
Association ID (AID) คือหมายเลขที่ Access Point (AP) กำหนดให้กับ Station (STA) หลังจากการ Association สำเร็จใน Phase 3 เพื่อใช้ระบุและจัดการ STA แต่ละเครื่องภายในเครือข่าย เช่น การจัดการข้อมูลและสถานะของ Client โดยจากผลการทดลองพบค่า AID เท่ากับ 3 และค่าดังกล่าวถูกส่งกลับมาในโครงสร้าง `wifi_event_sta_connected_t` ผ่านฟิลด์ `aid`
```
2. เหตุใดการเชื่อมต่อ Wi-Fi ความปลอดภัยแบบ WPA2-PSK จึงสามารถผ่าน Phase 2 (Authentication) และ Phase 3 (Association) จนเกิด Event `WIFI_EVENT_STA_CONNECTED` ได้สำเร็จ แม้ผู้ใช้จะป้อนรหัสผ่าน (Password) ผิด?
```c
เนื่องจาก Phase 2 (Authentication) ของการเชื่อมต่อแบบ WPA2-PSK ที่ใช้ Open System Authentication เป็นการยืนยันตัวตนในระดับ 802.11 และยังไม่ได้ตรวจสอบ Password ของ WPA2-PSK โดยตรง ส่วน Phase 3 (Association) เป็นขั้นตอนการขอเข้าร่วมเครือข่ายกับ AP ดังนั้นจึงสามารถเกิด Event `WIFI_EVENT_STA_CONNECTED` ได้ก่อนที่จะตรวจสอบ Password จริง

การตรวจสอบ Password และการสร้างกุญแจสำหรับการเข้ารหัสจะเกิดขึ้นใน Phase 4 (4-Way Handshake) หาก Password ผิด การทำ Handshake จะไม่สำเร็จและอุปกรณ์จะถูก Disconnect ในขั้นตอนถัดไป
```
3. หาก Router มีการตั้งค่า **MAC Address Filtering** (อนุญาตเฉพาะ MAC ที่ลงทะเบียน) ESP32 จะล้มเหลวในเฟสใด และจะส่ง Disconnect Reason Code ใดออกมา?
```c
หาก Router เปิดใช้งาน MAC Address Filtering และ MAC Address ของ ESP32 ไม่อยู่ในรายการที่อนุญาต ESP32 จะไม่สามารถผ่านขั้นตอน Association ได้ เนื่องจาก AP จะปฏิเสธคำขอ Association ของอุปกรณ์ โดยจะล้มเหลวใน Phase 3 (Association) และอาจได้รับ Disconnect Reason Code ที่เกี่ยวข้องกับการ Association Failure เช่น `WIFI_REASON_ASSOC_FAIL` ซึ่งในคำตอบตัวอย่างระบุค่าเป็น 3 หรือ 203

```
4. สรุปความแตกต่างสำคัญระหว่างจุดสิ้นสุดของ **Phase 3 (Link-Layer Connected)** กับจุดสิ้นสุดของ **Phase 5 (IP Address Assigned)**
```c
จุดสิ้นสุดของ Phase 3 (Link-Layer Connected) คือจุดที่ ESP32 ผ่านกระบวนการ Authentication และ Association ในระดับ 802.11 สำเร็จ และได้รับ Event `WIFI_EVENT_STA_CONNECTED` พร้อมค่า AID แต่ยังไม่ได้รับ IP Address จาก DHCP

ส่วนจุดสิ้นสุดของ Phase 5 (IP Address Assigned) คือขั้นที่ ESP32 ได้รับ IP Address จาก DHCP Server สำเร็จ โดยจากผลการทดลองพบ IP Address เป็น `10.42.102.249` ซึ่งหมายความว่าอุปกรณ์ได้รับการกำหนดค่าระดับ IP และสามารถนำไปใช้สื่อสารผ่านเครือข่าย TCP/IP ได้
```
