# ใบงานที่ 5.2: การยืนยันตัวตน การสถาปนาการเชื่อมต่อ และการรับหมายเลข IP Address (Wi-Fi Connection & IP Assignment)


```

--- 0x40080638: call_start_cpu0 at C:/Users/09677/esp/v5.5.1/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v5.5.1-dirty 2nd stage bootloader
I (29) boot: compile time Aug  3 2026 10:38:45
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
I (135) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=861fch (549372) map
I (324) esp_image: segment 4: paddr=000b6224 vaddr=400822b4 size=15b58h ( 88920) load
I (359) esp_image: segment 5: paddr=000cbd84 vaddr=50000000 size=00020h (    32) load
I (371) boot: Loaded app from partition at offset 0x10000
I (371) boot: Disabling RNG early entropy source...
I (381) cpu_start: Multicore app
I (390) cpu_start: Pro cpu start user code
I (390) cpu_start: cpu freq: 160000000 Hz
I (390) app_init: Application information:
I (390) app_init: Project name:     wifi_connection_phase
I (395) app_init: App version:      37de524-dirty
I (399) app_init: Compile time:     Aug  3 2026 10:37:14
I (404) app_init: ELF file SHA256:  3d3afb30a...
I (409) app_init: ESP-IDF:          v5.5.1-dirty
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
I (500) LAB_WIFI_CONN: [FORENSIC]: Call nvs_flash_init()
I (530) LAB_WIFI_CONN: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (530) LAB_WIFI_CONN: [FORENSIC]: Call esp_netif_init()
I (530) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_loop_create_default()
I (540) LAB_WIFI_CONN: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (540) LAB_WIFI_CONN: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbd980
I (550) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_init(&cfg)
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
I (650) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (650) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_handler_instance_register(IP_EVENT)
I (660) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (670) LAB_WIFI_CONN: ==================================================================
I (680) LAB_WIFI_CONN:   Lab 5.2: Wi-Fi Connection & IP Assignment (ESP-IDF Forensic)
I (680) LAB_WIFI_CONN: ==================================================================
I (690) LAB_WIFI_CONN: 

I (690) LAB_WIFI_CONN: ------------------------------------------------------------------
I (700) LAB_WIFI_CONN: >>> Experiment 5.2.1: Connection Test - Correct Credentials
I (710) LAB_WIFI_CONN: ------------------------------------------------------------------
I (720) LAB_WIFI_CONN:   Target SSID: "eem_Luna"
I (720) LAB_WIFI_CONN:   Target Password: "123456789naeem"
I (730) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (730) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (740) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (750) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (750) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (840) wifi:mode : sta (88:57:21:ad:64:98)
I (840) wifi:enable tsf
I (840) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (850) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (850) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (860) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (860) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (880) wifi:new:<1,0>, old:<1,0>, ap:<255,255>, sta:<1,0>, prof:1, snd_ch_cfg:0x0
I (880) wifi:state: init -> auth (0xb0)
I (1880) wifi:state: auth -> assoc (0x0)
I (1920) wifi:state: assoc -> run (0x10)
I (1990) wifi:connected with eem_Luna, aid = 2, channel 1, BW20, bssid = 2e:2b:53:fb:4b:ac
I (1990) wifi:security: WPA3-SAE, phy: bgn, rssi: -45
I (2010) wifi:pm start, type: 1

I (2010) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (2010) LAB_WIFI_CONN: =======================================================
I (2010) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (2020) LAB_WIFI_CONN:   -> Connected to SSID : eem_Luna
I (2030) LAB_WIFI_CONN:   -> BSSID            : 2E:2B:53:FB:4B:AC
I (2030) LAB_WIFI_CONN:   -> Channel          : 1
I (2040) LAB_WIFI_CONN:   -> Auth Mode        : 6
I (2040) LAB_WIFI_CONN: =======================================================
I (2040) wifi:dp: 2, bi: 102400, li: 4, scale listen interval from 307200 us to 409600 us
I (2060) wifi:AP's beacon interval = 102400 us, DTIM period = 2
I (2060) wifi:state: run -> init (0x5a0)
I (2080) wifi:pm stop, total sleep time: 0 us / 68684 us

I (2080) wifi:<ba-del>idx:0, tid:0
I (2080) wifi:new:<1,0>, old:<1,0>, ap:<255,255>, sta:<1,0>, prof:1, snd_ch_cfg:0x0
W (2080) LAB_WIFI_CONN: =======================================================
W (2090) LAB_WIFI_CONN: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP
W (2100) LAB_WIFI_CONN:   -> Target SSID          : eem_Luna
W (2100) LAB_WIFI_CONN:   -> Reason Code (Decimal): -
W (2110) LAB_WIFI_CONN:   -> Reason Code (Hex)    : -
W (2110) LAB_WIFI_CONN:   -> Reason Description   : CONNECTED_SUCCESSFULLY
W (2120) LAB_WIFI_CONN: =======================================================
E (2090) wifi:addba response cb: sta bss deleted
W (2130) LAB_WIFI_CONN: [RESULT]: TEST PASSED - Connected to AP successfully!.
I (4140) LAB_WIFI_CONN: 

I (4140) LAB_WIFI_CONN: ------------------------------------------------------------------
I (4140) LAB_WIFI_CONN: >>> Experiment 5.2.2: Connection Test - Wrong SSID (No AP Found)
I (4140) LAB_WIFI_CONN: ------------------------------------------------------------------
I (4150) LAB_WIFI_CONN:   Target SSID: "NON_EXISTENT_SSID_9999"
I (4160) LAB_WIFI_CONN:   Target Password: "12345678"
I (4160) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (4170) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (4170) wifi:flush txq
I (4170) wifi:stop sw txq
I (4180) wifi:lmac stop hw txq
I (4180) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (4280) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (4280) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (4290) wifi:mode : sta (88:57:21:ad:64:98)
I (4290) wifi:enable tsf
I (4290) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (4290) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (4300) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (4310) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (6720) LAB_WIFI_CONN: =======================================================
W (6720) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (6730) LAB_WIFI_CONN:   -> Target SSID          : NON_EXISTENT_SSID_9999
W (6730) LAB_WIFI_CONN:   -> Reason Code (Decimal): 201
W (6740) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0xC9
W (6740) LAB_WIFI_CONN:   -> Reason Description   : WIFI_REASON_NO_AP_FOUND (201)
W (6750) LAB_WIFI_CONN: =======================================================
W (6760) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (8760) LAB_WIFI_CONN: 

I (8760) LAB_WIFI_CONN: ------------------------------------------------------------------
I (8760) LAB_WIFI_CONN: >>> Experiment 5.2.3: Connection Test - Wrong Password (Auth/Handshake Fail)
I (8760) LAB_WIFI_CONN: ------------------------------------------------------------------
I (8770) LAB_WIFI_CONN:   Target SSID: "eem_Luna"
I (8780) LAB_WIFI_CONN:   Target Password: "WRONG_PASS_9999"
I (8780) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (8790) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (8790) wifi:flush txq
I (8790) wifi:stop sw txq
I (8800) wifi:lmac stop hw txq
I (8800) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (8860) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (8860) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (8870) wifi:mode : sta (88:57:21:ad:64:98)
I (8870) wifi:enable tsf
I (8870) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (8880) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (8890) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (8870) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (8910) wifi:new:<1,0>, old:<1,0>, ap:<255,255>, sta:<1,0>, prof:1, snd_ch_cfg:0x0
I (8910) wifi:state: init -> auth (0xb0)
I (9890) wifi:state: auth -> init (0x600)
I (9910) wifi:new:<1,0>, old:<1,0>, ap:<255,255>, sta:<1,0>, prof:1, snd_ch_cfg:0x0
W (9910) LAB_WIFI_CONN: =======================================================
W (9910) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (9920) LAB_WIFI_CONN:   -> Target SSID          : eem_Luna
W (9920) LAB_WIFI_CONN:   -> Reason Code (Decimal): 202
W (9930) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0xCA
W (9930) LAB_WIFI_CONN:   -> Reason Description   : WIFI_REASON_AUTH_FAIL (202)
W (9940) LAB_WIFI_CONN: =======================================================
W (9950) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (9950) LAB_WIFI_CONN: ==================================================================
I (9960) LAB_WIFI_CONN:   [Phase 2/3/4/5 Completed: Wi-Fi Connection Lab Finished]
I (9970) LAB_WIFI_CONN: ==================================================================
I (9980) main_task: Returned from app_main()
```

## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองทั้ง 3 สถานการณ์

| ข้อการทดลอง | สถานการณ์ทดสอบ                     |    Event สุดท้ายที่ได้รับ     | ผลลัพธ์ (Passed/Failed) | Reason Code (Decimal / Hex) | คำอธิบาย Reason Code      |
| :---------: | :--------------------------------- | :---------------------------: | :---------------------: | :-------------------------: | :------------------------ |
|  **5.2.1**  | SSID และ Password ถูกต้อง          |     `IP_EVENT_STA_GOT_IP`     |         Passed          |              -              | `CONNECTED_SUCCESSFULLY`  |
|  **5.2.2**  | ระบุ SSID ผิด (ไม่มีในระบบ)        | `WIFI_EVENT_STA_DISCONNECTED` |         Failed          |         201 / 0xC9          | `WIFI_REASON_NO_AP_FOUND` |
|  **5.2.3**  | ระบุ SSID ถูกต้อง แต่ Password ผิด | `WIFI_EVENT_STA_DISCONNECTED` |         Failed          |         202 / 0xCA          | `WIFI_REASON_NO_AP_FOUND` |

### 6.2 บันทึกข้อมูลเครือข่ายจากการเชื่อมต่อสำเร็จ (ข้อ 5.2.1)

| พารามิเตอร์เครือข่าย    | ค่าที่ได้รับจริงจาก DHCP |
| :---------------------- | :----------------------- |
| **SSID**                | eem_Luna                 |
| **BSSID (MAC Address)** | 2E:2B:53:FB:4B:AC        |
| **Channel**             | 1                        |
| **IP Address**          | 192.168.43.2             |
| **Subnet Mask**         | 255.255.255.0            |
| **Default Gateway**     | 192.168.43.1             |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการระบุ SSID ผิด (ข้อ 5.2.2) จึงส่งผลให้เกิด Disconnect Event ด้วย Reason Code `201` (`WIFI_REASON_NO_AP_FOUND`) ตั้งแต่เฟส Scan?
		**สาเหตุที่ระบุ SSID ผิดส่งผลให้เกิด Disconnect Reason 201 ตั้งแต่เฟส Scan:** ก่อนจะเริ่มกระบวนการ Authentication ตัว ESP32 จะทำการสแกนหา Beacon หรือ Probe Response จาก AP ที่ระบุ SSID ไว้ก่อน หากสแกนครบทุกช่องความถี่แล้วไม่พบสัญญาณจาก SSID นั้น ESP32 จึงยุติกระบวนการเชื่อมต่อทันทีตั้งแต่ระดับกายภาพ (MAC/PHY layer) และแจ้งเตือนด้วย `WIFI_REASON_NO_AP_FOUND`
2. เหตุใดการพิมพ์ Password ผิด (ข้อ 5.2.3) จึงผ่านเฟส Auth และ Assoc มาได้ แต่มาล้มเหลวในเฟส 4-Way Handshake (Reason Code `15` หรือ `204`)?
		**สาเหตุที่พิมพ์ Password ผิดแล้วผ่านเฟส Auth/Assoc แต่ล้มเหลวในเฟส 4-Way Handshake:** ในสถาปัตยกรรม 802.11 (WPA2/WPA3-Personal) ขั้นตอน Auth และ Assoc เป็นเพียงการตกลงสร้างการเชื่อมต่อระดับเปิดทางกายภาพเบื้องต้น (Open Authentication) เท่านั้น ซึ่งยังไม่มีการตรวจสอบความถูกต้องของ Password เมื่อผ่าน 2 ขั้นตอนนี้มาได้ จึงจะเข้าสู่กระบวนการ **4-Way Handshake** ซึ่งใช้ Password ในการคำนวณสร้างกุญแจเข้ารหัส (PMK/PTK) เมื่อ Password ผิด อุปกรณ์จะส่งข้อความล้มเหลว (Handshake Fail / Auth Fail) ทำให้หลุดการเชื่อมต่อในที่สุด
3. ลำดับการเกิด Event ระหว่าง **`WIFI_EVENT_STA_CONNECTED`** กับ **`IP_EVENT_STA_GOT_IP`** Event ใดเกิดขึ้นก่อนกัน และมีความหมายทางกายภาพของ Layer Network ต่างกันอย่างไร?
		- **ลำดับการเกิด:** `WIFI_EVENT_STA_CONNECTED` เกิดขึ้นก่อน `IP_EVENT_STA_GOT_IP`
    
		- **ความหมาย:**
    
		    - `WIFI_EVENT_STA_CONNECTED` หมายถึง ความสำเร็จใน **Data Link Layer (Layer 2)** — ตัวเครื่อง ESP32 และ AP สามารถต่อสายอากาศรับ-ส่งเฟรมข้อมูล 802.11 กันได้แล้ว
        
		    - `IP_EVENT_STA_GOT_IP` หมายถึง ความสำเร็จใน **Network Layer (Layer 3)** — ตัวเครื่องได้รับหมายเลข IP, Subnet Mask และ Gateway จาก DHCP Server เรียบร้อยแล้ว พร้อมสำหรับการรับ-ส่งข้อมูลบนเครือข่าย Internet (IP/TCP/UDP)
4. สมาชิกตัวแปร `reason` ในโครงสร้าง `wifi_event_sta_disconnected_t` มีประโยชน์อย่างไรต่อการออกแบบระบบค้นหาสาเหตุและกู้คืนการเชื่อมต่อ (Auto-Reconnection Mechanism) ในแอปพลิเคชัน IoT?
		- หากเกิด `WIFI_REASON_NO_AP_FOUND` (201): ระบบอาจรอกรอบเวลาสแกนใหม่ (Exponential Backoff) หรือสลับไปใช้ Wi-Fi สำรอง
    
		- หากเกิด `WIFI_REASON_AUTH_FAIL` (202): ระบบควรหยุดการพยายามต่อซ้ำทันที แล้วแจ้งเตือนผู้ใช้ให้เปลี่ยนรหัสผ่านใหม่ (ป้องกันการโดนล็อกเนื่องจากการต่อผิดรหัสผ่านรัวๆ)
    
		- หากเกิดเหตุชั่วคราว เช่น `WIFI_REASON_BEACON_TIMEOUT`: ระบบสามารถสั่ง `esp_wifi_connect()` ซ้ำใหม่ได้ทันที
