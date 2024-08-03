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