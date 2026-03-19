#include "include/input.h"

static Command keyBindings[262];

void input_init() {

	for (int i = 0; i < 262; i++) {
		keyBindings[i] = COM_UNUSED;
	}

	keyBindings[KEY_UP] = COM_UP;
	keyBindings['k'] = COM_UP;
	keyBindings[KEY_DOWN] = COM_DOWN;
	keyBindings['j'] = COM_DOWN;
	keyBindings[KEY_LEFT] = COM_LEFT;
	keyBindings['h'] = COM_LEFT;
	keyBindings[KEY_RIGHT] = COM_RIGHT;
	keyBindings['l'] = COM_RIGHT;

	keyBindings[27] = COM_NORMAL_MODE; // Esc key

	keyBindings['i'] = COM_INSERT_MODE;
	keyBindings['I'] = COM_INSERT_MODE;
	keyBindings['o'] = COM_INSERT_MODE;
	keyBindings['O'] = COM_INSERT_MODE;
	keyBindings['a'] = COM_INSERT_MODE;
	keyBindings['A'] = COM_INSERT_MODE;

	keyBindings['v'] = COM_VISUAL_MODE;

	keyBindings['s'] = COM_SEARCH;

    keyBindings['g'] = COM_LOWCASE_G;
    keyBindings['w'] = COM_LOWCASE_WORD;
    keyBindings['W'] = COM_WORD;
    keyBindings['e'] = COM_LOWCASE_END_WORD;
    keyBindings['E'] = COM_END_WORD;
    keyBindings['b'] = COM_LOWCASE_BACK;
    keyBindings['B'] = COM_BACK;
    keyBindings['^'] = COM_REL_START;
    keyBindings['0'] = COM_ABS_START;
    keyBindings['$'] = COM_END;
    keyBindings['f'] = COM_FIND;
    keyBindings['%'] = COM_MATCH_PAIRS;
}

int input_getKey(Command* com) {
	int c = getch();
	flushinp();
	if (com != NULL) {
		if (c == ERR)
			*com = COM_UNUSED;
		else
			*com = keyBindings[c];
	}
	return c;
}
