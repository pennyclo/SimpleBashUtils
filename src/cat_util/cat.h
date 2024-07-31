#ifndef CAT_H
#define CAT_H

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

typedef enum {
    VALID,
    UNKNOWN_OPT,
    FILEPATH_ALLOC,
    BUFFER_ALLOC,
    FILE_READ
} errors_t;

typedef struct {
    int b, E, n, s, T, v;
} options_t;

typedef struct {
    options_t opt;
    char **file_paths;
    int num_files;
    int num_line;
    errors_t invalid;
} data_t;


void optional_b (char *file_path);

#endif