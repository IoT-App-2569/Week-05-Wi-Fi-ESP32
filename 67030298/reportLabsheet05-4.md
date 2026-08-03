# ใบงานที่ 5.4: กระบวนการแลกเปลี่ยนคีย์ความปลอดภัยและการจัดสรรหมายเลข IP Address (4-Way Handshake & IP Assignment Phase)
## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกผลลัพธ์จากการสังเกตใน Serial Console ลงในตารางต่อไปนี้:

### 6.1 ตารางสรุปเปรียบเทียบผลการทดลองใน Handshake & IP Phase

| ข้อการทดลอง | สถานการณ์ทดสอบ | Event `WIFI_EVENT_STA_CONNECTED` (เกิด/ไม่เกิด) | Event `IP_EVENT_STA_GOT_IP` (เกิด/ไม่เกิด) | ผลการทดลอง | Disconnect Reason Code (ถ้ามี) |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **5.4.1** | Password ถูกต้อง | เกิด | เกิด | สำเร็จ (Success) | - |
| **5.4.2** | Password ผิด | เกิด | ไม่เกิด | ล้มเหลว (Failed) | 15 / 0x0F (WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT) |

### 6.2 บันทึกข้อมูล IP Network จาก Event `IP_EVENT_STA_GOT_IP` (ข้อ 5.4.1)

| พารามิเตอร์ Network Layer | ค่าที่จัดสรรได้จริงจาก DHCP Server |
| :--- | :--- |
| **IP Address** | 10.61.229.229 |
| **Subnet Mask** | 255.255.255.0 |
| **Default Gateway** | 10.61.229.63 |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดกระบวนการ **4-Way Handshake** จึงพิสูจน์ทราบรหัสผ่าน Wi-Fi ได้โดยไม่ต้องส่งรหัสผ่าน (Passphrase) ลอยไปในอากาศเลยแม้แต่แพ็กเกจเดียว?
> เพราะใช้การพิสูจน์ทราบผ่านการคำนวณค่าแฮช (MIC) หากทั้งสองฝั่งมีรหัสผ่าน (PSK) ตรงกัน ค่า MIC ที่คำนวณได้จะตรงกัน ทำให้ตรวจสอบรหัสผ่านได้โดยไม่ต้องส่งรหัสจริงๆ ผ่านอากาศ

2. อธิบายบทบาทและที่มาของคีย์ **PMK (Pairwise Master Key)** และ **PTK (Pairwise Transient Key)** ว่ามีความสัมพันธ์กันอย่างไรในการเข้ารหัสเฟรมข้อมูล?
> **PMK** ได้มาจากการนำรหัสผ่าน (PSK) ไปคำนวณร่วมกับ SSID เพื่อเป็นคีย์หลัก ส่วน **PTK** ถูกสร้างชั่วคราวต่อเซสชัน โดยคำนวณมาจาก PMK ผสมกับค่าสุ่ม (ANonce, SNonce) และ MAC Address เพื่อใช้เข้ารหัสข้อมูลจริง

3. เหตุใดเมื่อเราพิมพ์ Password ผิด (ข้อ 5.4.2) ESP32 จึงยังคงได้รับ Event **`WIFI_EVENT_STA_CONNECTED`** ก่อนที่จะเกิด Event **`WIFI_EVENT_STA_DISCONNECTED`** ตามมาในภายหลัง?
> เพราะ Event `WIFI_EVENT_STA_CONNECTED` เกิดขึ้นเมื่อจบ Phase 3 (Association) ซึ่ง WPA2 จะรับเข้ามาผูกสัมพันธ์ก่อน (Open System) แล้วไปตกม้าตายตอนตรวจรหัสผ่านใน Phase 4 (Handshake) จึงหลุดในภายหลัง

4. หากเครือข่าย Wi-Fi ไม่มี DHCP Server (ไม่มีการแจก IP อัตโนมัติ) ผลการทดลองในข้อ 5.4.1 จะหยุดอยู่ที่ขั้นตอนใด และจะไม่เกิด Event ใดขึ้น?
> จะหยุดอยู่ที่เฟส 4 (4-Way Handshake สำเร็จ) แต่จะไม่เกิด Event `IP_EVENT_STA_GOT_IP` ในเฟส 5 เพราะไม่สามารถรับหมายเลข IP ได้ ทำให้ส่งผลให้ออกอินเทอร์เน็ตไม่ได้

---

## 8. Log ของการทดลอง (Serial Console Log)
```text
I (27) boot: ESP-IDF v6.0.2-dirty 2nd stage bootloader
I (27) boot: compile time Aug  3 2026 10:53:50
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
I (79) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1a6a8h (108200) map
I (125) esp_image: segment 1: paddr=0002a6d0 vaddr=3ffb0000 size=04528h ( 17704) load
I (132) esp_image: segment 2: paddr=0002ec00 vaddr=40080000 size=01418h (  5144) load
I (135) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=86310h (549648) map
I (332) esp_image: segment 4: paddr=000b6338 vaddr=40081418 size=141f0h ( 82416) load
I (367) esp_image: segment 5: paddr=000ca530 vaddr=50000000 size=00028h (    40) load
I (378) boot: Loaded app from partition at offset 0x10000
I (378) boot: Disabling RNG early entropy source...
I (388) cpu_start: Multicore app
I (396) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (397) cpu_start: Pro cpu start user code
I (397) cpu_start: cpu freq: 160000000 Hz
I (399) app_init: Application information:
I (402) app_init: Project name:     04-Labsheet-05-4
I (407) app_init: App version:      f9372cb-dirty
I (411) app_init: Compile time:     Aug  3 2026 10:52:36
I (416) app_init: ELF file SHA256:  4d918693a...
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
I (490) LAB_HANDSHAKE_IP: [FORENSIC]: Call nvs_flash_init()
I (520) LAB_HANDSHAKE_IP: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (520) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_netif_init()
I (520) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_loop_create_default()
I (530) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (540) LAB_HANDSHAKE_IP: [FORENSIC]: esp_netif_create_default_wifi_sta() returned 0x3ffbddbc
I (540) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_init(&cfg)
I (560) wifi:wifi driver task: 3ffc04a8, prio:23, stack:6656, core=0
I (570) wifi:wifi firmware version: 00ad238
I (570) wifi:wifi certification version: v7.0
I (570) wifi:config NVS flash: enabled
I (570) wifi:config nano formatting: disabled
I (580) wifi:Init data frame dynamic rx buffer num: 32
I (580) wifi:Init static rx mgmt buffer num: 5
I (590) wifi:Init management short buffer num: 32
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
I (630) wifi_init: tcp mss: 1440
I (630) wifi_init: WiFi IRAM OP enabled
I (630) wifi_init: WiFi RX IRAM OP enabled
I (640) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (640) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_event_handler_instance_register(IP_EVENT)
I (650) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (660) LAB_HANDSHAKE_IP: ==================================================================
I (670) LAB_HANDSHAKE_IP:   Lab 5.4: 4-Way Handshake & IP Assignment Phase (ESP-IDF Forensic)
I (680) LAB_HANDSHAKE_IP: ==================================================================
I (680) LAB_HANDSHAKE_IP:

I (690) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (690) LAB_HANDSHAKE_IP: >>> Experiment 5.4.1: Handshake & IP Test - Correct Password
I (700) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (710) LAB_HANDSHAKE_IP:   Target SSID    : "Redmi Note 10S"
I (720) LAB_HANDSHAKE_IP:   Target Password: "3832538325zzz"
I (720) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_stop()
I (730) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (730) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (740) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_start()
I (750) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06
I (840) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(0)
I (860) wifi:mode : sta (84:1f:e8:39:bd:64)
I (860) wifi:enable tsf
I (860) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (860) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (860) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (870) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_connect()
I (880) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (900) wifi:new:<5,0>, old:<1,0>, ap:<255,255>, sta:<5,0>, prof:1, snd_ch_cfg:0x0
I (910) wifi:state: init -> auth (0xb0)
I (910) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (940) wifi:state: auth -> assoc (0x0)
I (950) wifi:state: assoc -> run (0x10)
I (990) wifi:connected with Redmi Note 10S, aid = 2, channel 5, BW20, bssid = 66:34:b4:f7:03:8a
I (990) wifi:security: WPA2-PSK, phy: bgn, rssi: -52, cipher(pairwise:0x3, group:0x3), pmf:0
I (1010) wifi:pm start, type: 1

I (1010) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (1010) wifi:dp: 2, bi: 102400, li: 4, scale listen interval from 307200 us to 409600 us
I (1020) wifi:AP's beacon interval = 102400 us, DTIM period = 2
I (1030) LAB_HANDSHAKE_IP: =======================================================
I (1030) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED received!
I (1040) LAB_HANDSHAKE_IP:   -> Phase 2 (Auth) & Phase 3 (Assoc) PASSED
I (1040) LAB_HANDSHAKE_IP:   -> Connected SSID  : Redmi Note 10S
I (1050) LAB_HANDSHAKE_IP:   -> BSSID           : 66:34:B4:F7:03:8A
I (1050) LAB_HANDSHAKE_IP:   -> Channel         : 5
I (1060) LAB_HANDSHAKE_IP:   -> Association ID  : 34680
I (1060) LAB_HANDSHAKE_IP: [FORENSIC]: Entering Phase 4: 4-Way EAPOL Key Exchange...
I (1070) LAB_HANDSHAKE_IP: =======================================================
I (2050) esp_netif_handlers: sta ip: 10.61.229.229, mask: 255.255.255.0, gw: 10.61.229.63
I (2050) LAB_HANDSHAKE_IP: =======================================================
I (2050) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: IP_EVENT_STA_GOT_IP received!
I (2060) LAB_HANDSHAKE_IP:   [SUCCESS]: Phase 4 (4-Way Handshake) & Phase 5 (DHCP IP) COMPLETED!
I (2070) LAB_HANDSHAKE_IP:   -> Allocated IP Address : 10.61.229.229
I (2070) LAB_HANDSHAKE_IP:   -> Subnet Mask          : 255.255.255.0
I (2080) LAB_HANDSHAKE_IP:   -> Default Gateway      : 10.61.229.63
I (2080) LAB_HANDSHAKE_IP: =======================================================
I (2090) LAB_HANDSHAKE_IP: [RESULT]: TEST PASSED - 4-Way Handshake & DHCP IP Assignment Successful!
I (4100) LAB_HANDSHAKE_IP: 

I (4100) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (4100) LAB_HANDSHAKE_IP: >>> Experiment 5.4.2: Handshake Test - Incorrect Password
I (4100) LAB_HANDSHAKE_IP: ------------------------------------------------------------------
I (4110) LAB_HANDSHAKE_IP:   Target SSID    : "Redmi Note 10S"
I (4120) LAB_HANDSHAKE_IP:   Target Password: "WRONG_PASSWORD_1234"
I (4120) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_stop()
I (4130) wifi:state: run -> init (0x0)
I (4140) wifi:pm stop, total sleep time: 2743333 us / 3127900 us

W (4140) LAB_HANDSHAKE_IP: =======================================================
W (4140) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (4150) LAB_HANDSHAKE_IP:   -> Target SSID          : Redmi Note 10S
W (4160) LAB_HANDSHAKE_IP:   -> Reason Code (Decimal): 8
W (4160) LAB_HANDSHAKE_IP:   -> Reason Code (Hex)    : 0x08
W (4170) LAB_HANDSHAKE_IP:   -> Reason Diagnosis     : OTHER_DISCONNECT_REASON
W (4180) LAB_HANDSHAKE_IP: =======================================================
I (4180) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (4200) wifi:flush txq
I (4200) wifi:stop sw txq
I (4200) wifi:lmac stop hw txq
I (4200) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (4250) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (4250) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_start()
I (4250) wifi:mode : sta (84:1f:e8:39:bd:64)
I (4250) wifi:enable tsf
I (4260) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (4260) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (4260) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (4280) LAB_HANDSHAKE_IP: [FORENSIC]: Call esp_wifi_connect()
I (4280) LAB_HANDSHAKE_IP: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (4290) LAB_HANDSHAKE_IP: [RESULT]: TEST FAILED - Disconnected during Handshake or Auth.
I (4300) LAB_HANDSHAKE_IP: ==================================================================
I (4300) LAB_HANDSHAKE_IP:   [Phase 4 & Phase 5 Completed: Wi-Fi Handshake & IP Lab Finished]
I (4310) LAB_HANDSHAKE_IP: ==================================================================
I (4320) main_task: Returned from app_main()
I (4650) wifi:new:<5,0>, old:<1,0>, ap:<255,255>, sta:<5,0>, prof:1, snd_ch_cfg:0x0
I (4650) wifi:state: init -> auth (0xb0)
I (4660) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (4660) wifi:state: auth -> assoc (0x0)
I (4670) wifi:state: assoc -> run (0x10)
I (7680) wifi:state: run -> init (0xf00)
W (7690) LAB_HANDSHAKE_IP: =======================================================
W (7690) LAB_HANDSHAKE_IP: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (7690) LAB_HANDSHAKE_IP:   -> Target SSID          : Redmi Note 10S
W (7700) LAB_HANDSHAKE_IP:   -> Reason Code (Decimal): 15
W (7700) LAB_HANDSHAKE_IP:   -> Reason Code (Hex)    : 0x0F
W (7710) LAB_HANDSHAKE_IP:   -> Reason Diagnosis     : WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT (204) [Phase 4: Wrong Password]
W (7720) LAB_HANDSHAKE_IP: =======================================================
```