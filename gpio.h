#ifndef GPIO_H
#define GPIO_H

#include <stm32f103x6.h>

#define PIN_SET_ACTIVE_HIGH(port, pin, enable) (port)->BSRR = 0x1 << ( (pin) + ((enable) ? 0 : 16) )
#define PIN_SET_ACTIVE_LOW(port, pin, enable)  PIN_SET_ACTIVE_HIGH(port, pin, !(enable))

#define LED_SET(on)     PIN_SET_ACTIVE_LOW(GPIOC, 13, on)
#define CHAIN_SET(high) PIN_SET_ACTIVE_LOW(GPIOB,  9, high)

void gpio_init(void);

#endif /* GPIO_H */
