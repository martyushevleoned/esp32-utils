#include "wifi_scan.h"

void wifi_scan_init()
{
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

std::vector<wifi_ap_record_t> wifi_scan_start()
{
    uint16_t ap_count;
    ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, true));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));

    if (ap_count == 0)
        return {};

    std::vector<wifi_ap_record_t> ap_records(ap_count);
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_count, ap_records.data()));

    ap_records.resize(ap_count);
    return ap_records;
}
