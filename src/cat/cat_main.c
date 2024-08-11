#include "parser_args.h"
#include "cat_flags.h"

void reader(data_t *data, int *cnt_lines);
void destroy_data(data_t *data);

int main(int argc, char **argv) {
    data_t data = parser(argc, argv);
    int cnt_lines = 1;

    for (int i = 0; i < data.num_files && !data.invalid; i++) {
        write_buffer(&data, i);
        if(!data.invalid && data.buffer) {
            reader(&data, &cnt_lines);
        }
    }

    destroy_data(&data);

    return 0;
}

void reader(data_t *data, int *cnt_lines) {
    int i = 0;

    while(i < data->lenght) {
        if(*cnt_lines) {
            if(data->opt.b) {
                optional_b(data, &i);
            } else if(data->opt.n) {
                optional_n(data);
            }
            
            *cnt_lines = 0;
        }

        if(data->buffer[i] == '\n') {
            data->num_line++;
            *cnt_lines = 1;
        }
        

        printf("%c", data->buffer[i]);
        i++;
        
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