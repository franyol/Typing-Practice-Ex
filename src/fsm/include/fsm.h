#ifndef _FSM_H_
#define _FSM_H_

#include <stdlib.h>
#include <sys/time.h>

typedef struct FSM_State {
	int id;
	void *data;
	void (*on_enter) (struct FSM_State *self, const void *arg);
	void (*on_exit) (struct FSM_State *self, void **arg);
	int (*update) (struct FSM_State *self, struct timeval *dt);
} FSM_State;

typedef struct FSM {
	FSM_State *states;
	ssize_t len; // states len
	ssize_t current;
} FSM;

void fsm_update(FSM *fsm, struct timeval *dt);

#endif
