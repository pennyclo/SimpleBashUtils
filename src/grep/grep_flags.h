#ifndef GREP_FLAGS_H
#define GREP_FLAGS_H

#include "parser_args.h"

void grep(data_t *data);
void reader(FILE *file, data_t *data);
int count_matchs(data_t *data, const char *line);
int valid_match(data_t *data, const char *line);
void outline(data_t *data, const char *line, int matchs_count);
void processing_line(data_t *data, const char *line);
void processing_h_flag(const data_t *data);
void processing_n_flag(const data_t *data);
void processing_c_flag(const data_t *data);
void processing_o_flag(data_t *data, const char *line);
void processing_l_c_flags(const data_t *data);
void output(const char *line);
void compiling_reg(data_t *data, const char *patterns);
size_t find_len_patterns(const data_t *data);
char *patterns_for_o(const data_t *data, char *patterns_line);

#endif
