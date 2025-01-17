#include "include/modes.h"
#include "input.h"
#include "draw_utils.h"
#include <unistd.h>

int lines_between(char *buf, int start, int end);

void insert_mode_on_enter(FSM_State *self, const void *arg) {
	IModeData* this = (IModeData*) self->data;

	// Read cursor position
	// if (arg != NULL) {
	// }

	// Read first chunk on file start
	if ( this->reader->bytesRead == 0 && this->reader->page == 0 ) {
		textReader_fillBuffer(this->reader);
	}
}

int insert_mode_update(FSM_State *self, struct timeval *dt) {
	IModeData* this = (IModeData*) self->data;
	TextReader* reader = this->reader;
	
	Command com;
	int c = input_getKey(&com);

	if (com == COM_NORMAL_MODE) {
		return -1;
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

	textReader_putChar(reader, c);
	// Print the buffer into screen
	textReader_print(reader);

	return INSERT;
}

void insert_mode_on_exit(FSM_State *self, void **arg) {
	//IModeData* this = (IModeData*) self->data;
}

