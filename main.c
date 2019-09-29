/* simple and disgusting bit-bang control of 2-wire LED chain...
 * 
 * this application will run on an STM32F103 / BluePill board, and
 * is intended to drive the "SK LIGHTSTRING2" product from suck UK.
 *
 * https://www.suck.uk.com/products/multicolour-bottle-string-light/
 *
 * connections:
 *  - Port B, pin 9  - LED chain, via `circuit.png`
 *  - Port C, pin 13 - onboard LED
 */

#include <stdint.h>
#include <stm32f103x6.h>

#include "sysclk.h"
#include "gpio.h"
#include "chain.h"
#include "color.h"

void SystemInit(void) {
	gpio_init();
	sysclk_init();
}

int main(void) {
	uint32_t delay;
	uint32_t i;

	enum state_color color1;
	enum state_color color2;

	color1 = COL_OFF;
	color2 = COL_CYAN;

	for (;;) {
		color_inc(&color1);
		CHAIN_ADDR_1();
		color_tx(color1);
		CHAIN_END();

		for (delay = 0; delay < 0x7f; delay++) {
			asm("nop;");
		}

		color_inc(&color2);
		CHAIN_ADDR_2();
		color_tx(color2);
		CHAIN_END();

		LED_SET(0);

		for (i = 0; i < 0x3fffff; i++) {
			asm("nop;");
		}

		LED_SET(1);
	}
}

void _exit(int _) {
	for(;;);
}

