#include "cat_util/cat.h"

data_t parser(int argc, char** argv);
void reader(data_t *data, int file_count);
char* strdup(const char* str);
void destroy_data(data_t *data);

int main(int argc, char **argv) {
    data_t data = parser(argc, argv);
    
    for (int i = 0; i < data.num_files && !data.invalid; i++) {
        reader(&data, i);
    }

    destroy_data(&data);

    return 0;
}

data_t parser(int argc, char **argv) {
    data_t data;
    data.opt.b = data.opt.E = data.opt.n = data.opt.s = data.opt.T = data.opt.v = 0;
    data.invalid = VALID;
    data.file_paths = NULL;
    data.num_line = 1;
    data.num_files = 0;
    int opt;

    static struct option long_options[] = {
        {"show-all", no_argument, 0, 'A'},
        {"number-nonblank", no_argument, 0, 'b'},
        {"show-ends", no_argument, 0, 'E'},
        {"number", no_argument, 0, 'n'},
        {"squeeze-blank", no_argument, 0, 's'},
        {"show-tabs", no_argument, 0, 'T'},
        {"show-nonprinting", no_argument, 0, 'v'},
        {0, 0, 0, 0}
    };

    while((opt = getopt_long(argc, argv, "beEnstTvA", long_options, NULL)) != -1) {
        switch (opt) {
            case 'b':
                data.opt.b = 1;
                break;
            case 'e':
                data.opt.E = 1;
                data.opt.v = 1;
                break;
            case 'E':
                data.opt.E = 1;
                break;
            case 'n':
                data.opt.n = 1;
                break;
            case 's':
                data.opt.s = 1;
                break;
            case 't':
                data.opt.T = 1;
                data.opt.v = 1;
                break;
            case 'T':
                data.opt.T = 1;
                break;
            case 'v':
                data.opt.v = 1;
                break;
            case 'A':
                data.opt.v = 1;
                data.opt.E = 1;
                data.opt.T = 1;
                break;
            case '?':
                data.invalid = UNKNOWN_OPT;
            default:
                //Just printf files.
        }
    }

    for (int index = optind; index < argc && !data.invalid; index++) {
        data.file_paths = realloc(data.file_paths, sizeof(char *) * (data.num_files + 1));
        if (!data.file_paths) {
            data.invalid = FILEPATH_ALLOC;
        }

        if(!data.invalid) {
            data.file_paths[data.num_files] = strdup(argv[index]);
            if (!data.file_paths[data.num_files]) {
                data.invalid = FILEPATH_ALLOC;
            }
        }

        data.num_files++;
    }

    return data;
}

void reader(data_t *data, int file_count) {
    size_t bytes_read;
    FILE *file = fopen(data->file_paths[file_count], "r");
    if(!file) {
        fprintf(stderr, "cat: %s: No such file or directory\n", optarg);
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char *)malloc(file_size + 1);
    if(!buffer) {
        data->invalid = BUFFER_ALLOC;
    } 

    if(!data->invalid) {
        bytes_read = fread(buffer, 1, file_size, file);
        if((long)bytes_read != file_size) {
            data->invalid = FILE_READ;
        } 
    }

    if(!data->invalid) {
        int i = 0;
        buffer[file_size] = '\0';
        while(i < file_size && buffer[i] != '\0') {
            if(data->opt.b) {
                if(!(i && buffer[i - 1] == '\n' && buffer[i] == '\n')) {
                    if(file_count && i == 0) {
                        data->num_line++;
                    } else {
                        if(data->num_line < 10) {
                            printf(" ");
                        }
                        printf("     %d  ", data->num_line++);
                    }
                } 
            } else if(data->opt.n) {
                if(data->num_line < 10) {
                    printf(" ");
                }
                printf("     %d  ", data->num_line++);
            }
            while(i < file_size && buffer[i] != '\n' && buffer[i] != '\0') {
                printf("%c", buffer[i]);
                i++;
            }
            i++;
            if(i < file_size) {
                printf("\n");
            } else {
                data->num_line--;
            }
        }
    }

    free(buffer);
    fclose(file);
}

char* strdup(const char* str) {
    size_t length = strlen(str) + 1;
    char* new_str = malloc(length);
    if (new_str) {
        memcpy(new_str, str, length);
    }
    
    return new_str;
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

    switch (data->invalid)
    {
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