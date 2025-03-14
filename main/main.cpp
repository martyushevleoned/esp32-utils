#include "led.h"
#include "time.h"
#include "wifi_scan.h"
#include "esp_log.h"

extern "C" void app_main()
{
    Led powerLed(GPIO_NUM_8);
    hardware_init();
    wifi_init();

    while (true)
    {
        std::vector<wifi_ap_record_t> ap_records = wifi_scan_start();
        ESP_LOGI("WIFI NETWORKS COUNT", "%d", ap_records.size());

        for (const wifi_ap_record_t &ap_record : ap_records)
            ESP_LOGI("WIFI PARAMS", "SSID: %s, RSSI: %d", ap_record.ssid, ap_record.rssi);

        powerLed.set(1);
        delay_seconds(5);
        powerLed.set(0);
    }
}