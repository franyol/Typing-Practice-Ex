#include "include/sections.h"
#include "input.h"
#include <string.h>

enum {
    LOAD_TEXT,
    NEXT_TARGET,
    GET_COMMAND
} state = LOAD_TEXT;

void section_2_on_enter(FSM_State *self, const void *arg) {
}

int section_2_update(FSM_State *self, struct timeval *dt) {
	TextReader *reader = (TextReader*) self->data;

	Command com;
    int c;
    static int target = 0;

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
            //reader->message = "Buffer loaded";

            state = NEXT_TARGET;
            break;
        case NEXT_TARGET:
            reader->writebuff[target] = 'b'; // Clear previous target

            do {
                target = rand() % reader->bytesOnScreen;
            } while (  reader->pagebuff[target] == ' '
                    || reader->pagebuff[target] == '\n'
                    || reader->pagebuff[target] == '\t'
                    || reader->pagebuff[target] == '\r');

            reader->writebuff[target] = 'h'; // Highlight new target

            state = GET_COMMAND;
            break;
        case GET_COMMAND:
            c = input_getKey(&com);

            if (c == 'q') return -1;

            switch (com) {
                case COM_UP:
                    textReader_lineDown(reader, 1);
                    break;
                case COM_DOWN:
                    textReader_lineUp(reader, 1);
                    break;
                case COM_LEFT:
                    reader->writeindex--;
                    reader->cache_column = -1; // Update cache column on next print
                    break;
                case COM_RIGHT:
                    reader->writeindex++;
                    reader->cache_column = -1; // Update cache column on next print
                    break;
                default:
                    break;
            }

            if (reader->writeindex == target) state = NEXT_TARGET;

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
