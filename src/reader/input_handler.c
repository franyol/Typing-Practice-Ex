#include "include/reader.h"
#include "string.h"
#include <stdlib.h>

#define MAX_CHAR_BUFF 20

int is_word_char(char c);
int is_blank_char(char c);
int is_non_word_char(char c);

void goto_next_non_non_word(TextReader* self);
void goto_next_non_word(TextReader* self);
void goto_next_non_blank(TextReader* self);
void goto_next_char(TextReader* self, char c);
void goto_prev_char(TextReader* self, char c);

void append(char* buf, char c);

void textReader_normal_mode_key_handler(TextReader *self, int c, Command com) {

    static char n_buf[MAX_CHAR_BUFF] = "";
    static char c_buf[MAX_CHAR_BUFF] = "";
    long n = 1;
    char *endptr;

    self->message = c_buf;

    if (c >= '0' && c <= '9' && c_buf[0] == '\0') {
        append(n_buf, c);
    }

    // Keys that expect a second keystroke have this special treatment
    if (c_buf[0] == 'f' || c_buf[0] == 'F') {
        if (com != COM_NORMAL_MODE &&
                c != ERR)
            com = (c_buf[0] == 'f') ? COM_FIND : COM_FIND_BACK;
    }

    // Keys that expect a second keystroke have this special treatment
    if (c_buf[0] == 'g') {
        if (com != COM_END_WORD &&
            com != COM_LOWCASE_END_WORD &&
            com != COM_LOWCASE_G &&
            com != COM_UNUSED) {
            com = COM_NORMAL_MODE;
        }
    }

    switch (com) {
        case COM_NORMAL_MODE:
            c_buf[0] = n_buf[0] = '\0';
            break;

        case COM_LOWCASE_G:
            if (c_buf[0] == 'g') {
                self->writeindex = 0;
                self->cache_column = -1;
                c_buf[0] = n_buf[0] = '\0';
            } else {
                append(c_buf, 'g');
            }
            break;

        case COM_FIND:
            if (c_buf[0] == 'f') {
                goto_next_char(self, c);
                self->cache_column = -1;
                c_buf[0] = n_buf[0] = '\0';
            } else {
                append(c_buf, 'f');
            }
            break;

        case COM_FIND_BACK:
            if (c_buf[0] == 'F') {
                goto_prev_char(self, c);
                self->cache_column = -1;
                c_buf[0] = n_buf[0] = '\0';
            } else {
                append(c_buf, 'F');
            }
            break;

        case COM_ABS_START:
            self->writeindex = self->writeindex - self->column;
            self->cache_column = -1;
            break;

        case COM_REL_START:
            self->writeindex = self->writeindex - self->column;
            goto_next_non_blank(self);
            self->cache_column = -1;
            break;

        case COM_END:
            goto_next_char(self, '\n');
            self->cache_column = -1;
            break;

        case COM_WORD:
            n = strtol(n_buf, &endptr, 10);
            if (*endptr != '\0' || n_buf[0] == '\0') n = 1;
            for (int i = 0; i < n; i++) {
                while (is_word_char(self->pagebuff[self->writeindex]) ||
                        is_non_word_char(self->pagebuff[self->writeindex])) {
                    goto_next_non_word(self);
                    goto_next_non_non_word(self);
                }
                goto_next_non_blank(self);
            }

            c_buf[0] = n_buf[0] = '\0';
            break;

        case COM_LOWCASE_WORD:
            n = strtol(n_buf, &endptr, 10);
            if (*endptr != '\0' || n_buf[0] == '\0') n = 1;
            for (int i = 0; i < n; i++) {
                // If in word, move to next non word
                if (is_word_char(self->pagebuff[self->writeindex])) {
                    goto_next_non_word(self);
                // If is non word, move to next word
                } else if (is_non_word_char(self->pagebuff[self->writeindex])) {
                    goto_next_non_non_word(self);
                }
                // Skip blank characters
                if (is_blank_char(self->pagebuff[self->writeindex])) {
                    goto_next_non_blank(self);
                }
            }
            self->cache_column = -1; // update cache column

            c_buf[0] = n_buf[0] = '\0';
            break;

        case COM_UP:
            n = strtol(n_buf, &endptr, 10);
            if (*endptr != '\0' || n_buf[0] == '\0') n = 1;

            textReader_lineDown(self, n);
            c_buf[0] = n_buf[0] = '\0';
            break;

        case COM_DOWN:
            n = strtol(n_buf, &endptr, 10);
            if (*endptr != '\0' || n_buf[0] == '\0') n = 1;

            textReader_lineUp(self, n);
            c_buf[0] = n_buf[0] = '\0';
            break;

        case COM_LEFT:
            self->writeindex--;
            self->cache_column = -1; // Update cache column on next print
            c_buf[0] = n_buf[0] = '\0';
            break;

        case COM_RIGHT:
            if (self->writeindex < self->bytesRead-1) self->writeindex++;
            self->cache_column = -1; // Update cache column on next print
            c_buf[0] = n_buf[0] = '\0';
            break;

        default:
            break;
    }
}

int is_word_char(char c) {
    return (
        (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') ||
        (c == '_')
    );
}

int is_blank_char(char c) {
    return (
        (c == ' ') ||
        (c == '\n') ||
        (c == '\t') ||
        (c == '\r')
    );
}

int is_non_word_char(char c) {
    return !is_word_char(c) && !is_blank_char(c);
}

void append(char* buf, char c) {
    size_t len = strlen(buf);

    if (len < MAX_CHAR_BUFF - 1) {
        buf[len] = c;
        buf[len+1] = '\0';
    }
}

void goto_next_non_word(TextReader* self) {
    while (is_word_char(self->pagebuff[self->writeindex])) {
        if (self->writeindex >= self->bytesRead-1) break;
        self->writeindex++;
    }
}

void goto_next_non_non_word(TextReader* self) {
    while (is_non_word_char(self->pagebuff[self->writeindex])) {
        if (self->writeindex >= self->bytesRead-1) break;
        self->writeindex++;
    }
}

void goto_next_non_blank(TextReader* self) {
    while (is_blank_char(self->pagebuff[self->writeindex])) {
        if (self->writeindex >= self->bytesRead-1) break;
        self->writeindex++;
    }
}

void goto_next_char(TextReader* self, char c) {
    while (self->pagebuff[self->writeindex] != c) {
        if (self->writeindex >= self->bytesRead-1) break;
        self->writeindex++;
    }
}

void goto_prev_char(TextReader* self, char c) {
    while (self->pagebuff[self->writeindex] != c) {
        if (self->writeindex <= 0) break;
        self->writeindex--;
    }
}
