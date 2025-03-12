#ifndef WIFI_SCAN_H
#define WIFI_SCAN_H

#include "esp_err.h"

esp_err_t wifi_scan_init(void);
esp_err_t wifi_scan_start(void);

#endif