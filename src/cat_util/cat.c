#include "cat.h"

void optional_b (char *file_path) {
    
}

void optional_n (int *num_line) {
    if(*num_line < 10) {
        printf(" ");
    }
    printf("     %d  ", *num_line);
}