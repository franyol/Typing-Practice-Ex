#ifndef __SECTIONS_H__
#define __SECTIONS_H__

#define MAX_FILES 1024
#define MAX_PATH 512

//
#define TEXT_DIR "/home/franyol/Desktop/gitrep/Typing-Practice-Ex/data/text"

#include "../../fsm/include/modes.h"

typedef enum Section {
	SECTION_1,
    SECTION_2,
} Section;

DECLARE_STATE(section_1);
DECLARE_STATE(section_2);

int open_random_file(const char *dir_path);

#endif
