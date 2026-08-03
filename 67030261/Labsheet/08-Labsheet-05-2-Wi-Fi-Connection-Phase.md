
ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองทั้ง 3 สถานการณ์

| ข้อการทดลอง | สถานการณ์ทดสอบ                     |                 Event สุดท้ายที่ได้รับ                  |           ผลลัพธ์ (Passed/Failed)           | Reason Code (Decimal / Hex) | คำอธิบาย Reason Code                                                                                                                                                                                                                      |
| :---------: | :--------------------------------- | :-----------------------------------------------------: | :-----------------------------------------: | :-------------------------: | :---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
|  **5.2.1**  | SSID และ Password ถูกต้อง          |     [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!     | TEST PASSED - Connected to AP successfully! |                             |                                                                                                                                                                                                                                           |
|  **5.2.2**  | ระบุ SSID ผิด (ไม่มีในระบบ)        |              WIFI_EVENT_STA_START received              | TEST FAILED - Disconnected event captured.  |            0x08             | คือ WIFI_REASON_ASSOC_LEAVE คำอธิบาย Disassociated because sending STA is leaving (or has left) BSS เกิด Disassociation ใน Association เฟส 3 เนื่องจากฝั่งใดฝั่งหนึ่ง  กำลังจะออกจากเครือข่าย BSS  นั้นๆ                                  |
|  **5.2.3**  | ระบุ SSID ถูกต้อง แต่ Password ผิด | [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received! | TEST FAILED - Disconnected event captured.  |            0x02             | คือ WIFI_REASON_AUTH_EXPIRE คำอธิบาย Previous authentication no longer valid เกิดการหมดเวลาหรือสิ้นสุดสถานะการยืนยันตัวตนใน Auth Phase เฟสย่อยที่ 2 เนื่องจากไม่ได้รับการตอบรับจาก AP ในเวลาที่กำหนด หรือ Authentication เดิมใช้การไม่ได้ |

### 6.2 บันทึกข้อมูลเครือข่ายจากการเชื่อมต่อสำเร็จ (ข้อ 5.2.1)

| พารามิเตอร์เครือข่าย    | ค่าที่ได้รับจริงจาก DHCP |
| :---------------------- | :----------------------- |
| **SSID**                | hello_world              |
| **BSSID (MAC Address)** | 0A:73:7B:AB:24:DC        |
| **Channel**             | 6                        |
| **IP Address**          | 172.20.10.2              |
| **Subnet Mask**         | 255.255.255.240          |
| **Default Gateway**     | 172.20.10.1              |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการระบุ SSID ผิด (ข้อ 5.2.2) จึงส่งผลให้เกิด Disconnect Event ด้วย Reason Code `201` (`WIFI_REASON_NO_AP_FOUND`) ตั้งแต่เฟส Scan?
2. เหตุใดการพิมพ์ Password ผิด (ข้อ 5.2.3) จึงผ่านเฟส Auth และ Assoc มาได้ แต่มาล้มเหลวในเฟส 4-Way Handshake (Reason Code `15` หรือ `204`)?
3. ลำดับการเกิด Event ระหว่าง **`WIFI_EVENT_STA_CONNECTED`** กับ **`IP_EVENT_STA_GOT_IP`** Event ใดเกิดขึ้นก่อนกัน และมีความหมายทางกายภาพของ Layer Network ต่างกันอย่างไร?
4. สมาชิกตัวแปร `reason` ในโครงสร้าง `wifi_event_sta_disconnected_t` มีประโยชน์อย่างไรต่อการออกแบบระบบค้นหาสาเหตุและกู้คืนการเชื่อมต่อ (Auto-Reconnection Mechanism) ในแอปพลิเคชัน IoT?
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
I (27) boot: compile time Aug  3 2026 11:08:31
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
I (136) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=856a4h (546468) map
I (332) esp_image: segment 4: paddr=000b56cc vaddr=4008145c size=141b0h ( 82352) load
I (366) esp_image: segment 5: paddr=000c9884 vaddr=50000000 size=00028h (    40) load
I (377) boot: Loaded app from partition at offset 0x10000
I (377) boot: Disabling RNG early entropy source...
I (388) cpu_start: Multicore app
I (396) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (396) cpu_start: Pro cpu start user code
I (396) cpu_start: cpu freq: 160000000 Hz
I (398) app_init: Application information:
I (402) app_init: Project name:     lab_2
I (406) app_init: App version:      1
I (409) app_init: Compile time:     Aug  3 2026 11:07:49
I (414) app_init: ELF file SHA256:  c387d6fd0...
I (418) app_init: ESP-IDF:          v6.1-dev-3480-g44c77cbf46
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
I (499) LAB_WIFI_CONN: [FORENSIC]: Call nvs_flash_init()
I (539) LAB_WIFI_CONN: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (539) LAB_WIFI_CONN: [FORENSIC]: Call esp_netif_init()
I (539) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_loop_create_default()
I (549) LAB_WIFI_CONN: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (559) LAB_WIFI_CONN: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbdecc
I (559) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_init(&cfg)
I (579) wifi:wifi driver task: 3ffc05a8, prio:23, stack:6656, core=0
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
I (639) wifi_init: udp mbox: 6
I (649) wifi_init: tcp mbox: 6
I (649) wifi_init: tcp tx win: 5760
I (649) wifi_init: tcp rx win: 5760
I (659) wifi_init: tcp mss: 1440
I (659) wifi_init: WiFi IRAM OP enabled
I (659) wifi_init: WiFi RX IRAM OP enabled
I (669) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (669) LAB_WIFI_CONN: [FORENSIC]: Call esp_event_handler_instance_register(IP_EVENT)
I (679) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (689) LAB_WIFI_CONN: ==================================================================
I (699) LAB_WIFI_CONN:   Lab 5.2: Wi-Fi Connection & IP Assignment (ESP-IDF Forensic)
I (699) LAB_WIFI_CONN: ==================================================================
I (709) LAB_WIFI_CONN:

I (709) LAB_WIFI_CONN: ------------------------------------------------------------------
I (719) LAB_WIFI_CONN: >>> Experiment 5.2.1: Connection Test - Correct Credentials
I (729) LAB_WIFI_CONN: ------------------------------------------------------------------
I (739) LAB_WIFI_CONN:   Target SSID: "hello_world"
I (739) LAB_WIFI_CONN:   Target Password: "qwertyuiop"
I (749) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (749) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (779) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (779) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (779) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06
I (869) wifi:mode : sta (8c:94:df:45:93:e4)
I (869) wifi:enable tsf
I (879) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (879) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (879) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (889) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (899) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (1769) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
I (1769) wifi:state: init -> auth (0xb0)
I (1779) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (1779) wifi:state: auth -> assoc (0x0)
I (1789) wifi:state: assoc -> run (0x10)
I (2549) wifi:connected with hello_world, aid = 1, channel 6, BW20, bssid = 0a:73:7b:ab:24:dc
I (2549) wifi:security: WPA2-PSK, phy: bgn, rssi: -48, cipher(pairwise:0x3, group:0x3), pmf:0
I (2569) wifi:pm start, type: 1

I (2569) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (2569) wifi:AP's beacon interval = 102400 us, DTIM period = 1
I (2579) LAB_WIFI_CONN: =======================================================
I (2579) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (2589) LAB_WIFI_CONN:   -> Connected to SSID : hello_world
I (2599) LAB_WIFI_CONN:   -> BSSID            : 0A:73:7B:AB:24:DC
I (2599) LAB_WIFI_CONN:   -> Channel          : 6
I (2609) LAB_WIFI_CONN:   -> Auth Mode        : 3
I (2609) LAB_WIFI_CONN: =======================================================
I (4719) esp_netif_handlers: sta ip: 172.20.10.2, mask: 255.255.255.240, gw: 172.20.10.1
I (4719) LAB_WIFI_CONN: =======================================================
I (4719) LAB_WIFI_CONN: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!
I (4729) LAB_WIFI_CONN:   -> IP Address : 172.20.10.2
I (4729) LAB_WIFI_CONN:   -> Netmask    : 255.255.255.240
I (4739) LAB_WIFI_CONN:   -> Gateway    : 172.20.10.1
I (4739) LAB_WIFI_CONN: =======================================================
I (4749) LAB_WIFI_CONN: [RESULT]: TEST PASSED - Connected to AP successfully!
I (6759) LAB_WIFI_CONN:

I (6759) LAB_WIFI_CONN: ------------------------------------------------------------------
I (6759) LAB_WIFI_CONN: >>> Experiment 5.2.2: Connection Test - Wrong SSID (No AP Found)
I (6759) LAB_WIFI_CONN: ------------------------------------------------------------------
I (6769) LAB_WIFI_CONN:   Target SSID: "NON_EXISTENT_SSID_9999"
I (6779) LAB_WIFI_CONN:   Target Password: "12345678"
I (6779) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (6789) wifi:state: run -> init (0x0)
I (6799) wifi:pm stop, total sleep time: 2781750 us / 4224606 us

I (6799) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
W (6809) LAB_WIFI_CONN: =======================================================
W (6809) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (6819) LAB_WIFI_CONN:   -> Target SSID          : hello_world
W (6819) LAB_WIFI_CONN:   -> Reason Code (Decimal): 8
W (6829) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0x08
W (6829) LAB_WIFI_CONN:   -> Reason Description   : OTHER_DISCONNECT_REASON
W (6839) LAB_WIFI_CONN: =======================================================
I (6849) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (6849) wifi:flush txq
I (6849) wifi:stop sw txq
I (6859) wifi:lmac stop hw txq
I (6859) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (6899) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (6899) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (6899) wifi:mode : sta (8c:94:df:45:93:e4)
I (6899) wifi:enable tsf
I (6899) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (6909) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (6909) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (6919) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (6929) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (6929) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (8939) LAB_WIFI_CONN:

I (8939) LAB_WIFI_CONN: ------------------------------------------------------------------
I (8939) LAB_WIFI_CONN: >>> Experiment 5.2.3: Connection Test - Wrong Password (Auth/Handshake Fail)
I (8939) LAB_WIFI_CONN: ------------------------------------------------------------------
I (8949) LAB_WIFI_CONN:   Target SSID: "hello_world"
I (8959) LAB_WIFI_CONN:   Target Password: "WRONG_PASS_9999"
I (8959) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (8969) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (8969) wifi:flush txq
I (8969) wifi:stop sw txq
I (8979) wifi:lmac stop hw txq
I (8979) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (9079) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (9079) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (9079) wifi:mode : sta (8c:94:df:45:93:e4)
I (9079) wifi:enable tsf
I (9089) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (9089) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (9099) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (9089) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (9369) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
I (9369) wifi:state: init -> auth (0xb0)
I (9379) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (9379) wifi:state: auth -> assoc (0x0)
I (9389) wifi:state: assoc -> run (0x10)
I (9559) wifi:state: run -> init (0x2c0)
I (9569) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
W (9569) LAB_WIFI_CONN: =======================================================
W (9569) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (9579) LAB_WIFI_CONN:   -> Target SSID          : hello_world
W (9579) LAB_WIFI_CONN:   -> Reason Code (Decimal): 2
W (9589) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0x02
W (9589) LAB_WIFI_CONN:   -> Reason Description   : WIFI_REASON_AUTH_EXPIRE (2)
W (9599) LAB_WIFI_CONN: =======================================================
W (9609) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (9609) LAB_WIFI_CONN: ==================================================================
I (9619) LAB_WIFI_CONN:   [Phase 2/3/4/5 Completed: Wi-Fi Connection Lab Finished]
I (9629) LAB_WIFI_CONN: ==================================================================
I (9639) main_task: Returned from app_main()

```