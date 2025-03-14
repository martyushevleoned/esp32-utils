#ifndef WIFI_H
#define WIFI_H

#include "esp_wifi.h"

void wifi_hardware_init();

void wifi_sniffer_init(wifi_promiscuous_cb_t packet_handler);

void wifi_sniffer_default_packet_handler(void *buff, wifi_promiscuous_pkt_type_t type);

void wifi_scan_init();

void wifi_scan_start(uint16_t *ap_count, wifi_ap_record_t *ap_records);

#endif