/*
 * Lab 5.1: Wi-Fi Connection and Scanning Phase
 * Student: นายสุวิจักขณ์ ลาวัง (Suwijak Lawang) | ID: 67030248 | Table: 1
 * Board: ESP32-D0WD-V3 (MAC: 84:1F:E8:39:81:70)
 */
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include <stdio.h>
#include <string.h>

static const char *TAG = "LAB_WIFI_SCAN";

static const char *get_auth_mode_name(wifi_auth_mode_t authmode) {
  switch (authmode) {
  case WIFI_AUTH_OPEN: return "OPEN (No Password)";
  case WIFI_AUTH_WEP: return "WEP";
  case WIFI_AUTH_WPA_PSK: return "WPA_PSK";
  case WIFI_AUTH_WPA2_PSK: return "WPA2_PSK";
  case WIFI_AUTH_WPA_WPA2_PSK: return "WPA_WPA2_PSK";
  case WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2_ENTERPRISE";
  case WIFI_AUTH_WPA3_PSK: return "WPA3_PSK";
  case WIFI_AUTH_WPA2_WPA3_PSK: return "WPA2_WPA3_PSK";
  default: return "UNKNOWN";
  }
}

static void perform_wifi_scan(wifi_scan_config_t *scan_config, const char *test_title, char *found_first_ssid, size_t max_ssid_len) {
  ESP_LOGI(TAG, "------------------------------------------------------------------");
  ESP_LOGI(TAG, ">>> %s", test_title);
  ESP_LOGI(TAG, "------------------------------------------------------------------");

  ESP_LOGI(TAG, "[FORENSIC]: Call esp_wifi_scan_start(scan_config, block=true)");
  int64_t start_time = esp_timer_get_time();
  esp_err_t err = esp_wifi_scan_start(scan_config, true);
  int64_t duration_ms = (esp_timer_get_time() - start_time) / 1000;
  ESP_LOGI(TAG, "[FORENSIC]: esp_wifi_scan_start() returned %s (0x%x) [Duration: %lld ms]", esp_err_to_name(err), err, duration_ms);

  if (err != ESP_OK) return;

  uint16_t ap_count = 0;
  esp_wifi_scan_get_ap_num(&ap_count);
  ESP_LOGI(TAG, "[STATUS]: Scan SUCCESS, [AP COUNT]: %u network(s) found", ap_count);

  if (ap_count > 0) {
    wifi_ap_record_t *ap_info = (wifi_ap_record_t *)malloc(sizeof(wifi_ap_record_t) * ap_count);
    uint16_t number = ap_count;
    esp_wifi_scan_get_ap_records(&number, ap_info);

    printf("\n%-4s | %-24s | %-17s | %-6s | %-4s | %-20s\n", "No.", "SSID", "MAC Address (BSSID)", "RSSI", "Chan", "Encryption Type");
    printf("--------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < number; i++) {
      char bssid_str[18];
      snprintf(bssid_str, sizeof(bssid_str), "%02X:%02X:%02X:%02X:%02X:%02X",
               ap_info[i].bssid[0], ap_info[i].bssid[1], ap_info[i].bssid[2],
               ap_info[i].bssid[3], ap_info[i].bssid[4], ap_info[i].bssid[5]);
      printf("%-4d | %-24s | %-17s | %-4d dBm | %-4d | %-20s\n", i + 1,
             strlen((char *)ap_info[i].ssid) > 0 ? (char *)ap_info[i].ssid : "<Hidden>",
             bssid_str, ap_info[i].rssi, ap_info[i].primary, get_auth_mode_name(ap_info[i].authmode));
    }
    printf("--------------------------------------------------------------------------------------------------\n");
    free(ap_info);
  }
}

void app_main(void) {
  nvs_flash_init();
  esp_netif_init();
  esp_event_loop_create_default();
  esp_netif_create_default_wifi_sta();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&cfg);
  esp_wifi_set_mode(WIFI_MODE_STA);
  esp_wifi_start();

  ESP_LOGI(TAG, "Lab 5.1 Wi-Fi Scan - Station: %s", "Suwijak Lawangp");
  wifi_scan_config_t scan_all = {.channel = 0, .show_hidden = true, .scan_type = WIFI_SCAN_TYPE_ACTIVE};
  perform_wifi_scan(&scan_all, "Experiment 5.1.1: General AP Scan (All Channels)", NULL, 0);

  wifi_scan_config_t scan_ch1 = {.channel = 1, .show_hidden = true, .scan_type = WIFI_SCAN_TYPE_ACTIVE};
  perform_wifi_scan(&scan_ch1, "Experiment 5.1.2: Channel-Specific Scan (Channel 1)", NULL, 0);

  wifi_scan_config_t scan_target = {.ssid = (uint8_t *)"Suwijak Lawangp", .channel = 0, .show_hidden = true};
  perform_wifi_scan(&scan_target, "Experiment 5.1.3: Targeted SSID Scan - Existing (\"Suwijak Lawangp\")", NULL, 0);

  wifi_scan_config_t scan_dummy = {.ssid = (uint8_t *)"NON_EXISTENT_AP_9999", .channel = 0, .show_hidden = true};
  perform_wifi_scan(&scan_dummy, "Experiment 5.1.4: Targeted SSID Scan - Non-Existent", NULL, 0);
}
