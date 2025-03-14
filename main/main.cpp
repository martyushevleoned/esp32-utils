#include "led.h"
#include "time.h"

extern "C"
{
#include "wifi_scan.h"
}

#include "esp_log.h"

extern "C" void app_main()
{
    hardware_init();
    wifi_init();
    uint16_t ap_count;
    while (1)
    {
        wifi_ap_record_t *records = wifi_scan_start(&ap_count);
        for (int i = 0; i < ap_count; i++)
            ESP_LOGI("TAG", "SSID: %s, RSSI: %d", records[i].ssid, records[i].rssi);
        free(records);
        delay_seconds(5);
    }
}