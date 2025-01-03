#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <sys/time.h>
#include "include/fsm.h"
#include "include/modes.h"

static void mainLoop( int freq ) {
	struct timeval elapsed, f, start, end;
	FSM_State states[] = {
		{INSERT, NULL, insert_mode_on_enter, insert_mode_on_exit, insert_mode_update},
	};
	FSM fsm = {states, sizeof(states)/sizeof(FSM_State), -1};

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

int fsm_runMainLoop(int fps) {
	setlocale(LC_ALL, "");
	initscr(); cbreak(); noecho();
	start_color();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	// init_pair_colors();

	mainLoop(fps);

	endwin();
	exit(EXIT_SUCCESS);
}
