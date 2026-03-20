#include "include/reader.h"
#include "string.h"
#include <stdlib.h>

#define MAX_CHAR_BUFF 5

void append(char* buf, char c) {
    size_t len = strlen(buf);

    if (len < MAX_CHAR_BUFF - 1) {
        buf[len] = c;
        buf[len+1] = '\0';
    }
}

void textReader_normal_mode_key_handler(TextReader *self, int c, Command com) {

    static char n_buf[MAX_CHAR_BUFF] = "";
    static char c_buf[MAX_CHAR_BUFF] = "";
    long n = 1;
    char *endptr;

    if (c >= '0' && c <= '9') {
        append(n_buf, c);
    }

    switch (com) {
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
            self->writeindex++;
            self->cache_column = -1; // Update cache column on next print
            c_buf[0] = n_buf[0] = '\0';
            break;

        default:
            break;
    }
}
