#include "include/modes.h"
#include "input.h"

void insert_mode_on_enter(FSM_State *self, const void *arg) {
	// Init data structure
	static IModeData data = {0, 0, 0};	
	if (self->data == NULL) self->data = (void*) &data;

	input_init();

	if (arg != NULL) {
		IModeArg *imArg = (IModeArg*) arg;
		data.line = imArg->line;
		data.page = imArg->page;
		data.column = imArg->column;
	}
}

int insert_mode_update(FSM_State *self, struct timeval *dt) {
	IModeData* this = (IModeData*) self->data;
	
	Command com;
	int c = input_getKey(&com);

	if (com == COM_NORMAL_MODE) {
		return -1;
	}
	if (c != ERR) printw("%c", c);

	return INSERT;
}

void insert_mode_on_exit(FSM_State *self, void **arg) {
	IModeData* this = (IModeData*) self->data;
}
