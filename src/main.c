#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "../cat_util/cat.h"

arguments *parcer(int argc, char** argv);
void reader(char** argv);

int main(int argc, char** argv) {
    

    return 0;
}

arguments *parcer(int argc, char** argv) {
    arguments argument;
    int opt;

    while(opt = getopt(argc, argv, "beEnstTvA")) {
        switch (opt) {
            case 'b':
                argument.b = 1;
                break;
            case 'e':
                argument.E = 1;
                argument.v = 1;
                break;
            case 'E':
                argument.E = 1;
                break;
            case 'n':
                argument.n = 1;
                break;
            case 's':
                argument.s = 1;
                break;
            case 't':
                argument.T = 1;
                argument.v = 1;
                break;
            case 'T':
                argument.T = 1;
                break;
            case 'v':
                argument.v = 1;
                break;
            case 'A':
                argument.v = 1;
                argument.E = 1;
                argument.T = 1;
                break;
            default:
                fprintf(stderr, "Unknown options <-%c>", opt); // if this option does not exist
                exit(1);
        }
    }

    return &argument;
}

void reader(char** argv) {

}

