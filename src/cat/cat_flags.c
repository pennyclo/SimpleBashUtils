#include "cat_flags.h"

void optional_b(data_t *data, int cnt_symbol) {
  if (data->buffer[cnt_symbol] != '\n') {
    optional_n(data);
  }
}

void optional_n(data_t *data) { printf("%6d\t", data->num_line++); }

void optional_E(data_t *data, int cnt_symbol) {
  if (data->buffer[cnt_symbol] == '\n') {
    printf("$");
  }
}

void optional_T(data_t *data, int cnt_symbol) {
  if (data->buffer[cnt_symbol] == '\t') {
    printf("^");
    data->buffer[cnt_symbol] = 'I';
  }
}

void optional_s(data_t *data, int *cnt_symbol) {
  if (data->buffer[*cnt_symbol] == '\n') {
    int count_space = 0;

    while (data->buffer[*cnt_symbol] == '\n') {
      (*cnt_symbol)++;
      count_space++;
    }

    (*cnt_symbol)--;
  }
}

void optional_v(data_t *data, int ptr_symbol) {
  unsigned char c = (unsigned char)data->buffer[ptr_symbol];

  if (c == '\t' || c == '\n') {
    return;
  }

  if (c < SPACE) {
    printf("^");
    data->buffer[ptr_symbol] = c + SHIFT;
  } else if (c == DEL) {
    printf("^");
    data->buffer[ptr_symbol] = '?';
  } else if (c > DEL) {
    if (c < NON_BREAKING_SPACE) {
      printf("M-^");
      data->buffer[ptr_symbol] = c - SHIFT;
    } else {
      printf("M-");
      data->buffer[ptr_symbol] = c & DEL;
    }
  }
}
