#include "include/modes.h"

void insert_mode_on_enter(FSM_State *self, const void *arg) {
	// Init data structure
	static IModeData data = {0, 0, 0};	
	if (self->data == NULL) self->data = (void*) &data;

	if (arg != NULL) {
		IModeArg *imArg = (IModeArg*) arg;
		data.line = imArg->line;
		data.page = imArg->page;
		data.column = imArg->column;
	}
}

int insert_mode_update(FSM_State *self, struct timeval *dt) {
	IModeData* this = (IModeData*) self->data;
	switch(getch()) {
		case 'q':
			return -1;
		default:
			break;
	}
	flushinp();

	static int n;

	printw("loop: %d ", ++n);

	return INSERT;
}

void insert_mode_on_exit(FSM_State *self, void **arg) {
	IModeData* this = (IModeData*) self->data;
}
