#ifndef CHAIN_H
#define CHAIN_H

#include "nop_delay.h"
#include "gpio.h"

/* the command's low duration must be ~1.6us */
#define CHAIN_PULSE_LOW() \
	{ \
		CHAIN_SET(0); \
		NOP160(); \
	}

/* the ZERO bit is represented by a ~1.6us low period, followed
 * by a high period of ~3.4us */
#define CHAIN_DATA_0() \
	{ \
		CHAIN_PULSE_LOW(); \
		CHAIN_SET(1); \
		NOP160(); \
		NOP20(); \
		NOP5(); \
	}

/* the ONE bit is represented by a ~1.6us low period, followed
 * by a high period of ~1us */
#define CHAIN_DATA_1() \
	{ \
		CHAIN_PULSE_LOW(); \
		CHAIN_SET(1); \
		NOP20(); \
	}

/* after commands there must be a low period... we don't care
 * too much what this is */
#define CHAIN_END() \
	{ \
		CHAIN_SET(0); \
		NOP320(); \
		NOP160(); \
		CHAIN_SET(1); \
	}

/* ease-of-access macro to transmit address 0x01 */
#define CHAIN_ADDR_1() \
	{ \
		CHAIN_DATA_0(); \
		CHAIN_DATA_0(); \
		CHAIN_DATA_0(); \
		CHAIN_DATA_0(); \
		CHAIN_DATA_1(); \
	}

/* ease-of-access macro to transmit address 0x02 */
#define CHAIN_ADDR_2() \
	{ \
		CHAIN_DATA_0(); \
		CHAIN_DATA_0(); \
		CHAIN_DATA_0(); \
		CHAIN_DATA_1(); \
		CHAIN_DATA_0(); \
	}

#endif /* CHAIN_H */
