#ifndef _DRAW_UTILS_H_
#define _DRAW_UTILS_H_

#include <ncurses.h>

typedef enum Color {
	BLACK,
	RED,
	BLUE,
	YELLOW,
	GREEN,
	CURSOR
} Color;

void init_colors();

void clear_win(void);

#endif
