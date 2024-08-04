#include "cat.h"

void optional_b (data_t *data, int ptr_symbol) {
    if(!(ptr_symbol && data->buffer[ptr_symbol - 1] == '\n' && data->buffer[ptr_symbol] == '\n')) {
        if(data->num_line > 1 && ptr_symbol == 0) {
            data->num_line++;
        } else {
            optional_n(data);
        }
    } 
}

void optional_n (data_t *data) {
    printf("%6d  ", data->num_line++);
}

void optional_E () {
    printf("$");
}

void optional_T (data_t *data, int *ptr_symbol) {
    if(data->buffer[*ptr_symbol] == '\t') {
        printf("^I");
        (*ptr_symbol)++;
    }

}

void optional_s (data_t *data, int *ptr_symbol) {
    int tmp = 0;
    while(data->buffer[*ptr_symbol] == '\n') {
        (*ptr_symbol)++;
        tmp++;
    }

    if(tmp >= 1) {
        printf("%6d", data->num_line++);
        printf("\n");
    }
}