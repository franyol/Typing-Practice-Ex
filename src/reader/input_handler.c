#include "include/reader.h"
#include "string.h"
#include <stdlib.h>

#define MAX_CHAR_BUFF 5

int is_word_char(char c);
int is_blank_char(char c);
int is_non_word_char(char c);

void append(char* buf, char c);

void textReader_normal_mode_key_handler(TextReader *self, int c, Command com) {

    static char n_buf[MAX_CHAR_BUFF] = "";
    static char c_buf[MAX_CHAR_BUFF] = "";
    long n = 1;
    char *endptr;

    if (c >= '0' && c <= '9') {
        append(n_buf, c);
    }

    switch (com) {
        case COM_NORMAL_MODE:
            c_buf[0] = n_buf[0] = '\0';
            break;

        case COM_LOWCASE_G:
            append(c_buf, 'g');
            break;

        case COM_LOWCASE_WORD:
            n = strtol(n_buf, &endptr, 10);
            if (*endptr != '\0' || n_buf[0] == '\0') n = 1;
            for (int i = 0; i < n; i++) {
                // If in word, move to next non word
                if (is_word_char(self->pagebuff[self->writeindex])) {
                    while (is_word_char(self->pagebuff[self->writeindex])) {
                        if (self->writeindex >= self->bytesRead-1) break;
                        self->writeindex++;
                    }
                // If is non word, move to next word
                } else if (is_non_word_char(self->pagebuff[self->writeindex])) {
                    while (is_non_word_char(self->pagebuff[self->writeindex])) {
                        if (self->writeindex >= self->bytesRead-1) break;
                        self->writeindex++;
                    }
                }
                // Skip blank characters
                if (is_blank_char(self->pagebuff[self->writeindex])) {
                    while (is_blank_char(self->pagebuff[self->writeindex])) {
                        if (self->writeindex >= self->bytesRead-1) break;
                        self->writeindex++;
                    }
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
