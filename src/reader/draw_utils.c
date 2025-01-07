#include "include/draw_utils.h"

void init_colors() {
	init_pair(BLACK, COLOR_WHITE, COLOR_BLACK);
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(YELLOW, COLOR_WHITE, COLOR_YELLOW);
	init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(CURSOR, COLOR_BLACK, COLOR_WHITE);
}

void clear_win(void) {
	attrset(A_NORMAL | COLOR_PAIR(BLACK));
	int max_x, max_y;
	getmaxyx(stdscr, max_y, max_x);
	for (int i=0; i<max_y; i++) {
		mvprintw(i,0,"%*s", max_x, "");
	}
}
