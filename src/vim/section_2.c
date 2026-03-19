#include "include/sections.h"
#include "input.h"

enum {
    GET_COMMAND,
    MOVE
} state = GET_COMMAND;

void section_2_on_enter(FSM_State *self, const void *arg) {

}

int section_2_update(FSM_State *self, struct timeval *dt) {

	Command com;
	int c = input_getKey(&com);

	if (c == 'q') return -1;


    // Visual
	clear_win();

	static int h, w;
	getmaxyx(stdscr, h, w);
	mvprintw(h/2, w/2, "About the manuals, press q to quit");

	return SECTION_1;
}

void section_2_on_exit(FSM_State *self, void **arg) {

}
