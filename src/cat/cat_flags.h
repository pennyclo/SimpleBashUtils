#ifndef CAT_FLAGS_H
#define CAT_FLAGS_H

#include "parser_args.h"

#define SPACE 32
#define SHIFT 64
#define DEL 127
#define NON_BREAKING_SPACE 160

void optional_b(data_t *data, int cnt_symbol);
void optional_n(data_t *data);
void optional_E(data_t *data, int cnt_symbol);
void optional_T(data_t *data, int cnt_symbol);
void optional_s(data_t *data, int *cnt_symbol);
void optional_v(data_t *data, int ptr_symbol);

#endif
