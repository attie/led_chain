#include "color.h"
#include "chain.h"

/* this function will transmit the Blue, Green and Red fields of the
 * command, based on the color value provided */
inline void color_tx(enum state_color color) {
	/* blue */
	if ((color == COL_BLUE) || (color == COL_CYAN) || (color == COL_MAGENTA)) {
		CHAIN_DATA_1();
	} else {
		CHAIN_DATA_0();
	}

	/* green */
	if ((color == COL_GREEN) || (color == COL_YELLOW) || (color == COL_CYAN)) {
		CHAIN_DATA_1();
	} else {
		CHAIN_DATA_0();
	}

	/* red */
	if ((color == COL_RED) || (color == COL_YELLOW) || (color == COL_MAGENTA)) {
		CHAIN_DATA_1();
	} else {
		CHAIN_DATA_0();
	}
}

/* this function will roll the color value through the enum's options */
inline void color_inc(enum state_color *color) {
	*color += 1;
	if (*color == COL_EOL) {
		*color = 0;
	}
}
