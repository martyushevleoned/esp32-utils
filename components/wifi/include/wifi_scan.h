#ifndef WIFI_SCAN_H
#define WIFI_SCAN_H

#include "esp_wifi.h"
#include "nvs_flash.h"
#include <vector>

void hardware_init();

void wifi_init();

std::vector<wifi_ap_record_t> wifi_scan_start();

#endif