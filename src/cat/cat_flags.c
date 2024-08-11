#include "cat_flags.h"

void optional_b (data_t *data, int *cnt_symbol) {
    // if(!(ptr_symbol && data->buffer[ptr_symbol - 1] == '\n' && data->buffer[ptr_symbol] == '\n')) {
    //     if(data->num_line > 1 && ptr_symbol == 0) {
    //         data->num_line++;
    //     } else {
    //         optional_n(data);
    //     }
    // } 
    optional_n(data);
    
    while(data->buffer[*cnt_symbol] == '\n') {
        (*cnt_symbol)++;
    }

    if(data->buffer[*cnt_symbol - 1] == '\n') {
        (*cnt_symbol)--;
    }
}

void optional_n (data_t *data) {
    printf("%6d\t", data->num_line);
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

void optional_v (data_t *data, const int *ptr_symbol) {
    if(data->buffer[*ptr_symbol] == '\t' || data->buffer[*ptr_symbol] == '\n') {
    } else if(data->buffer[*ptr_symbol] > 0 && data->buffer[*ptr_symbol] < 32) {
        printf("^");
        data->buffer[*ptr_symbol] += 64;
    } else if(data->buffer[*ptr_symbol] == 127) {
        printf("^");
        data->buffer[*ptr_symbol] = '?';
    }
}