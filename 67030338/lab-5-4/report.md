# ใบงานที่ 5.4: กระบวนการแลกเปลี่ยนคีย์ความปลอดภัยและการจัดสรรหมายเลข IP Address (4-Way Handshake & IP Assignment Phase)
```
mode:DIO, clock div:2
load:0x3fff0030,len:6380
ho 0 tail 12 room 4
load:0x40078000,len:15916
load:0x40080400,len:3860
--- 0x40080400: _invalid_pc_placeholder at C:/Users/09677/esp/v5.5.1/esp-idf/components/xtensa/xtensa_vectors.S:2235
entry 0x40080638
--- 0x40080638: call_start_cpu0 at C:/Users/09677/esp/v5.5.1/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v5.5.1-dirty 2nd stage bootloader
I (29) boot: compile time Aug  3 2026 21:05:31
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
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=19ee8h (106216) map
I (125) esp_image: segment 1: paddr=00029f10 vaddr=3ffb0000 size=03eech ( 16108) load
I (131) esp_image: segment 2: paddr=0002de04 vaddr=40080000 size=02214h (  8724) load
I (135) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=861f0h (549360) map
I (324) esp_image: segment 4: paddr=000b6218 vaddr=40082214 size=15bf8h ( 89080) load
I (359) esp_image: segment 5: paddr=000cbe18 vaddr=50000000 size=00020h (    32) load
I (371) boot: Loaded app from partition at offset 0x10000
I (371) boot: Disabling RNG early entropy source...
I (381) cpu_start: Multicore app
I (390) cpu_start: Pro cpu start user code
I (390) cpu_start: cpu freq: 160000000 Hz
I (390) app_init: Application information:
I (390) app_init: Project name:     wifi_handshake_ip_phase
I (395) app_init: App version:      37de524-dirty
I (399) app_init: Compile time:     Aug  3 2026 21:04:31
I (405) app_init: ELF file SHA256:  ca25896be...
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
I (471) spi_flash: detected chip: generic
I (474) spi_flash: flash io: dio
W (477) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (490) main_task: Started on CPU0
I (500) main_task: Calling app_main()
I (500) LAB_HANDSHAKE_IP: [FORENSIC]: Call nvs_flash_init()
I (530) LAB_HANDSHAKE_IP: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (530) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_netif_init()
I (530) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_loop_create_default()
I (540) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (540) LAB_HANDSHAKE_IP: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbd980
I (550) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_init(&cfg)
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
I (650) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (650) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_handler_instance_register(IP_EVENT)
I (660) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (670) LAB_HANDSHAKE_IP: ==================================================================
I (680) LAB_HANDSHAKE_IP:   Lab 5.4: 4-Way Handshake & IP Assignment Phase (ESP-IDF Forensic)
I (690) LAB_HANDSHAKE_IP: ==================================================================
I (690) LAB_HANDSHAKE_IP: 

I (700) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (700) LAB_HANDSHAKE_IP: >>> Experiment 5.4.1: Handshake & IP Test - Correct Password
I (710) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (720) LAB_HANDSHAKE_IP:   Target SSID    : "eem_Luna"
I (720) LAB_HANDSHAKE_IP:   Target Password: "123456789naeem"
I (730) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_stop()
I (740) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (740) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (750) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_start()
I (760) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (840) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(0)
I (870) wifi:mode : sta (88:57:21:ad:64:98)
I (870) wifi:enable tsf
I (880) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (880) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (880) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (890) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_connect()
I (900) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (910) wifi:new:<1,0>, old:<1,0>, ap:<255,255>, sta:<1,0>, prof:1, snd_ch_cfg:0x0
I (910) wifi:state: init -> auth (0xb0)
I (1860) wifi:state: auth -> assoc (0x0)
I (1890) wifi:state: assoc -> run (0x10)
I (1950) wifi:connected with eem_Luna, aid = 1, channel 1, BW20, bssid = 4e:c2:e8:ad:4e:37
I (1950) wifi:security: WPA3-SAE, phy: bgn, rssi: -36
I (1970) wifi:pm start, type: 1

I (1970) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (1970) LAB_HANDSHAKE_IP: =======================================================
I (1980) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (1980) LAB_HANDSHAKE_IP:   -> Phase 2 (Auth) & Phase 3 (Assoc) PASSED
I (1990) LAB_HANDSHAKE_IP:   -> Connected SSID  : eem_Luna
I (2000) LAB_HANDSHAKE_IP:   -> BSSID           : 4E:C2:E8:AD:4E:37
I (2000) LAB_HANDSHAKE_IP:   -> Channel         : 1
I (2010) LAB_HANDSHAKE_IP:   -> Association ID  : 3
I (2010) LAB_HANDSHAKE_IP: [FORENSIC]: Entering Phase 4: 4-Way EAPOL Key Exchange...
I (2020) LAB_HANDSHAKE_IP: =======================================================
I (2020) wifi:<ba-add>idx:0 (ifx:0, 4e:c2:e8:ad:4e:37), tid:0, ssn:1, winSize:64
I (2050) wifi:dp: 2, bi: 102400, li: 4, scale listen interval from 307200 us to 409600 us
I (2050) wifi:AP's beacon interval = 102400 us, DTIM period = 2
I (3030) esp_netif_handlers: sta ip: 10.65.224.169, mask: 255.255.255.0, gw: 10.65.224.40
I (3030) LAB_HANDSHAKE_IP: =======================================================
I (3030) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!
I (3040) LAB_HANDSHAKE_IP:   [SUCCESS]: Phase 4 (4-Way Handshake) & Phase 5 (DHCP IP) COMPLETED!
I (3050) LAB_HANDSHAKE_IP:   -> Allocated IP Address : 10.65.224.169
I (3050) LAB_HANDSHAKE_IP:   -> Subnet Mask          : 255.255.255.0
I (3060) LAB_HANDSHAKE_IP:   -> Default Gateway      : 10.65.224.40
I (3060) LAB_HANDSHAKE_IP: =======================================================
I (3070) LAB_HANDSHAKE_IP: [RESULT]: TEST PASSED - 4-Way Handshake & DHCP IP Assignment Successful!
I (5080) LAB_HANDSHAKE_IP: 

I (5080) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (5080) LAB_HANDSHAKE_IP: >>> Experiment 5.4.2: Handshake Test - Incorrect Password
I (5080) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (5090) LAB_HANDSHAKE_IP:   Target SSID    : "eem_Luna"
I (5100) LAB_HANDSHAKE_IP:   Target Password: "WRONG_PASSWORD_1234"
I (5100) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_stop()
I (5110) wifi:state: run -> init (0x0)
I (5120) wifi:pm stop, total sleep time: 2176102 us / 3148580 us

I (5120) wifi:<ba-del>idx:0, tid:0
I (5120) wifi:new:<1,0>, old:<1,0>, ap:<255,255>, sta:<1,0>, prof:1, snd_ch_cfg:0x0
W (5130) LAB_HANDSHAKE_IP: =======================================================
W (5130) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (5140) LAB_HANDSHAKE_IP:   -> Target SSID          : eem_Luna
W (5150) LAB_HANDSHAKE_IP:   -> Reason Code (Decimal): 8
W (5150) LAB_HANDSHAKE_IP:   -> Reason Code (Hex)    : 0x08
W (5160) LAB_HANDSHAKE_IP:   -> Reason Diagnosis     : OTHER_DISCONNECT_REASON
W (5160) LAB_HANDSHAKE_IP: =======================================================
I (5170) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (5180) wifi:flush txq
I (5180) wifi:stop sw txq
I (5180) wifi:lmac stop hw txq
I (5190) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (5240) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (5240) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_start()
I (5240) wifi:mode : sta (88:57:21:ad:64:98)
I (5240) wifi:enable tsf
I (5250) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (5250) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (5260) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_connect()
I (5270) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (5270) wifi:new:<1,0>, old:<1,0>, ap:<255,255>, sta:<1,0>, prof:1, snd_ch_cfg:0x0
I (5280) wifi:state: init -> auth (0xb0)
W (5280) LAB_HANDSHAKE_IP: [RESULT]: TEST FAILED - Disconnected during Handshake or Auth.
I (5780) LAB_HANDSHAKE_IP: ==================================================================
I (5780) LAB_HANDSHAKE_IP:   [Phase 4 & Phase 5 Completed: Wi-Fi Handshake & IP Lab Finished]
I (5790) LAB_HANDSHAKE_IP: ==================================================================
I (6200) main_task: Returned from app_main()
I (6300) wifi:state: auth -> init (0x600)
I (6370) wifi:new:<1,0>, old:<1,0>, ap:<255,255>, sta:<1,0>, prof:1, snd_ch_cfg:0x0
W (6380) LAB_HANDSHAKE_IP: =======================================================
W (6380) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (6390) LAB_HANDSHAKE_IP:   -> Target SSID          : eem_Luna
W (6390) LAB_HANDSHAKE_IP:   -> Reason Code (Decimal): 202
W (6400) LAB_HANDSHAKE_IP:   -> Reason Code (Hex)    : 0xCA
W (6400) LAB_HANDSHAKE_IP:   -> Reason Diagnosis     : WIFI_REASON_AUTH_FAIL (1/202)
W (6410) LAB_HANDSHAKE_IP: =======================================================
```
## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองใน Handshake & IP Phase

| ข้อการทดลอง | สถานการณ์ทดสอบ   | Event `WIFI_EVENT_STA_CONNECTED` (เกิด/ไม่เกิด) | Event `IP_EVENT_STA_GOT_IP` (เกิด/ไม่เกิด) | ผลการทดลอง | Disconnect Reason Code (ถ้ามี)         |
| :---------: | :--------------- | :---------------------------------------------: | :----------------------------------------: | :--------: | :------------------------------------- |
|  **5.4.1**  | Password ถูกต้อง |                      เกิด                       |                    เกิด                    |   Passed   | -                                      |
|  **5.4.2**  | Password ผิด     |                     ไม่เกิด                     |    ไม่เกิด_(หลุดในชั้น Handshake/Auth)_    |   Failed   | `202 / 0xCA` (`WIFI_REASON_AUTH_FAIL`) |

### 6.2 บันทึกข้อมูล IP Network จาก Event `IP_EVENT_STA_GOT_IP` (ข้อ 5.4.1)

| พารามิเตอร์ Network Layer | ค่าที่จัดสรรได้จริงจาก DHCP Server |
| :------------------------ | :--------------------------------- |
| **IP Address**            | 10.65.224.169                      |
| **Subnet Mask**           | 255.255.255.0                      |
| **Default Gateway**       | 10.65.224.40                       |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดกระบวนการ **4-Way Handshake** จึงพิสูจน์ทราบรหัสผ่าน Wi-Fi ได้โดยไม่ต้องส่งรหัสผ่าน (Passphrase) ลอยไปในอากาศเลยแม้แต่แพ็กเกจเดียว?
		Ans
		ทั้งสองฝั่ง (AP และ Station) จะนำ Passphrase + SSID ไปคำนวณล่วงหน้าแยกกันเองผ่านฟังก์ชัน Hash (PBKDF2) ได้เป็นคีย์ลับเรียกว่า **PMF/PMK**
		ในกระบวนการ 4-Way Handshake จะส่งเพียงค่าสุ่ม (ANonce, SNonce) และรหัสตรวจสอบความถูกต้องของข้อความ (MIC - Message Integrity Code) ลอยผ่านอากาศไปมา หากคำนวณ MIC ออกมาแล้วตรงกันทั้งสองฝ่าย จะเป็นการพิสูจน์ได้ทันทีว่าใช้ Passphrase เดียวกันโดยไม่ต้องส่ง Passphrase จริงผ่านอากาศ
2. อธิบายบทบาทและที่มาของคีย์ **PMK (Pairwise Master Key)** และ **PTK (Pairwise Transient Key)** ว่ามีความสัมพันธ์กันอย่างไรในการเข้ารหัสเฟรมข้อมูล?
		Ans
		- **PMK:** เกิดจาก Passphrase + SSID ซึ่งเป็นคีย์หลักแบบคงที่
	    - **PTK:** เกิดจากการนำ **PMK** + ค่าสุ่ม **ANonce** (จาก AP) + **SNonce** (จาก Station) + **MAC Address** ของทั้งสองฝั่ง มาประมวลผลเข้ารหัสร่วมกัน เพื่อสร้างเป็นคีย์ชั่วคราว (PTK) นำไปใช้เข้ารหัส/ถอดรหัสแพ็กเกจข้อมูลจริงในการสื่อสารของ Session นั้นๆ
3. เหตุใดเมื่อเราพิมพ์ Password ผิด (ข้อ 5.4.2) ESP32 จึงยังคงได้รับ Event **`WIFI_EVENT_STA_CONNECTED`** ก่อนที่จะเกิด Event **`WIFI_EVENT_STA_DISCONNECTED`** ตามมาในภายหลัง?
		Ans
		เพราะ Event `CONNECTED` หมายถึงการผ่าน **Phase 2 (Auth) & Phase 3 (Association)** ในระดับ 802.11 Link Layer เรียบร้อยแล้ว (ตัวรับ-ส่งคลื่นวิทยุจับคู่กันสำเร็จ)
		แต่ความผิดพลาดของ Password จะไปตรวจพบใน **Phase 4 (4-Way Handshake)** ที่มีการแลกเปลี่ยนคีย์ PTK/MIC หากคำนวณ MIC ไม่ตรงกัน AP จะปฏิเสธการถอดรหัสและส่งสัญญาณตัดการเชื่อมต่อทันที ทำให้เกิด Event `DISCONNECTED` ตามมาทีหลัง
4. หากเครือข่าย Wi-Fi ไม่มี DHCP Server (ไม่มีการแจก IP อัตโนมัติ) ผลการทดลองในข้อ 5.4.1 จะหยุดอยู่ที่ขั้นตอนใด และจะไม่เกิด Event ใดขึ้น?
		Ans
		- **ขั้นตอนที่หยุด:** จะผ่าน Phase 4 (4-Way Handshake) แต่จะไปค้างอยู่ที่ **Phase 5 (IP Assignment Phase)**
	    - **Event ที่จะไม่เกิดขึ้น:** จะไม่เกิด Event **`IP_EVENT_STA_GOT_IP`** (ส่งผลให้ระบบค้างรอจนกว่าจะ Timeout)
