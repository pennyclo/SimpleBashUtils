#ifndef PARSER_ARGS_H
#define PARSER_ARGS_H

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


data_t parser(int argc, char** argv);
void switch_parser(int opt, data_t *data);
void alloc_filepaths (data_t *data, int argc, char **argv);
void write_buffer(data_t *data, int file_count);
char* strdup(const char* str);

#endif