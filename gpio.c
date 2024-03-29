#include <stm32f103x6.h>

#include "gpio.h"

/* initialize the GPIO pins... see README.md */
void gpio_init(void) {
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

	GPIOB->CRH = (GPIOB->CRH & (GPIO_CRH_MODE9 | GPIO_CRH_CNF9))
		| (0x2 << GPIO_CRH_MODE9_Pos) /* 0x2 = Output, < 2MHz */
		| (0x0 << GPIO_CRH_CNF9_Pos); /* 0x0 = General purpose, push-pull */
	GPIOC->CRH = (GPIOC->CRH & (GPIO_CRH_MODE13 | GPIO_CRH_CNF13))
		| (0x2 << GPIO_CRH_MODE13_Pos) /* 0x2 = Output, < 2MHz */
		| (0x0 << GPIO_CRH_CNF13_Pos); /* 0x0 = General purpose, push-pull */

	LED_SET(1);
	CHAIN_SET(0);
}
