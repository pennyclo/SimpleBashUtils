#ifndef GREP_FLAGS_H
#define GREP_FLAGS_H

#include "parser_args.h"

void grep(data_t *data, int file_count);
void reader(FILE *file, data_t *data);
void outline(data_t *data, char *line);
int e_flag(data_t *data, char *line, int reti);

#endif