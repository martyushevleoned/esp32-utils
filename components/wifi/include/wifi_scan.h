#ifndef WIFI_SCAN_H
#define WIFI_SCAN_H

#include "wifi.h"
#include <vector>

void wifi_scan_init();

std::vector<wifi_ap_record_t> wifi_scan_start();

#endif