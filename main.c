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
	uint32_t delay;

	gpio_init();
	sysclk_init();

	/* there must be a period of "high" signal before the first command is issued,
	 * otherwise it will be ignored / mis-interpreted... I'm not sure if this is
	 * because the LEDs require startup current, or (I think more likely), the
	 * start of the command is triggered by a falling edge */
	CHAIN_SET(1);
	for (delay = 0; delay < 0xff; delay++) {
		asm("nop;");
	}
}

static inline void run_led_1(enum state_color *color) {
	CHAIN_ADDR_1();
	color_tx(*color);
	CHAIN_END();

	color_inc(color);
}

static inline void run_led_2(enum state_color *color) {
	CHAIN_ADDR_2();
	color_tx(*color);
	CHAIN_END();

	color_inc(color);
}

int main(void) {
	uint32_t delay;

	enum state_color color1 = COL_RED;
	enum state_color color2 = COL_CYAN;

	run_led_1(&color1);
	run_led_2(&color2);

	for (;;) {
		for (delay = 0; delay < 0x1fffff; delay++) {
			asm("nop;");
		}

		run_led_1(&color1);
		LED_SET(0);

		for (delay = 0; delay < 0x1fffff; delay++) {
			asm("nop;");
		}

		run_led_2(&color2);
		LED_SET(1);
	}
}

void _exit(int _) {
	for(;;);
}

