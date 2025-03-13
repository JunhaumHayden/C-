/**
 * @file main.c
 * @author risinek (risinek@gmail.com)
 * @date 2021-04-03
 * @copyright Copyright (c) 2021
 * 
 * @brief Main file used to setup ESP32 into initial state
 * 
 * Starts management AP and webserver  
 */

#include <stdio.h>

#define CONFIG_SCAN_MAX_AP 30
#define CONFIG_MGMT_AP_SSID "REDE_INSEGURA"
#define CONFIG_MGMT_AP_PASSWORD "0987654321"
#define CONFIG_MGMT_AP_MAX_CONNECTIONS 5

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"
#include "esp_event.h"

#include "attack.h"
#include "wifi_controller.h"
#include "interface/webserver.h"


#include "nvs_flash.h"

static const char* TAG = "main";



void app_main(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }


    ESP_LOGD(TAG, "app_main started");
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifictl_mgmt_ap_start();
    attack_init();
    webserver_run();
}
