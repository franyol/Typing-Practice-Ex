#ifndef __SECTIONS_H__
#define __SECTIONS_H__

#include "../../fsm/include/modes.h"

typedef enum Section {
	SECTION_1,
    SECTION_2,
} Section;

DECLARE_STATE(section_1);
DECLARE_STATE(section_2);

#endif
