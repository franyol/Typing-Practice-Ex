#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include "include/fsm.h"
#include "include/modes.h"
#include "draw_utils.h"
#include "input.h"
#include "reader.h"

static void mainLoop( int freq, char *filename ) {
	struct timeval elapsed, f, start, end;

	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	static char pageBuff[8192];
	static char writeBuff[8192];
	static TextReader reader;
	static IModeData insert_data;

	reader.page = 0;
	reader.line = 0;
	reader.column = 0;
	reader.index = 0;
	reader.writeindex = 0;
	reader.pagebuff = pageBuff;
	reader.writebuff = writeBuff;
	reader.fd = fd;
	reader.buffSize = 8192;
	reader.bytesRead = 0;

	insert_data.reader = &reader;
	
	FSM_State states[] = {
		{INSERT, &insert_data, insert_mode_on_enter, insert_mode_on_exit, insert_mode_update},
		{NORMAL, &insert_data, normal_mode_on_enter, normal_mode_on_exit, normal_mode_update},
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

int fsm_runMainLoop(int fps, char *filename) {
	setlocale(LC_ALL, "");
	initscr(); cbreak(); noecho();
	start_color();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	init_colors();
	input_init();

	mainLoop(fps, filename);

	endwin();
	exit(EXIT_SUCCESS);
}
