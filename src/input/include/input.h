#ifndef _INPUT_H_
#define _INPUT_H_

#include <ncurses.h>

typedef enum {
	COM_UP,
	COM_DOWN,
	COM_LEFT,
	COM_RIGHT,
	COM_NORMAL_MODE,
	COM_INSERT_MODE,
	COM_VISUAL_MODE,
	COM_SEARCH,
	COM_UNUSED,
    COM_LOWCASE_G,
    COM_LOWCASE_WORD,
    COM_WORD,
    COM_END_WORD,
    COM_LOWCASE_END_WORD,
    COM_LOWCASE_BACK,
    COM_BACK,
    COM_REL_START,
    COM_ABS_START,
    COM_END,
    COM_FIND,
    COM_MATCH_PAIRS,
} Command;

void input_init();

int input_getKey(Command* com);

#endif
