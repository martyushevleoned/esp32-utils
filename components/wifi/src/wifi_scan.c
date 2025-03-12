#include <stdio.h>
#include "wifi_scan.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"

#define TAG "WIFI_SCAN"

esp_err_t wifi_scan_init() {
    ESP_LOGI(TAG, "Initializing Wi-Fi...");
    
    // Инициализация NVS (необходима для Wi-Fi)
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Настройка Wi-Fi в режиме STA
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "Wi-Fi initialized successfully");
    return ESP_OK;
}

esp_err_t wifi_scan_start() {
    ESP_LOGI(TAG, "Starting Wi-Fi scan...");

    // Запуск сканирования
    ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, true));

    // Получение количества доступных сетей
    uint16_t ap_count = 0;
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
    if (ap_count == 0) {
        ESP_LOGW(TAG, "No Wi-Fi networks found.");
        return ESP_OK;
    }

    // Получение данных о найденных сетях
    wifi_ap_record_t ap_info[ap_count];
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_count, ap_info));

    // Вывод информации о найденных сетях
    ESP_LOGI(TAG, "Found %d Wi-Fi networks:", ap_count);
    for (int i = 0; i < ap_count; i++) {
        ESP_LOGI(TAG, "SSID: %s, RSSI: %d, Channel: %d",
                 ap_info[i].ssid, ap_info[i].rssi, ap_info[i].primary);
    }

    return ESP_OK;
}
