#include "include/modes.h"
#include "input.h"
#include "draw_utils.h"
#include <unistd.h>

int lines_between(char *buf, int start, int end);

void normal_mode_on_enter(FSM_State *self, const void *arg) {
	//IModeData* this = (IModeData*) self->data;
}

int normal_mode_update(FSM_State *self, struct timeval *dt) {
	IModeData* this = (IModeData*) self->data;
	TextReader* reader = this->reader;
	
	Command com;
	input_getKey(&com);

	if (com == COM_INSERT_MODE) {
		return INSERT;
	}

	clear_win();

	if (textReader_isBufferEnd(reader)) {
		if (textReader_isPageEnd(reader)) {
			textReader_pageUp(reader);
		} else {
			return -1;
		}
	}

	getmaxyx(stdscr, reader->h, reader->w);

	switch (com) {
		case COM_UP:
			textReader_lineDown(reader, 1);
			break;
		case COM_DOWN:
			textReader_lineUp(reader, 1);
			break;
		case COM_LEFT:
			reader->writeindex--;
			break;
		case COM_RIGHT:
			reader->writeindex++;
			break;
		default:
			break;
	}

	// Print the buffer into screen
	textReader_print(reader);

	//mvprintw(0, 0, "com: %s ", (com == COM_UNUSED) ? "unused" : "used" );
	//mvprintw(0, 0, "col: %d ", reader->column );

	return NORMAL;
}

void normal_mode_on_exit(FSM_State *self, void **arg) {
	//IModeData* this = (IModeData*) self->data;
}

