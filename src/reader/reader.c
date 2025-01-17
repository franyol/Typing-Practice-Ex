#include "include/reader.h"
#include <unistd.h>

unsigned int textReader_linesBetween(TextReader *self, unsigned int start, unsigned int end) {
	int count = 0;
	int index = 0;
	for (; start <= end; start++) {
		index++;
		if(self->pagebuff[start] == '\n' || index >= self->w - 7) {
			index = 0;
			count++;
		}
	}
	return count;
}

int textReader_fillBuffer(TextReader *self) {
	self->bytesRead = read(self->fd, self->pagebuff, self->buffSize);
	return self->bytesRead;
}

int textReader_pageUp(TextReader *self) {
	self->page++;
	self->line = 0;
	self->column = 0;
	self->index = 0;
	self->writeindex = 0;

	for (int i = 0; i < self->bytesRead; i++)
		self->writebuff[i] = 'b';

	return textReader_fillBuffer(self);
}

int textReader_pageDown(TextReader *self) {
	if (self->page < 1) return 0;
	if (lseek(self->fd, -self->buffSize, SEEK_CUR) == -1) {
		perror("lseek");
		close(self->fd);
		return -1;
	}

	self->page--;
	self->line = 0;
	self->column = 0;
	self->index = 0;
	self->writeindex = 0;

	return textReader_fillBuffer(self);
}

void textReader_lineUp(TextReader *self, int n) {
	int j = 0;
	for (int i = 0; i < n; i++) {
		while(self->index < self->buffSize) {
			if (self->pagebuff[self->index++] != '\n') break;
			if (self->column + j++ >= self->w - 7) break;
		}
	}
}

void textReader_lineDown(TextReader *self, int n) {
	int j = 0;
	for (int i = 0; i < n; i++) {
		while(self->index > 0) {
			if (self->pagebuff[self->index--] != '\n') break;
			if (self->column - j++ < 0) break;
		}
	}
}

void textReader_putChar(TextReader* self, int c) {
	if (c != ERR) {
		if (c == KEY_BACKSPACE) {
			self->writebuff[self->writeindex] = 'b';

			self->writeindex--;
		} else {

			if (c == self->pagebuff[self->writeindex])
				self->writebuff[self->writeindex++] = 'g';
			else
				self->writebuff[self->writeindex++] = 'r';
		}
	}
}

void textReader_print(TextReader* self) {
	move(self->y, self->x);

	int index, lines = 0, count = 0;
	for (index=self->writeindex; lines <= self->h/2 && index > 0;) {
		index--;
		count++;
		if (self->pagebuff[index] == '\n' || count >= self->w - 7) {
				lines++;
				count = 0;
		}
	}
	self->index = index;

	unsigned int cur_line = textReader_curLine(self) + 1;

	for (int line = 0; line < self->h; line++) {
		if (index > self->bytesRead) break;
		printw("%5d ", cur_line+line);

		for (int col = 0; 1; col++) {
			if (index > self->bytesRead) break;
			if (col >= self->w-7) {
				printw("\n");
				break;
			}

			switch (self->writebuff[index]) {
				case 'g':
					attrset(A_NORMAL | COLOR_PAIR(GREEN));
					break;
				case 'r':
					attrset(A_NORMAL | COLOR_PAIR(RED));
					break;
			}

			// Blinking cursor
			if (index == self->writeindex) {
				attrset(A_BLINK | COLOR_PAIR(CURSOR));
				self->column = col;
				self->line = line;
			}

			if (self->pagebuff[index] == '\n') {
				printw(" \n");
				attrset(A_NORMAL | COLOR_PAIR(BLACK));
				index++;
				break;
			}
			printw("%c", self->pagebuff[index]);

			attrset(A_NORMAL | COLOR_PAIR(BLACK));
			index++;
		}
	}
}
