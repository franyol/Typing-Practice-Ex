#ifndef _INPUT_H_
#define _INPUT_H_

#include <ncurses.h>

typedef enum {
	COM_UP,
	COM_DOWN,
	COM_LEFT,
	COM_RIGHT,
	COM_NORMAL_MODE,
	COM_INPUT_MODE,
	COM_VISUAL_MODE,
	COM_SEARCH,
	COM_UNUSED
} Command;

void input_init();

int input_getKey(Command* com);

#endif
