#ifndef COLOR_H
#define COLOR_H

enum state_color {
	COL_OFF,     /* red green blue */
	COL_RED,     /*  1    0    0   */
	COL_GREEN,   /*  0    1    0   */
	COL_BLUE,    /*  0    0    1   */
	COL_YELLOW,  /*  1    1    0   */
	COL_CYAN,    /*  0    1    1   */
	COL_MAGENTA, /*  1    0    1   */
	COL_WHITE,   /*  1    1    1   */
};

void color_tx(enum state_color color);
void color_inc(enum state_color *color);

#endif /* COLOR_H */
