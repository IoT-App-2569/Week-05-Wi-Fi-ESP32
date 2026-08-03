
ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองทั้ง 3 สถานการณ์

| ข้อการทดลอง | สถานการณ์ทดสอบ                     |    Event สุดท้ายที่ได้รับ    |           ผลลัพธ์ (Passed/Failed)           | Reason Code (Decimal / Hex) | คำอธิบาย Reason Code                                                 |
| :---------: | :--------------------------------- | :--------------------------: | :-----------------------------------------: | :-------------------------: | :------------------------------------------------------------------- |
|  **5.2.1**  | SSID และ Password ถูกต้อง          | IP_EVENT_STA_GOT_IP received | TEST PASSED - Connected to AP successfully! |                             |                                                                      |
|  **5.2.2**  | ระบุ SSID ผิด (ไม่มีในระบบ)        | WIFI_EVENT_STA_DISCONNECTED  | TEST FAILED - Disconnected event captured.  |            0xC9             | คือWIFI_REASON_NO_AP_FOUND เกิดจากหา SSID ไม่เจอ เเล้ว STA ยกเลิกเอง |
|  **5.2.3**  | ระบุ SSID ถูกต้อง แต่ Password ผิด | WIFI_EVENT_STA_DISCONNECTED  | TEST FAILED - Disconnected event captured.  |            0x02             | SSID ถูกต้อง แต่รหัสผ่านผิด → 4-way handshake ล้มเหลว                |

### 6.2 บันทึกข้อมูลเครือข่ายจากการเชื่อมต่อสำเร็จ (ข้อ 5.2.1)

| พารามิเตอร์เครือข่าย    | ค่าที่ได้รับจริงจาก DHCP |
| :---------------------- | :----------------------- |
| **SSID**                | hello_world              |
| **BSSID (MAC Address)** | 96:44:8A:D9:7E:63        |
| **Channel**             | 6                        |
| **IP Address**          | 172.20.10.2              |
| **Subnet Mask**         | 255.255.255.240          |
| **Default Gateway**     | 172.20.10.1              |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการระบุ SSID ผิด (ข้อ 5.2.2) จึงส่งผลให้เกิด Disconnect Event ด้วย Reason Code `201` (`WIFI_REASON_NO_AP_FOUND`) ตั้งแต่เฟส Scan?
   ```
   เมื่อเรียก esp_wifi_connect() ไดรเวอร์ต้องสแกนก่อน เพื่อหา AP ที่ broadcast SSID ตรงกับที่ตั้งค่าไว้ ถ้าไม่มี AP ไหน broadcast SSID นั้นเลย ก็ไม่มีเป้าหมายให้ส่งเฟรม Authentication ต่อจึงหยุดตั้งแต่ชั้น Scan และไดรเวอร์แจ้ง disconnect ด้วย reason ไม่พบ AP
   ```
2. เหตุใดการพิมพ์ Password ผิด (ข้อ 5.2.3) จึงผ่านเฟส Auth และ Assoc มาได้ แต่มาล้มเหลวในเฟส 4-Way Handshake (Reason Code `15` หรือ `204`)?
   ```
   WPA2-PSK ใช้ Open System Authentication ในขั้น Auth ซึ่งเป็นเพียงการแลกเฟรมรับรู้กันเฉยๆ ไม่มีการตรวจสอบรหัสผ่านเลย จึงผ่านได้ ตามด้วย Association ที่เป็นการตกลง capability การเชื่อมต่อ ก็ยังไม่เกี่ยวกับ PSK จุดที่รหัสผ่านถูกใช้จริงคือ 4-Way Handshake ทั้งสองฝ่ายต้องคำนวณ PMK จาก PSK แล้วแลก Nonce สร้าง PTK และตรวจสอบ MIC ถ้ารหัสผ่านผิด PMK/PTK จะไม่ตรงกัน MIC ตรวจไม่ผ่าน handshake ล้มเหลว ทำให้ reason 204 หรือ 15 ตามทฤษฎี เเต่ในทางปฏิบัติ log ที่ได้จริงมักเป็น reason 2 AUTH_EXPIRE เพราะขึ้นกับพฤติกรรมของ AP ว่า active-reject หรือ silent-timeout
   ```
3. ลำดับการเกิด Event ระหว่าง **`WIFI_EVENT_STA_CONNECTED`** กับ **`IP_EVENT_STA_GOT_IP`** Event ใดเกิดขึ้นก่อนกัน และมีความหมายทางกายภาพของ Layer Network ต่างกันอย่างไร?
   ```
   WIFI_EVENT_STA_CONNECTED เกิดก่อนอยู่ใน Layer 2  Association + 4-Way Handshake เสร็จสมบูรณ์ มีMAC แล้ว แต่ยังไม่มี IP เเล้วตามด้วยIP_EVENT_STA_GOT_IP อยู่ Layer 3 DHCP Client ขอและได้รับ IP Netmask Gateway จาก DHCP Server แล้ว
   ```
4. สมาชิกตัวแปร `reason` ในโครงสร้าง `wifi_event_sta_disconnected_t` มีประโยชน์อย่างไรต่อการออกแบบระบบค้นหาสาเหตุและกู้คืนการเชื่อมต่อ (Auto-Reconnection Mechanism) ในแอปพลิเคชัน IoT?
   ```
   reason ทำให้ระบบ IoT ออกแบบ recovery strategy แบบ context-aware แทนที่จะ retry เหมือนกันทุกกรณี
	- NO_AP_FOUND 201 ปัญหา config  SSID ผิด ไม่ควร retry ถี่ ควร backoff นานหรือแจ้งเตือนตรวจ config
	- AUTH_FAIL หรือ 4WAY_HANDSHAKE_TIMEOUT ปัญหา รหัสผ่านผิด หยุด retry ด้วยรหัสเดิม เข้าโหมด provisioning ใหม่ให้ผู้ใช้กรอกรหัสผ่าน
	- BEACON_TIMEOUT สัญญาณอ่อน เหมาะกับ exponential backoff เพราะมีโอกาสเชื่อมกลับได้เอง
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
I (80) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1a694h (108180) map
I (126) esp_image: segment 1: paddr=0002a6bc vaddr=3ffb0000 size=045a8h ( 17832) load
I (134) esp_image: segment 2: paddr=0002ec6c vaddr=40080000 size=013ach (  5036) load
I (136) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=857a0h (546720) map
I (333) esp_image: segment 4: paddr=000b57c8 vaddr=400813ac size=14260h ( 82528) load
I (366) esp_image: segment 5: paddr=000c9a30 vaddr=50000000 size=00028h (    40) load
I (377) boot: Loaded app from partition at offset 0x10000
I (378) boot: Disabling RNG early entropy source...
I (388) cpu_start: Multicore app
I (396) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (397) cpu_start: Pro cpu start user code
I (397) cpu_start: cpu freq: 160000000 Hz
I (398) app_init: Application information:
I (402) app_init: Project name:     lab_2
I (406) app_init: App version:      1
I (409) app_init: Compile time:     Aug  3 2026 11:07:49
I (414) app_init: ELF file SHA256:  5d0cb34ab...
I (419) app_init: ESP-IDF:          v6.1-dev-3480-g44c77cbf46
I (424) efuse_init: Min chip rev:     v0.0
I (428) efuse_init: Max chip rev:     v3.99
I (432) efuse_init: Chip rev:         v3.1
I (436) heap_init: Initializing. RAM available for dynamic allocation:
I (442) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (447) heap_init: At 3FFB8A98 len 00027568 (157 KiB): DRAM
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
I (549) LAB_WIFI_CONN: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbded4
I (559) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_init(&cfg)
I (579) wifi:wifi driver task: 3ffc05b0, prio:23, stack:6656, core=0
I (599) wifi:wifi firmware version: 5d0a58b
I (599) wifi:wifi certification version: v7.0
I (599) wifi:config NVS flash: enabled
I (599) wifi:config nano formatting: disabled
I (609) wifi:Init data frame dynamic rx buffer num: 32
I (609) wifi:Init static rx mgmt buffer num: 5
I (609) wifi:Init management short buffer num: 32
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
I (869) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(0)
I (969) wifi:mode : sta (8c:94:df:45:93:e4)
I (969) wifi:enable tsf
I (969) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (969) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (969) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (979) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (989) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (1269) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
I (1269) wifi:state: init -> auth (0xb0)
I (1279) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (1279) wifi:state: auth -> assoc (0x0)
I (1299) wifi:state: assoc -> run (0x10)
I (1429) wifi:connected with hello_world, aid = 3, channel 6, BW20, bssid = 96:44:8a:d9:7e:63
I (1429) wifi:security: WPA2-PSK, phy: bgn, rssi: -53, cipher(pairwise:0x3, group:0x3), pmf:0
I (1439) wifi:pm start, type: 1

I (1439) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (1449) LAB_WIFI_CONN: =======================================================
I (1449) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (1459) LAB_WIFI_CONN:   -> Connected to SSID : hello_world
I (1459) LAB_WIFI_CONN:   -> BSSID            : 96:44:8A:D9:7E:63
I (1469) LAB_WIFI_CONN:   -> Channel          : 6
I (1469) LAB_WIFI_CONN:   -> Auth Mode        : 3
I (1479) LAB_WIFI_CONN: =======================================================
I (1509) wifi:AP's beacon interval = 102400 us, DTIM period = 1
I (2529) esp_netif_handlers: sta ip: 172.20.10.2, mask: 255.255.255.240, gw: 172.20.10.1
I (2529) LAB_WIFI_CONN: =======================================================
I (2529) LAB_WIFI_CONN: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!
I (2539) LAB_WIFI_CONN:   -> IP Address : 172.20.10.2
I (2539) LAB_WIFI_CONN:   -> Netmask    : 255.255.255.240
I (2549) LAB_WIFI_CONN:   -> Gateway    : 172.20.10.1
I (2549) LAB_WIFI_CONN: =======================================================
I (2559) LAB_WIFI_CONN: [RESULT]: TEST PASSED - Connected to AP successfully!
I (4569) wifi:state: run -> init (0x0)
I (4579) wifi:pm stop, total sleep time: 1875812 us / 3137139 us

I (4579) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
I (4579) LAB_WIFI_CONN: [FORENSIC]: Teardown disconnect confirmed (reason 8) - not a test result
I (5589) LAB_WIFI_CONN:

I (5589) LAB_WIFI_CONN: ------------------------------------------------------------------
I (5589) LAB_WIFI_CONN: >>> Experiment 5.2.2: Connection Test - Wrong SSID (No AP Found)
I (5589) LAB_WIFI_CONN: ------------------------------------------------------------------
I (5599) LAB_WIFI_CONN:   Target SSID: "NON_EXISTENT_SSID_9999"
I (5609) LAB_WIFI_CONN:   Target Password: "12345678"
I (5609) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (5619) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (5619) wifi:flush txq
I (5619) wifi:stop sw txq
I (5629) wifi:lmac stop hw txq
I (5629) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (5669) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (5669) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (5669) wifi:mode : sta (8c:94:df:45:93:e4)
I (5669) wifi:enable tsf
I (5669) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (5679) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (5679) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (5689) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (5699) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (8119) LAB_WIFI_CONN: =======================================================
W (8119) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (8119) LAB_WIFI_CONN:   -> Target SSID          : NON_EXISTENT_SSID_9999
W (8129) LAB_WIFI_CONN:   -> Reason Code (Decimal): 201
W (8129) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0xC9
W (8139) LAB_WIFI_CONN:   -> Reason Description   : WIFI_REASON_NO_AP_FOUND (201)
W (8139) LAB_WIFI_CONN: =======================================================
W (8149) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (10159) LAB_WIFI_CONN:

I (10159) LAB_WIFI_CONN: ------------------------------------------------------------------
I (10159) LAB_WIFI_CONN: >>> Experiment 5.2.3: Connection Test - Wrong Password (Auth/Handshake Fail)
I (10159) LAB_WIFI_CONN: ------------------------------------------------------------------
I (10169) LAB_WIFI_CONN:   Target SSID: "hello_world"
I (10179) LAB_WIFI_CONN:   Target Password: "WRONG_PASS_9999"
I (10179) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_stop()
I (10189) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (10189) wifi:flush txq
I (10199) wifi:stop sw txq
I (10199) wifi:lmac stop hw txq
I (10199) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (10249) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (10249) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_start()
I (10249) wifi:mode : sta (8c:94:df:45:93:e4)
I (10249) wifi:enable tsf
I (10259) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (10259) LAB_WIFI_CONN: [FORENSIC]: Call esp_wifi_connect()
I (10269) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (10259) LAB_WIFI_CONN: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (10619) wifi:new:<6,0>, old:<1,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
I (10619) wifi:state: init -> auth (0xb0)
I (10629) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (10629) wifi:state: auth -> assoc (0x0)
I (10639) wifi:state: assoc -> run (0x10)
I (10749) wifi:state: run -> init (0x2c0)
I (10769) wifi:new:<6,0>, old:<6,0>, ap:<255,255>, sta:<6,0>, prof:1, snd_ch_cfg:0x0
W (10769) LAB_WIFI_CONN: =======================================================
W (10769) LAB_WIFI_CONN: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (10779) LAB_WIFI_CONN:   -> Target SSID          : hello_world
W (10779) LAB_WIFI_CONN:   -> Reason Code (Decimal): 2
W (10789) LAB_WIFI_CONN:   -> Reason Code (Hex)    : 0x02
W (10789) LAB_WIFI_CONN:   -> Reason Description   : WIFI_REASON_AUTH_EXPIRE (2)
W (10799) LAB_WIFI_CONN: =======================================================
W (10809) LAB_WIFI_CONN: [RESULT]: TEST FAILED - Disconnected event captured.
I (10809) LAB_WIFI_CONN: ==================================================================
I (10819) LAB_WIFI_CONN:   [Phase 2/3/4/5 Completed: Wi-Fi Connection Lab Finished]
I (10829) LAB_WIFI_CONN: ==================================================================
I (10839) main_task: Returned from app_main()

```
