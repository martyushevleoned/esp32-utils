#include "wifi_scan.h"

void hardware_init()
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
}

void wifi_init()
{
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

wifi_ap_record_t *wifi_scan_start(uint16_t *ap_count)
{
    ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, true));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(ap_count));
    wifi_ap_record_t *records = malloc(sizeof(wifi_ap_record_t) * *ap_count);
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(ap_count, records));
    return records;
}
