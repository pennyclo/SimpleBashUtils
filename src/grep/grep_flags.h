#ifndef GREP_FLAGS_H
#define GREP_FLAGS_H

#include "parser_args.h"

void grep(data_t *data);
void reader(FILE *file, data_t *data);
void outline(data_t *data, const char *line, int matchs_count);
int value_match(data_t *data, const char *line);
int matchs(data_t *data, const char *line);
int e_flag(data_t *data, char *line, int reti);

#endif
