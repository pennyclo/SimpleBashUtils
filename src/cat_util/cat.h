#ifndef CAT_H
#define CAT_H

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

typedef struct {
    int b, E, n, s, T, v;
} arguments;

void optional_b (char *file_path);

#endif