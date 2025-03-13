#include "led.h"
#include "time.h"

extern "C" void app_main()
{
    Led led(GPIO_NUM_8);
    while (1)
    {
        led.set(0);
        delay_seconds(1);
        led.set(1);
        delay_seconds(1);
    }
}