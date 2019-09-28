#ifndef CHAIN_H
#define CHAIN_H

#include "nop_delay.h"
#include "gpio.h"

#define CHAIN_PULSE_LOW() \
	{ \
		CHAIN_SET(0); \
		NOP160(); \
	}

#define CHAIN_DATA_0() \
	{ \
		CHAIN_PULSE_LOW(); \
		CHAIN_SET(1); \
		NOP160(); \
		NOP20(); \
		NOP5(); \
	}

#define CHAIN_DATA_1() \
	{ \
		CHAIN_PULSE_LOW(); \
		CHAIN_SET(1); \
		NOP20(); \
	}

#define CHAIN_END() \
	{ \
		CHAIN_SET(0); \
		NOP320(); \
		NOP160(); \
		CHAIN_SET(1); \
	}

#define CHAIN_ADDR_1() \
	{ \
		CHAIN_DATA_0(); \
		CHAIN_DATA_0(); \
		CHAIN_DATA_0(); \
		CHAIN_DATA_0(); \
		CHAIN_DATA_1(); \
	}

#define CHAIN_ADDR_2() \
	{ \
		CHAIN_DATA_0(); \
		CHAIN_DATA_0(); \
		CHAIN_DATA_0(); \
		CHAIN_DATA_1(); \
		CHAIN_DATA_0(); \
	}

#endif /* CHAIN_H */
