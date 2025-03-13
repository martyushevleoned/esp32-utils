#include "led.h"

Led::Led(gpio_num_t pin) : _pin(pin)
{
    gpio_set_direction(_pin, GPIO_MODE_OUTPUT);
};

esp_err_t Led::set(bool state)
{
    return state ? gpio_set_level(_pin, 1) : gpio_set_level(_pin, 0);
}
