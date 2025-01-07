#ifndef _READER_H_
#define _READER_H_

#include <ncurses.h>
#include <unistd.h>
#include <fcntl.h>
#include "draw_utils.h"

#define textReader_isBufferEnd(reader) (reader->writeindex > reader->bytesRead)
#define textReader_isPageEnd(reader) (reader->buffSize == reader->bytesRead)
#define textReader_curLine(reader) (textReader_linesBetween(reader, 0, reader->index))
#define textReader_linesTillEnd(reader) (textReader_linesBetween(reader, reader->index, reader->bytesRead))

typedef struct {
	// Size and position
	int x;
	int y;
	int h;
	int w;

	unsigned int page;      	// Current page number
	unsigned int line;			// Current line number
	unsigned int column;		// Current column number
	unsigned int index;			// Current buffer index (where the visible text begins)
	unsigned int writeindex; 	// Current buffer index for writing
	char *pagebuff;				// Buffer containing the text read from the file
	char *writebuff;			// Contains information about text highligting
	int fd;						// File descriptor
	int buffSize;				// Buffer max size
	ssize_t bytesRead;			// Number of bytes saved on buffer from the last read
} TextReader;

unsigned int textReader_linesBetween(TextReader* self, unsigned int start, unsigned int end);

int textReader_fillBuffer(TextReader* self);

/*
 * read the next page
 *
 * each page is of the size of the buffer
 */
int textReader_pageUp(TextReader* self);

/*
 *	read the previous page
 *
 * Returns -1 on error and closes the fd
 */
int textReader_pageDown(TextReader* self);

/*
 * Moves the index (print) to the next line
 */
void textReader_lineUp(TextReader* self, int n);

/*
 * Moves the index (print) to the previous line
 */
void textReader_lineDown(TextReader* self, int n);

/*
 * updates the writebuf info and cursor position
 */
void textReader_putChar(TextReader* self, int c);

/*
 *	Prints the text on x, y, with height h and width w
 *	taken from the TextReader Object
 *
 * This function requires start_colors from draw_utils.h
 */
void textReader_print(TextReader* self);

#endif
