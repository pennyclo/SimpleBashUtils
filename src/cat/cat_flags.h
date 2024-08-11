#ifndef CAT_FLAGS_H
#define CAT_FLAGS_H

#include "parser_args.h"

void optional_b (data_t *data, int *cnt_symbol);
void optional_n (data_t *data);
void optional_E ();
void optional_T (data_t *data, int *ptr_symbol);
void optional_s (data_t *data, int *ptr_symbol);
void optional_v (data_t *data, const int *ptr_symbol);

#endif