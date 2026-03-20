#include "include/reader.h"
#include "string.h"

#define MAX_CHAR_BUFF 5

void textReader_normal_mode_key_handler(TextReader *self, int c, Command com) {

    static char c_buf[MAX_CHAR_BUFF] = "";

    switch (com) {
        case COM_UP:
            textReader_lineDown(self, 1);
            break;
        case COM_DOWN:
            textReader_lineUp(self, 1);
            break;
        case COM_LEFT:
            self->writeindex--;
            self->cache_column = -1; // Update cache column on next print
            break;
        case COM_RIGHT:
            self->writeindex++;
            self->cache_column = -1; // Update cache column on next print
            break;
        default:
            break;
    }
}
