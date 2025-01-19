#ifndef _MODES_H_
#define _MODES_H_

#include "fsm.h"
#include "../../reader/include/reader.h"
#include <time.h>
#include <ncurses.h>

typedef enum Mode {
	INSERT,
	NORMAL
} Mode;

typedef struct IModeData {
	TextReader *reader;	
} IModeData;

typedef struct IModeArg {
	int x;
} IModeArg;

typedef struct NModeData {
	TextReader *reader;	
} NModeData;

typedef struct NModeArg {
	int x;
} NModeArg;

#define DECLARE_STATE(type) \
	void type##_on_exit(FSM_State *self, void **arg); \
	int type##_update(FSM_State *self, struct timeval *dt); \
	void type##_on_enter(FSM_State *self, const void *arg);

DECLARE_STATE(insert_mode);
DECLARE_STATE(normal_mode);

#endif
