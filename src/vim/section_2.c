#include "include/sections.h"
#include "input.h"
#include <string.h>

enum {
    LOAD_TEXT,
    NEXT_TARGET,
    GET_COMMAND,
    MOVE
} state = LOAD_TEXT;

void section_2_on_enter(FSM_State *self, const void *arg) {
}

int section_2_update(FSM_State *self, struct timeval *dt) {
	TextReader *reader = (TextReader*) self->data;

	Command com;
	int c = input_getKey(&com);

	if (c == 'q') return -1;

    static int fd = -1;

    switch (state) {
        case LOAD_TEXT:
            fd = open_random_file(TEXT_DIR);

            if (fd == -1) {
                perror("open_random_file, check TEXT_DIR definition");
                return -1;
            }

            reader->fd = fd;
            textReader_fillBuffer(reader);
            reader->message = "Buffer loaded";

            state = NEXT_TARGET;
            break;
        case NEXT_TARGET:
            break;
        case GET_COMMAND:
            break;
        case MOVE:
            break;
        default:
            break;
    }


    // Visual
	clear_win();

	getmaxyx(stdscr, reader->h, reader->w);
    if (strcmp(reader->message, "")) {
        reader->h = reader->h * 0.7;
    }

    textReader_print(reader);

	return SECTION_2;
}

void section_2_on_exit(FSM_State *self, void **arg) {

}
