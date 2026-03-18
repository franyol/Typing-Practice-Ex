#include "include/sections.h"
#include "input.h"

void section_1_on_enter(FSM_State *self, const void *arg) {

}

int section_1_update(FSM_State *self, struct timeval *dt) {

	Command com;
	int c = input_getKey(&com);

	if (c == 'q') return -1;

	clear_win();

	static int h, w;
	getmaxyx(stdscr, h, w);
	mvprintw(h/2, w/2, "Section 1, press q to quit");

	return SECTION_1;
}

void section_1_on_exit(FSM_State *self, void **arg) {

}
