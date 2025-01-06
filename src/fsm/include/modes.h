#ifndef _MODES_H_
#define _MODES_H_

#include "fsm.h"
#include <time.h>
#include <ncurses.h>

typedef enum Mode {
	INSERT
} Mode;

typedef enum Color {
	BLACK,
	RED,
	BLUE,
	YELLOW,
	GREEN,
	CURSOR
} Color;

typedef struct IModeData {
	unsigned int page;
	unsigned int line;
	unsigned int column;
	unsigned int index;
	unsigned int writeindex;
	char *pagebuff;
	char *writebuff;
	int fd;
	int buffSize;
	ssize_t bytesRead;
} IModeData;

typedef struct IModeArg {
	unsigned int page;
	unsigned int line;
	unsigned int column;
} IModeArg;

#define DECLARE_STATE(type) \
	void type##_on_exit(FSM_State *self, void **arg); \
	int type##_update(FSM_State *self, struct timeval *dt); \
	void type##_on_enter(FSM_State *self, const void *arg);

DECLARE_STATE(insert_mode);

#endif
