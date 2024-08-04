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
    FILE_READ,
    MISS_FILE
} errors_t;

typedef struct {
    int b, E, n, s, T, v;
} options_t;

typedef struct {
    options_t opt;
    char **file_paths;
    char *buffer;
    int num_files;
    int num_line;
    errors_t invalid;
} data_t;

void optional_b (data_t *data, int ptr_symbol);
void optional_n (data_t *data);
void optional_E ();
void optional_T (data_t *data, int *ptr_symbol);
void optional_s (data_t *data, int *ptr_symbol);

#endif