#include "include/modes.h"
#include "input.h"
#include <unistd.h>

void clear_win(void);
int lines_between(char *buf, int start, int end);

void insert_mode_on_enter(FSM_State *self, const void *arg) {
	IModeData* this = (IModeData*) self->data;

	// Read cursor position
	if (arg != NULL) {
		IModeArg *imArg = (IModeArg*) arg;
		this->line = imArg->line;
		this->page = imArg->page;
		this->column = imArg->column;
	}

	// Read first chunk
	if (	this->bytesRead == 0 && 
			this->column == 0 && 
			this->line == 0 && 
			this->page == 0	) {
		this->bytesRead = read(this->fd, this->pagebuff, this->buffSize);
	}

	input_init();

}

int insert_mode_update(FSM_State *self, struct timeval *dt) {
	IModeData* this = (IModeData*) self->data;
	
	Command com;
	int c = input_getKey(&com);

	if (com == COM_NORMAL_MODE) {
		return -1;
	}

	clear_win();

	if (this->writeindex > this->bytesRead) {
		if (this->buffSize == this->bytesRead) {
			this->page++;
			this->line = 0;
			this->column = 0;
			this->index = 0;
			this->writeindex = 0;

			this->bytesRead = read(this->fd, this->pagebuff, this->buffSize);
		} else {
			return -1;
		}
	}

	if (c != ERR) {
		if (c == KEY_BACKSPACE) {
			this->writebuff[this->writeindex] = 'b';
			this->writeindex--;
		}
		else if (c == this->pagebuff[this->writeindex])
			this->writebuff[this->writeindex++] = 'g';
		else
			this->writebuff[this->writeindex++] = 'r';
	}

	int screen_h, screen_w;
	getmaxyx(stdscr, screen_h, screen_w);
	
	// Print the buffer into screen
	move(0, 0);
	int index = this->index;
	int cur_line = lines_between(this->pagebuff, 0, this->index);
	int lines_to_end = lines_between(this->pagebuff, this->index, this->bytesRead);

	for (int line = 0; line < screen_h; line++) {
		if (index > this->bytesRead) break;
		printw("%5d ", cur_line+line+1);

		for (int col = 0; col < screen_w; col++) {
			if (index > this->bytesRead) break;

			switch (this->writebuff[index]) {
				case 'g':
					attrset(A_NORMAL | COLOR_PAIR(GREEN));
					break;
				case 'r':
					attrset(A_NORMAL | COLOR_PAIR(RED));
					break;
			}
			if (index == this->writeindex) {
				attrset(A_BLINK | COLOR_PAIR(CURSOR));
				this->column = col;
			}

			if (this->pagebuff[index] == '\n') {
				printw(" \n");
				if (index == this->writeindex) {
					if (c != ERR) this->line++;
					if ((this->line - cur_line) > screen_h/2 && lines_to_end > screen_h)
						while (this->pagebuff[this->index++] != '\n');
				}
				attrset(A_NORMAL | COLOR_PAIR(BLACK));
				index++;
				break;
			}
			printw("%c", this->pagebuff[index]);

			attrset(A_NORMAL | COLOR_PAIR(BLACK));
			index++;
		}
	}

	return INSERT;
}

void insert_mode_on_exit(FSM_State *self, void **arg) {
	//IModeData* this = (IModeData*) self->data;
}

void clear_win(void) {
	attrset(A_NORMAL | COLOR_PAIR(BLACK));
	int max_x, max_y;
	getmaxyx(stdscr, max_y, max_x);
	for (int i=0; i<max_y; i++) {
		mvprintw(i,0,"%*s", max_x, "");
	}
}

int lines_between(char *buf, int start, int end) {
	int count = 0;
	for (int i = start; i <= end; i++) {
		if(buf[i] == '\n') count++;
	}
	return count;
}
