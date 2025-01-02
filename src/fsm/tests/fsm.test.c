#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "../include/fsm.h"

int end;

typedef struct TestData {
	int value;
} TestData;

void s0_on_enter(FSM_State* self, const void *arg) {
	printf("entering state %d\n", self->id);
}

void s0_on_exit(FSM_State* self, void **arg) {
	TestData* data;

	data = (TestData*) malloc(sizeof(TestData));
	data->value = 35;
	*arg = (void*) data;

	printf("exiting state %d\n", self->id);
}

int s0_update(FSM_State* self, struct timeval *dt) {
	printf("Updating state %d, now go to 1\n", self->id);
	return 1;
}

void s1_on_enter(FSM_State *self, const void *arg) {
	TestData* data;

	printf("entering state 1\n");

	if (arg != NULL) {
		data = (TestData*) arg;
		self->data = data;
		printf("received data: %d\n", data->value);
	}
}

void s1_on_exit(FSM_State *self, void **arg) {
	printf("exiting state %d\n", self->id);
}

int s1_update(FSM_State *self, struct timeval *dt) {
	TestData* data;

	if (self->data != NULL) {
		data = (TestData*) self->data;
		printf("remembering data %d\n", data->value);
	}

	printf("Updating state %d, now end\n", self->id);
	end = 1;
	return 1;
}

void test_fsm(void) {
	FSM_State s0 = {0, NULL, s0_on_enter, s0_on_exit, s0_update};
	FSM_State s1 = {1, NULL, s1_on_enter, s1_on_exit, s1_update};

	FSM_State states[2] = {s0, s1};
	FSM fsm = {states, 2, -1};

	end = 0;
	while (end == 0) {
		fsm_update(&fsm, NULL);
	}
}

int main() {
	test_fsm();
	printf("test_fsm: OK\n");

	printf("all tests passed\n");
	exit(EXIT_SUCCESS);
}

