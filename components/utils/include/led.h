#ifndef UTILS_LED_H
#define UTILS_LED_H

#include "driver/gpio.h"

class Led
{
public:
    Led(gpio_num_t pin);

    esp_err_t set(bool state);

private:
    gpio_num_t _pin;
};

#endif