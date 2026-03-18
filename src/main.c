#include "fsm.h"
#include "vim.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		fprintf(stderr, "Usage: %s vim [section:int]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (strcmp(argv[1], "vim") == 0) {
		if (argc > 2) {
			char *endptr;
			long section = strtol(argv[2], &endptr, 10);

			if (*endptr != '\0')
				exit(EXIT_FAILURE);

			vim_runMainLoop(30, section);	
		}
	}

	fsm_runMainLoop(30, argv[1]);	
}
