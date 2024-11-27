#ifndef PARCER_ARGS_H
#define PARCER_ARGS_H

#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e, i, v, c, l, n, h, s, f, o;
} options_t;

typedef enum {
  VALID,
  FILEPATH_ALLOC,
  COMPILE_REG,
  ALLOC_PATTERN,
  REG_ERROR,
  UNKNOWN_OPT,
} errors_t;

typedef struct {
  int valid_all_matchs;
  int valid_flags;
  int count_matchs;
  int count_line;
  int count_files;
} value_flag_t;

typedef struct {
  options_t opt;
  errors_t invalid;
  regex_t regex;
  value_flag_t value_flags;
  int num_files;
  int num_pattern;
  int num_lines;
  char** patterns;
  char** file_paths;
} data_t;

data_t parser(int argc, char** argv);
void parser_f_flags(data_t* data, char* patterns);
void move_line(char* line);
void switch_parser(int opt, data_t* data);
void alloc_filepaths(data_t* data, int argc, char** argv);
void alloc_parser(data_t* data, char* optarg);
char* strdup(const char* str);
char* alloc_patterns_o(data_t* data, size_t len_patterns);

#endif
