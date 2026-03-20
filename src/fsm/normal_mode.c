#include "include/modes.h"
#include "input.h"
#include "draw_utils.h"
#include <unistd.h>
#include <string.h>

int lines_between(char *buf, int start, int end);

void normal_mode_on_enter(FSM_State *self, const void *arg) {
	//IModeData* this = (IModeData*) self->data;
}

int normal_mode_update(FSM_State *self, struct timeval *dt) {
	IModeData* this = (IModeData*) self->data;
	TextReader* reader = this->reader;

	Command com;
	int c = input_getKey(&com);

	if (com == COM_INSERT_MODE) {
		return INSERT;
	}

	clear_win();

	if (reader->writeindex < 0) {
		textReader_pageDown(reader);
	} else if (textReader_isBufferEnd(reader)) {
		if (textReader_isPageEnd(reader)) {
			textReader_pageUp(reader);
		} else {
			return -1;
		}
	}

	getmaxyx(stdscr, reader->h, reader->w);
    if (strcmp(reader->message, "")) {
        reader->h = reader->h * 0.7;
    }

	// Print the buffer into screen
	textReader_print(reader);

    textReader_normal_mode_key_handler(reader, c, com);

	//mvprintw(0, 0, "com: %s ", (com == COM_UNUSED) ? "unused" : "used" );
	//mvprintw(5, 0, "page: %d wrideindex: %d readerindex: %d, seek: %d", reader->page, reader->writeindex, reader->index, debug );

	return NORMAL;
}

void normal_mode_on_exit(FSM_State *self, void **arg) {
	//IModeData* this = (IModeData*) self->data;
}

