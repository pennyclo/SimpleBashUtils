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
    if(data->buffer[*cnt_symbol] == '\n') {
        int count_space = 0;

        while(data->buffer[*cnt_symbol] == '\n') {
            (*cnt_symbol)++;
            count_space++;
        }

        (*cnt_symbol)--;
    }
}

void optional_v(data_t *data, int ptr_symbol) {
    unsigned char c = (unsigned char)data->buffer[ptr_symbol];
    
    if(c == '\t' || c == '\n') {
        return;
    }
    
    if (c < 32){
        printf("^");
        data->buffer[ptr_symbol] = c + 64;
    } else if(c == 127) {
        printf("^");
        data->buffer[ptr_symbol] = '?';
    } else if(c > 127) {
        if(c < 160) {
            printf("M-^");
            data->buffer[ptr_symbol] = c - 64;
        } else{
            printf("M-");
            data->buffer[ptr_symbol] = c & 0x7F;
        }
    }
}