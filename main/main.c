#include "wifi_scan.h"
#include "utils.h"

void app_main()
{
    ESP_ERROR_CHECK(wifi_scan_init());
    while (1)
    {
        wifi_scan_start();
        delay(5000);
    }
}