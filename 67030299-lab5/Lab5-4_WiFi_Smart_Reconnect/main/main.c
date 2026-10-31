/*
 * Lab 5.4: 4-Way Handshake & Smart Reconnection
 * Student: นางสาวธนพร พิศมัย (Thanaporn Pitsamai) | ID: 67030299 | Table: 2
 */
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"

static const char *TAG = "LAB_HANDSHAKE_IP";
static EventGroupHandle_t s_wifi_event_group;
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

#define TARGET_WIFI_SSID   "Thanaporn Pitsamaip"
#define TARGET_WIFI_PASS   "67030299pass"

static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
  if (event_base == WIFI_EVENT) {
    if (event_id == WIFI_EVENT_STA_START) {
      esp_wifi_connect();
    } else if (event_id == WIFI_EVENT_STA_CONNECTED) {
      wifi_event_sta_connected_t *e = (wifi_event_sta_connected_t *)event_data;
      ESP_LOGI(TAG, "[EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED - AID=%d, SSID=%s", e->aid, e->ssid);
      ESP_LOGI(TAG, "[FORENSIC]: Entering Phase 4: 4-Way EAPOL Key Exchange...");
    } else if (event_id == WIFI_EVENT_STA_DISCONNECTED) {
      wifi_event_sta_disconnected_t *e = (wifi_event_sta_disconnected_t *)event_data;
      ESP_LOGW(TAG, "[EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED - Reason=%d (0x%02X)", e->reason, e->reason);
      xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
    }
  } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
    ip_event_got_ip_t *e = (ip_event_got_ip_t *)event_data;
    ESP_LOGI(TAG, "[SUCCESS]: Phase 4 Handshake & Phase 5 DHCP COMPLETED -> IP: " IPSTR, IP2STR(&e->ip_info.ip));
    xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
  }
}

void app_main(void) {
  s_wifi_event_group = xEventGroupCreate();
  nvs_flash_init();
  esp_netif_init();
  esp_event_loop_create_default();
  esp_netif_create_default_wifi_sta();

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&cfg);
  esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL);
  esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, NULL);
  esp_wifi_set_mode(WIFI_MODE_STA);

  wifi_config_t wifi_cfg = {0};
  strncpy((char *)wifi_cfg.sta.ssid, TARGET_WIFI_SSID, sizeof(wifi_cfg.sta.ssid));
  strncpy((char *)wifi_cfg.sta.password, TARGET_WIFI_PASS, sizeof(wifi_cfg.sta.password));
  esp_wifi_set_config(WIFI_IF_STA, &wifi_cfg);
  esp_wifi_start();

  xEventGroupWaitBits(s_wifi_event_group, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT, pdFALSE, pdFALSE, pdMS_TO_TICKS(10000));
}
