
## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองใน Handshake & IP Phase

| ข้อการทดลอง | สถานการณ์ทดสอบ   | Event `WIFI_EVENT_STA_CONNECTED` (เกิด/ไม่เกิด) | Event `IP_EVENT_STA_GOT_IP` (เกิด/ไม่เกิด) |                           ผลการทดลอง                           | Disconnect Reason Code (ถ้ามี) |
| :---------: | :--------------- | :---------------------------------------------: | :----------------------------------------: | :------------------------------------------------------------: | :----------------------------- |
|  **5.4.1**  | Password ถูกต้อง |            WIFI_EVENT_STA_CONNECTED             |                    เกิด                    | TEST PASSED - 4-Way Handshake & DHCP IP Assignment Successful! |                                |
|  **5.4.2**  | Password ผิด     |           WIFI_EVENT_STA_DISCONNECTED           |                  ไม่เกิด                   |                          TEST FAILED                           | 0x02 WIFI_REASON_AUTH_EXPIRE   |

### 6.2 บันทึกข้อมูล IP Network จาก Event `IP_EVENT_STA_GOT_IP` (ข้อ 5.4.1)

| พารามิเตอร์ Network Layer | ค่าที่จัดสรรได้จริงจาก DHCP Server |
| :------------------------ | :--------------------------------- |
| **IP Address**            | 172.20.10.2                        |
| **Subnet Mask**           | 255.255.255.240                    |
| **Default Gateway**       |  172.20.10.1                       |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดกระบวนการ **4-Way Handshake** จึงพิสูจน์ทราบรหัสผ่าน Wi-Fi ได้โดยไม่ต้องส่งรหัสผ่าน (Passphrase) ลอยไปในอากาศเลยแม้แต่แพ็กเกจเดียว?
	```
	AP และ Client คำนวณ PMK จาก Passphrase+SSID เก็บไว้ในเครื่องตัวเองอยู่แล้ว ไม่เคยส่ง PMK หรือรหัสผ่านออกไป สิ่งที่ส่งผ่านอากาศจริงมีแค่ ANonce/SNonce  และค่า MIC ที่คำนวณจาก PTK เท่านั้น ทั้งสองฝ่ายนำ Nonce ที่แลกกันไปคำนวณ PTK และสร้าง MIC แล้วเทียบกัน ถ้ารหัสผ่านตรงกัน MIC จะตรงกันทันที  หากรหัสผ่านผิด PMK/PTK จะต่างกัน ทำให้ MIC ไม่ตรงและ Handshake ล้มเหลว โดยไม่ต้องเปิดเผยรหัสผ่านเลย
	```
2. อธิบายบทบาทและที่มาของคีย์ **PMK (Pairwise Master Key)** และ **PTK (Pairwise Transient Key)** ว่ามีความสัมพันธ์กันอย่างไรในการเข้ารหัสเฟรมข้อมูล?
```
PMK (Pairwise Master Key)
	- ที่มา คำนวณจาก PBKDF2 จะมี Passphrase เเละ SSID ทั้ง AP และ Client คำนวณแยกกันในเครื่องตัวเอง ไม่เคยส่งผ่านอากาศ
	- หน้าที่ เป็นคีย์หลักระยะยาว คงที่จนกว่าจะเปลี่ยนรหัสผ่าน ใช้เป็นวัตถุดิบตั้งต้นสำหรับสร้าง PTK
PTK (Pairwise Transient Key)
	- ที่มา คำนวณจาก PRF จะมี PMK ANonce SNonce AP_MAC เเบะ STA_MAC ระหว่างทำ 4-Way Handshake โดยใช้ Nonce สุ่มใหม่ที่แลกกันในแต่ละครั้ง
	- หน้าที่ แบ่งเป็น 3 ส่วน
		— KCK ใช้เซ็น/ตรวจ MIC ยืนยันตัวตน
		- KEK ใช้เข้ารหัส GTK ที่ส่งมาในเฟรมที่ 3 
		- TK ใช้เข้ารหัส/ถอดรหัสข้อมูลจริงหลัง Handshake สำเร็จ
ความสัมพันธ์ PMK เป็นกุญแจที่ทั้งสองฝ่ายรู้ร่วมกันโดยไม่ต้องเปิดเผย ส่วน PTK คือกุญแจใช้งานชั่วคราวที่สร้างจาก PMK ผสมกับข้อมูลสุ่มเฉพาะ session ทำให้ PTK ไม่ซ้ำกันในแต่ละครั้งที่เชื่อมต่อ แม้ PMK เดิมจะไม่เปลี่ยน ป้องกัน Replay Attack และแยกความปลอดภัยของแต่ละ session ออกจากกัน
```
3. เหตุใดเมื่อเราพิมพ์ Password ผิด (ข้อ 5.4.2) ESP32 จึงยังคงได้รับ Event **`WIFI_EVENT_STA_CONNECTED`** ก่อนที่จะเกิด Event **`WIFI_EVENT_STA_DISCONNECTED`** ตามมาในภายหลัง?
```
Event WIFI_EVENT_STA_CONNECTED เกิดขึ้นทันทีที่ Layer 2 Authentication และ Association สำเร็จตามมาตรฐาน 802.11 เป็นแค่การขอเข้าร่วมเครือข่ายระดับเฟรม ยังไม่มีการตรวจสอบรหัสผ่าน WPA2-PSK ใดๆ ทั้งสิ้น การตรวจรหัสผ่านจริงเกิดใน Phase 4 คือ 4-Way EAPOL Handshake ซึ่งเริ่มทำงานหลังจาก Associate สำเร็จแล้ว เมื่อ MIC ไม่ตรงกันเพราะรหัสผ่านผิด Handshake จึง timeout และเกิด DISCONNECTED ตามมาทีหลัง
```
4. หากเครือข่าย Wi-Fi ไม่มี DHCP Server (ไม่มีการแจก IP อัตโนมัติ) ผลการทดลองในข้อ 5.4.1 จะหยุดอยู่ที่ขั้นตอนใด และจะไม่เกิด Event ใดขึ้น?
```
4-Way Handshake เป็นกระบวนการระดับ Layer 2 ที่ไม่เกี่ยวกับ DHCP จึงผ่าน Phase 1ถุง4 ได้ตามปกติ Event WIFI_EVENT_STA_CONNECTED จะยังคงเกิดขึ้นเหมือนเดิม เพราะ Associate สำเร็จแล้วในระดับ 802.11 จากนั้นส่ง DHCP DISCOVER แต่ไม่มี Server ตอบ OFFER กลับมา ทำให้ค้างรออยู่ที่ขั้น DHCP Client เเล้ว Event IP_EVENT_STA_GOT_IP จะไม่เกิดขึ้นเลย และโปรแกรมจะไม่แสดงผล TEST PASSED
```

### Log

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
I (27) boot: compile time Aug  4 2026 02:59:22
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
I (80) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1a684h (108164) map
I (126) esp_image: segment 1: paddr=0002a6ac vaddr=3ffb0000 size=045a8h ( 17832) load
I (134) esp_image: segment 2: paddr=0002ec5c vaddr=40080000 size=013bch (  5052) load
I (136) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=85690h (546448) map
I (332) esp_image: segment 4: paddr=000b56b8 vaddr=400813bc size=14250h ( 82512) load
I (366) esp_image: segment 5: paddr=000c9910 vaddr=50000000 size=00028h (    40) load
I (377) boot: Loaded app from partition at offset 0x10000
I (377) boot: Disabling RNG early entropy source...
I (388) cpu_start: Multicore app
I (396) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (396) cpu_start: Pro cpu start user code
I (396) cpu_start: cpu freq: 160000000 Hz
I (398) app_init: Application information:
I (402) app_init: Project name:     lab_4
I (406) app_init: App version:      1
I (409) app_init: Compile time:     Aug  4 2026 02:57:29
I (414) app_init: ELF file SHA256:  24a20afbb...
I (419) app_init: ESP-IDF:          v6.1-dev-3480-g44c77cbf46
I (424) efuse_init: Min chip rev:     v0.0
I (428) efuse_init: Max chip rev:     v3.99
I (432) efuse_init: Chip rev:         v3.1
I (436) heap_init: Initializing. RAM available for dynamic allocation:
I (442) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (447) heap_init: At 3FFB8A90 len 00027570 (157 KiB): DRAM
I (452) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (458) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (463) heap_init: At 4009560C len 0000A9F4 (42 KiB): IRAM
I (470) spi_flash: detected chip: generic
I (472) spi_flash: flash io: dio
W (475) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (489) main_task: Started on CPU0
I (499) main_task: Calling app_main()
I (499) LAB_HANDSHAKE_IP: [FORENSIC]: Call nvs_flash_init()
I (539) LAB_HANDSHAKE_IP: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (539) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_netif_init()
I (539) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_loop_create_default()
I (549) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (559) LAB_HANDSHAKE_IP: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbddc4
I (559) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_init(&cfg)
I (579) wifi:wifi driver task: 3ffc04a0, prio:23, stack:6656, core=0
I (599) wifi:wifi firmware version: 5d0a58b
I (599) wifi:wifi certification version: v7.0
I (599) wifi:config NVS flash: enabled
I (599) wifi:config nano formatting: disabled
I (609) wifi:Init data frame dynamic rx buffer num: 32
I (609) wifi:Init static rx mgmt buffer num: 5
I (619) wifi:Init management short buffer num: 32
I (619) wifi:Init dynamic tx buffer num: 32
I (619) wifi:Init static rx buffer size: 1600
I (629) wifi:Init static rx buffer num: 10
I (629) wifi:Init dynamic rx buffer num: 32
I (639) wifi_init: rx ba win: 6
I (639) wifi_init: accept mbox: 6
I (639) wifi_init: tcpip mbox: 32
I (649) wifi_init: udp mbox: 6
I (649) wifi_init: tcp mbox: 6
I (649) wifi_init: tcp tx win: 5760
I (649) wifi_init: tcp rx win: 5760
I (659) wifi_init: tcp mss: 1440
I (659) wifi_init: WiFi IRAM OP enabled
I (659) wifi_init: WiFi RX IRAM OP enabled
I (669) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (679) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_handler_instance_register(IP_EVENT)
I (679) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (689) LAB_HANDSHAKE_IP: ==================================================================
I (699) LAB_HANDSHAKE_IP:   Lab 5.4: 4-Way Handshake & IP Assignment Phase (ESP-IDF Forensic)
I (709) LAB_HANDSHAKE_IP: ==================================================================
I (709) LAB_HANDSHAKE_IP:

I (719) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (729) LAB_HANDSHAKE_IP: >>> Experiment 5.4.1: Handshake & IP Test - Correct Password
I (729) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (739) LAB_HANDSHAKE_IP:   Target SSID    : "hello_world"
I (749) LAB_HANDSHAKE_IP:   Target Password: "qwertyuiop"
I (749) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_stop()
I (759) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (789) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (789) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_start()
I (789) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06
I (889) wifi:mode : sta (8c:94:df:45:93:e4)
I (889) wifi:enable tsf
I (889) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (889) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (889) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (899) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_connect()
I (909) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (1229) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
I (1229) wifi:state: init -> auth (0xb0)
I (1239) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (1239) wifi:state: auth -> assoc (0x0)
I (1259) wifi:state: assoc -> run (0x10)
I (1299) wifi:connected with hello_world, aid = 3, channel 6, BW20, bssid = 96:44:8a:d9:7e:63
I (1299) wifi:security: WPA2-PSK, phy: bgn, rssi: -39, cipher(pairwise:0x3, group:0x3), pmf:0
I (1309) wifi:pm start, type: 1

I (1309) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (1319) LAB_HANDSHAKE_IP: =======================================================
I (1319) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (1329) LAB_HANDSHAKE_IP:   -> Phase 2 (Auth) & Phase 3 (Assoc) PASSED
I (1329) LAB_HANDSHAKE_IP:   -> Connected SSID  : hello_world
I (1339) LAB_HANDSHAKE_IP:   -> BSSID           : 96:44:8A:D9:7E:63
I (1349) LAB_HANDSHAKE_IP:   -> Channel         : 6
I (1349) LAB_HANDSHAKE_IP:   -> Association ID  : 34756
I (1359) LAB_HANDSHAKE_IP: [FORENSIC]: Entering Phase 4: 4-Way EAPOL Key Exchange...
I (1359) LAB_HANDSHAKE_IP: =======================================================
I (1329) wifi:AP's beacon interval = 102400 us, DTIM period = 1
I (2389) esp_netif_handlers: sta ip: 172.20.10.2, mask: 255.255.255.240, gw: 172.20.10.1
I (2389) LAB_HANDSHAKE_IP: =======================================================
I (2389) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!
I (2399) LAB_HANDSHAKE_IP:   [SUCCESS]: Phase 4 (4-Way Handshake) & Phase 5 (DHCP IP) COMPLETED!
I (2409) LAB_HANDSHAKE_IP:   -> Allocated IP Address : 172.20.10.2
I (2409) LAB_HANDSHAKE_IP:   -> Subnet Mask          : 255.255.255.240
I (2419) LAB_HANDSHAKE_IP:   -> Default Gateway      : 172.20.10.1
I (2419) LAB_HANDSHAKE_IP: =======================================================
I (2429) LAB_HANDSHAKE_IP: [RESULT]: TEST PASSED - 4-Way Handshake & DHCP IP Assignment Successful!
I (4439) LAB_HANDSHAKE_IP:

I (4439) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (4439) LAB_HANDSHAKE_IP: >>> Experiment 5.4.2: Handshake Test - Incorrect Password
I (4439) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (4449) LAB_HANDSHAKE_IP:   Target SSID    : "hello_world"
I (4459) LAB_HANDSHAKE_IP:   Target Password: "WRONG_PASSWORD_1234"
I (4459) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_stop()
I (4469) wifi:state: run -> init (0x0)
I (4479) wifi:pm stop, total sleep time: 1572723 us / 3167209 us

I (4479) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
W (4489) LAB_HANDSHAKE_IP: =======================================================
W (4489) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (4499) LAB_HANDSHAKE_IP:   -> Target SSID          : hello_world
W (4499) LAB_HANDSHAKE_IP:   -> Reason Code (Decimal): 8
W (4509) LAB_HANDSHAKE_IP:   -> Reason Code (Hex)    : 0x08
W (4519) LAB_HANDSHAKE_IP:   -> Reason Diagnosis     : OTHER_DISCONNECT_REASON
W (4519) LAB_HANDSHAKE_IP: =======================================================
I (4529) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (4539) wifi:flush txq
I (4539) wifi:stop sw txq
I (4539) wifi:lmac stop hw txq
I (4539) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (4569) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (4569) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_start()
I (4579) wifi:mode : sta (8c:94:df:45:93:e4)
I (4579) wifi:enable tsf
I (4579) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (4589) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (4589) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (4599) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_connect()
I (4609) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (4609) LAB_HANDSHAKE_IP: [RESULT]: TEST FAILED - Disconnected during Handshake or Auth.
I (4869) LAB_HANDSHAKE_IP: ==================================================================
I (4879) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
I (4879) wifi:state: init -> auth (0xb0)
I (4889) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (4889) LAB_HANDSHAKE_IP:   [Phase 4 & Phase 5 Completed: Wi-Fi Handshake & IP Lab Finished]
I (4899) wifi:state: auth -> assoc (0x0)
I (4909) LAB_HANDSHAKE_IP: ==================================================================
I (4909) main_task: Returned from app_main()
I (4909) wifi:state: assoc -> run (0x10)
I (4939) wifi:state: run -> init (0x2c0)
I (4959) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
W (4959) LAB_HANDSHAKE_IP: =======================================================
W (4959) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (4969) LAB_HANDSHAKE_IP:   -> Target SSID          : hello_world
W (4969) LAB_HANDSHAKE_IP:   -> Reason Code (Decimal): 2
W (4979) LAB_HANDSHAKE_IP:   -> Reason Code (Hex)    : 0x02
W (4979) LAB_HANDSHAKE_IP:   -> Reason Diagnosis     : WIFI_REASON_AUTH_EXPIRE (2)
W (4989) LAB_HANDSHAKE_IP: =======================================================

```