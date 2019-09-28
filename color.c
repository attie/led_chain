#include "color.h"
#include "chain.h"

inline void color_tx(enum state_color color) {
	/* blue */
	if ((color == COL_BLUE) || (color == COL_CYAN) || (color == COL_MAGENTA) || (color == COL_WHITE)) {
		CHAIN_DATA_1();
	} else {
		CHAIN_DATA_0();
	}

	/* green */
	if ((color == COL_GREEN) || (color == COL_YELLOW) || (color == COL_CYAN) || (color == COL_WHITE)) {
		CHAIN_DATA_1();
	} else {
		CHAIN_DATA_0();
	}

	/* red */
	if ((color == COL_RED) || (color == COL_YELLOW) || (color == COL_MAGENTA) || (color == COL_WHITE)) {
		CHAIN_DATA_1();
	} else {
		CHAIN_DATA_0();
	}
}

inline void color_inc(enum state_color *color) {
	if (*color >= COL_WHITE) {
		*color = COL_OFF;
	} else {
		*color += 1;
	}
}
