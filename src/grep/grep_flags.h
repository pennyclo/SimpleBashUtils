#ifndef GREP_FLAGS_H
#define GREP_FLAGS_H

#include <regex.h>

#include "parser_args.h"

void grep(data_t *data, int file_count);
void reader(FILE *file, data_t *data);
void outline(char *line, size_t count_char);
void e_flag(data_t *data, char *line);

#endif
