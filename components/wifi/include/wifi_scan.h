#ifndef WIFI_SCAN_H
#define WIFI_SCAN_H

#include "esp_wifi.h"
#include "nvs_flash.h"

void hardware_init();

void wifi_init();

wifi_ap_record_t *wifi_scan_start(uint16_t *);

#endif