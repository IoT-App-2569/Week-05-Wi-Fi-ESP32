/*
 * Lab 5.2: Wi-Fi STA Connection & DHCP IP Assignment
 * Student: นางสาวสุวิมล ศรีประไหม (Suwimon Sripramai) | ID: 67030249 | Table: 1
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

static const char *TAG = "LAB_WIFI_CONN";

static EventGroupHandle_t s_wifi_event_group;
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

// Personalized target Hotspot credentials for Suwimon Sripramai
#define EXAMPLE_ESP_WIFI_SSID      "Suwimon Sripramaip"
#define EXAMPLE_ESP_WIFI_PASS      "67030249pass"

static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
  if (event_base == WIFI_EVENT) {
    if (event_id == WIFI_EVENT_STA_START) {
      ESP_LOGI(TAG, "[EVENT FORENSIC]: WIFI_EVENT_STA_START received");
      esp_wifi_connect();
    } else if (event_id == WIFI_EVENT_STA_CONNECTED) {
      wifi_event_sta_connected_t *e = (wifi_event_sta_connected_t *)event_data;
      ESP_LOGI(TAG, "[EVENT FORENSIC]: WIFI_EVENT_STA_CONNECTED to %s (Ch: %d, Auth: %d)", e->ssid, e->channel, e->authmode);
    } else if (event_id == WIFI_EVENT_STA_DISCONNECTED) {
      wifi_event_sta_disconnected_t *e = (wifi_event_sta_disconnected_t *)event_data;
      ESP_LOGW(TAG, "[EVENT FORENSIC]: WIFI_EVENT_STA_DISCONNECTED reason=%d (0x%02X)", e->reason, e->reason);
      xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
    }
  } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
    ip_event_got_ip_t *e = (ip_event_got_ip_t *)event_data;
    ESP_LOGI(TAG, "[EVENT FORENSIC]: IP_EVENT_STA_GOT_IP -> IP: " IPSTR, IP2STR(&e->ip_info.ip));
    xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
  }
}

static void test_wifi_connection(const char *test_title, const char *ssid, const char *password) {
  xEventGroupClearBits(s_wifi_event_group, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT);
  ESP_LOGI(TAG, ">>> %s (SSID: %s)", test_title, ssid);

  esp_wifi_stop();
  wifi_config_t wifi_config = {0};
  strncpy((char *)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid));
  strncpy((char *)wifi_config.sta.password, password, sizeof(wifi_config.sta.password));
  esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
  esp_wifi_start();

  EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT, pdFALSE, pdFALSE, pdMS_TO_TICKS(10000));
  if (bits & WIFI_CONNECTED_BIT) {
    ESP_LOGI(TAG, "[RESULT]: TEST PASSED - Connected to AP successfully!");
  } else {
    ESP_LOGW(TAG, "[RESULT]: TEST FAILED - Disconnected event captured.");
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

  // 5.2.1 Success
  test_wifi_connection("Experiment 5.2.1: Correct Credentials", EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
  vTaskDelay(pdMS_TO_TICKS(1500));
  // 5.2.2 Non-existent SSID
  test_wifi_connection("Experiment 5.2.2: Wrong SSID (No AP Found)", "NON_EXISTENT_SSID_9999", "12345678");
  vTaskDelay(pdMS_TO_TICKS(1500));
  // 5.2.3 Wrong Password
  test_wifi_connection("Experiment 5.2.3: Wrong Password (Handshake Fail)", EXAMPLE_ESP_WIFI_SSID, "WRONG_PASS_9999");
}
