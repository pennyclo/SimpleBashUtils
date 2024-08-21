#include "cat_flags.h"

void optional_b(data_t *data, int cnt_symbol) {
    if(data->buffer[cnt_symbol] != '\n') {
        optional_n(data);
    }
}

void optional_n(data_t *data) {
    printf("%6d\t", data->num_line++);
}

void optional_E(data_t *data, int cnt_symbol) {
    if(data->buffer[cnt_symbol] == '\n') {
        printf("$");
    }
}

void optional_T(data_t *data, int cnt_symbol) {
    if(data->buffer[cnt_symbol] == '\t') {
        printf("^");
        data->buffer[cnt_symbol] = 'I';
    }
}

void optional_s(data_t *data, int *cnt_symbol) {
    int empty_lines = 0;

    while (*cnt_symbol < data->lenght && data->buffer[*cnt_symbol] == '\n') {
        (*cnt_symbol)++;
        empty_lines++;
    }

}

void optional_v(data_t *data, const int *ptr_symbol) {
    if(data->buffer[*ptr_symbol] == '\t' || data->buffer[*ptr_symbol] == '\n') {
    } else if(data->buffer[*ptr_symbol] > 0 && data->buffer[*ptr_symbol] < 32) {
        printf("^");
        data->buffer[*ptr_symbol] += 64;
    } else if(data->buffer[*ptr_symbol] == 127) {
        printf("^");
        data->buffer[*ptr_symbol] = '?';
    }
}