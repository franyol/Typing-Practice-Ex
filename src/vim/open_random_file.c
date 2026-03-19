#include "include/sections.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int open_random_file(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (!dir) {
        perror("opendir");
        return -1;
    }

    char *files[MAX_FILES];
    int count = 0;

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[MAX_PATH];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode)) {
            files[count++] = strdup(full_path);

            if (count >= MAX_FILES)
                break;
        }
    }

    closedir(dir);

    if (count == 0) {
        return -1;
    }

    int index = rand() % count;

    int fd = open(files[index], O_RDONLY);
    if (fd == -1) {
        perror("open");
    }

    // Free memory
    for (int i = 0; i < count; i++) {
        free(files[i]);
    }

    return fd;
}
