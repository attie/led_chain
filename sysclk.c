#include <stdint.h>
#include <stm32f103x6.h>

void sysclk_init(void) {
	/* step 0: increase flash access latency before increasing core speed
	 *         one wait state for 24 MHz < SYSCLK <= 48 MHz */
	FLASH->ACR = (FLASH->ACR & ~(FLASH_ACR_LATENCY))
		| FLASH_ACR_LATENCY_0;

	/* step 1: enable and wait for the High-Speed External clock
	 *         this is an 8 MHz resonator */
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY));

	/* step 2: configure the scaler, and enable / wait for it
	 *         PLLXTPRE = /1
	 *         PLLSRC   = HSE
	 *         PLLMUL   = x9
	 *         output   = 8 MHz / 1 * 9 = 72 MHz */
	RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL))
		| RCC_CFGR_PLLMULL9
		| RCC_CFGR_PLLSRC; /* Use HSE */
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY));

	/* step 3: configure the AHB, APB1, APB2 and ADC scalers
	 *         AHB  output = 72 MHz / 1 = 72 MHz
	 *         APB1 output = 72 MHz / 2 = 36 MHz
	 *         APB2 output = 72 MHz / 1 = 72 MHz
	 *         ADC  output = 72 MHz / 6 = 12 MHz */
	RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_PPRE2 | RCC_CFGR_PPRE1 | RCC_CFGR_HPRE | RCC_CFGR_ADCPRE))
		| RCC_CFGR_PPRE2_DIV1
		| RCC_CFGR_PPRE1_DIV2
		| RCC_CFGR_HPRE_DIV1
		| RCC_CFGR_ADCPRE_DIV6;
	RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_SW))
		| (1 << RCC_CFGR_SW_Pos); /* HSE */

	/* step 4: set the system clock to PLL, and wait for it to take effect */
	RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_SW))
		| RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}
