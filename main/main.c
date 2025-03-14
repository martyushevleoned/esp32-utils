#include "bluetooth.h"

void app_main()
{
    bluetooth_sniffer_init(bluetooth_sniffer_default_callback_handler);
}