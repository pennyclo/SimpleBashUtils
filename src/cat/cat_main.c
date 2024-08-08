#include "parser_args.h"
#include "cat_flags.h"

void reader(data_t *data);
void destroy_data(data_t *data);

int main(int argc, char **argv) {
    data_t data = parser(argc, argv);

    for (int i = 0; i < data.num_files && !data.invalid; i++) {
        data.buffer = write_buffer(&data, i);
        if(!data.invalid) {
            reader(&data);
        }
    }

    destroy_data(&data);

    return 0;
}

void reader(data_t *data) {
    int i = 0;
    long lenght = strlen(data->buffer);

    while(i < lenght) {
        if(data->opt.b) {
            optional_b(data, i);
        } else if(data->opt.n) {
            optional_n(data);
        }
        while(i < lenght && data->buffer[i] != '\0' && data->buffer[i] != '\n') {
            if(data->opt.T) {
                optional_T(data, &i);
            }

            if(data->opt.v) {
                optional_v(data, &i);
            }
            
            printf("%c", data->buffer[i]);
            i++;
        }


        if(i < lenght) {
            if(data->opt.E) {
                optional_E();
            }
            
            printf("\n");
            i++;

            if(data->opt.s) {
                optional_s(data, &i);
            }

        } else {
            data->num_line--;
        }
    }

    free(data->buffer);
}

void destroy_data(data_t *data) {
    if(data->file_paths) {
        for(int i = 0; i < data->num_files; i++) {
            if(data->file_paths[i]) {
                free(data->file_paths[i]);
            }
        }

        free(data->file_paths);
    }

    switch (data->invalid) {
        case UNKNOWN_OPT:
            fprintf(stderr, "Unknown options. Only supported b,e,E,n,s,t,T,v,A\n");
            break;
        case FILEPATH_ALLOC:
            fprintf(stderr, "Error allocating file path\n");
            break;
        case BUFFER_ALLOC:
            fprintf(stderr, "Error allocated buffer\n");
            break;
        case FILE_READ:
            fprintf(stderr, "Error reading files\n");
            break;

        default:
            break;
    }
}