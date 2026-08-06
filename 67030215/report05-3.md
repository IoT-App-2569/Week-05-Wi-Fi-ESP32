
rst:0x1 (POWERON_ 2MB
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (ets Jul 29 2019 12:21:46

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
I (134) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=860f4h (549108) map
I (323) esp_image: segment 4: paddr=000b611c vaddr=400822b4 size=15b58h ( 88920) load
I (358) esp_image: segment 5: paddr=000cbc7c vaddr=50000000 size=00020h (    32) load
I (370) boot: Loaded app from partition at offset 0x10000
I (370) boot: Disabling RNG early entropy source...
I (381) cpu_start: Multicore app
I (389) cpu_start: Pro cpu start user code
I (389) cpu_start: cpu freq: 160000000 Hz
I (389) app_init: Application information:
I (389) app_init: Project name:     LED_Blink
I (393) app_init: App version:      1
I (396) app_init: Compile time:     Aug  6 2026 10:54:55
I (402) app_init: ELF file SHA256:  e3ab40d61...
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
I (484) LAB_AUTH_ASSOC: [FORENSIC]: Call nvs_flash_init()
I (504) LAB_AUTH_ASSOC: [FORENSIC]: nvs_flash_init() returned ESP_OK (0x0)
I (504) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_netif_init()
I (504) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_event_loop_create_default()
I (504) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
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
I (684) LAB_AUTH_ASSOC:   Target SSID    : "MY_SSID"
I (684) LAB_AUTH_ASSOC:   Target Password: "MY_PASSWORD"
I (694) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_stop()
I (694) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
W (704) wifi:Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2
I (754) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (754) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_start()
I (754) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
W (764) phy_init: failed to load RF calibration data (0xffffffff), falling back to full calibration
I (844) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(2)
I (884) wifi:mode : sta (14:33:5c:0d:cd:7c)
I (884) wifi:enable tsf
I (884) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 43 received
I (884) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
I (894) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (904) LAB_AUTH_ASSOC: [FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...
I (904) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (914) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
W (3324) LAB_AUTH_ASSOC: =======================================================
W (3324) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (3334) LAB_AUTH_ASSOC:   -> Target SSID          : MY_SSID
W (3334) LAB_AUTH_ASSOC:   -> Reason Code (Decimal): 201
W (3344) LAB_AUTH_ASSOC:   -> Reason Code (Hex)    : 0xC9
W (3344) LAB_AUTH_ASSOC:   -> Reason Diagnosis     : WIFI_REASON_NO_AP_FOUND (201) [Phase 1: SSID Not Found]
W (3354) LAB_AUTH_ASSOC: =======================================================
W (3364) LAB_AUTH_ASSOC: [RESULT]: TEST FAILED - Disconnected event captured in Link-Layer.
I (5374) LAB_AUTH_ASSOC: 

I (5374) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (5374) LAB_AUTH_ASSOC: >>> Experiment 5.3.2: Link-Layer Test - Non-Existent AP
I (5374) LAB_AUTH_ASSOC: ------------------------------------------------------------------
I (5384) LAB_AUTH_ASSOC:   Target SSID    : "NON_EXISTENT_AP_9999"
I (5394) LAB_AUTH_ASSOC:   Target Password: "12345678"
I (5394) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_stop()
I (5404) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT ID 3 received
I (5404) wifi:flush txq
I (5404) wifi:stop sw txq
I (5414) wifi:lmac stop hw txq
I (5414) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
W (5424) wifi:Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2
I (5474) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_set_config() returned ESP_OK (0x0)
I (5474) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_start()
I (5484) wifi:mode : sta (14:33:5c:0d:cd:7c)
I (5484) wifi:enable tsf
I (5484) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_START received
I (5494) LAB_AUTH_ASSOC: [FORENSIC]: Initiating 802.11 Link-Layer Connection (Auth & Assoc)...
I (5494) LAB_AUTH_ASSOC: [FORENSIC]: Call esp_wifi_connect()
I (5504) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_connect() returned ESP_OK (0x0)
I (5484) LAB_AUTH_ASSOC: [FORENSIC]: esp_wifi_start() returned ESP_OK (0x0)
W (7914) LAB_AUTH_ASSOC: =======================================================
W (7924) LAB_AUTH_ASSOC: [EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED received!
W (7924) LAB_AUTH_ASSOC:   -> Target SSID          : NON_EXISTENT_AP_9999
W (7924) LAB_AUTH_ASSOC:   -> Reason Code (Decimal): 201
W (7934) LAB_AUTH_ASSOC:   -> Reason Code (Hex)    : 0xC9
W (7934) LAB_AUTH_ASSOC:   -> Reason Diagnosis     : WIFI_REASON_NO_AP_FOUND (201) [Phase 1: SSID Not Found]
W (7944) LAB_AUTH_ASSOC: =======================================================
W (7954) LAB_AUTH_ASSOC: [RESULT]: TEST FAILED - Disconnected event captured in Link-Layer.
I (7964) LAB_AUTH_ASSOC: ==================================================================
I (7974) LAB_AUTH_ASSOC:   [Phase 2 & Phase 3 Completed: Link-Layer Auth & Assoc Finished]
I (7984) LAB_AUTH_ASSOC: ==================================================================
I (7984) main_task: Returned from app_main()

