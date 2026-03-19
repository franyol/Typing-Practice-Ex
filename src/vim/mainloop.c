#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include "fsm.h"
#include "modes.h"
#include "draw_utils.h"
#include "input.h"
#include "include/sections.h"

static void mainLoop( int freq, long section ) {
	struct timeval elapsed, f, start, end;

	static char pageBuff[8192];
	static char writeBuff[8192];
	static TextReader reader;
    reader.pagebuff = pageBuff;
    reader.writebuff = writeBuff;
    reader.message = "";
	reader.page = 0;
	reader.line = 0;
	reader.column = 0;
    reader.cache_column = 0;
    reader.on_last_column = 0;
	reader.index = 0;
	reader.writeindex = 0;
	//reader.fd = fd;
	reader.buffSize = 8192;
	reader.bytesRead = 0;

	FSM_State states[] = {
		{INSERT, NULL, section_1_on_enter, section_1_on_exit, section_1_update},
		{INSERT, &reader, section_2_on_enter, section_2_on_exit, section_2_update},
	};
	FSM fsm = {states, sizeof(states)/sizeof(FSM_State), section-1};

	f.tv_sec = 1/freq;
	f.tv_usec = (1000000/freq) % 1000000;
	elapsed.tv_sec = 100;
	elapsed.tv_usec = 0;

	if (gettimeofday(&start, NULL) != 0) {
		fprintf(stderr, "gettimeofday error\n");
		exit(EXIT_FAILURE);
	}

	for (;;) {
		fsm_update(&fsm, &elapsed);
		if (fsm.current == -1) break;

		do {
			if (gettimeofday(&end, NULL) != 0) {
				fprintf(stderr, "gettimeofday error\n");
				exit(EXIT_FAILURE);
			}

			elapsed.tv_sec = end.tv_sec - start.tv_sec;
			elapsed.tv_usec = end.tv_usec - start.tv_usec;
		} while( freq > 0 && ((f.tv_sec > elapsed.tv_sec) ||
				(f.tv_sec == elapsed.tv_sec && f.tv_usec > elapsed.tv_usec)) );

		start = end;

		refresh();
	}
}

int vim_runMainLoop(int fps, long section) {
	setlocale(LC_ALL, "");
	initscr(); cbreak(); noecho();
	start_color();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	init_colors();
	input_init();

	mainLoop(fps, section);

	endwin();
	exit(EXIT_SUCCESS);
}
