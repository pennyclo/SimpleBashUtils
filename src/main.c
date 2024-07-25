#include "cat_util/cat.h"

char** parcer(int argc, char** argv, int* num_files);
void reader(char* file_path, arguments *argument);
char* strdup(const char* str);

int main(int argc, char** argv) {
    int num_files;
    char** file = parcer(argc, argv, &num_files);

    // for(int i = 0; i < num_files; i++) {
    //     reader(file[i]);
    // }
    
    for(int i = 0; i < num_files; i++) {
        free(file[i]);
    }

    free(file);

    return 0;
}

char** parcer(int argc, char** argv, int* num_files) {
    arguments argument;
    int opt;
    *num_files = 0;
    char **file_paths = NULL;

    while((opt = getopt(argc, argv, "b:e:E:n:s:t:T:v:A:")) != -1) {
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
            case '?':
                fprintf(stderr, "Unknown options <-%c>", opt); // if this option does not exist
                exit(1);
            default:
                //Just printf files.
        }
        
        char **new_file_path = realloc(file_paths, sizeof(char *) * (*num_files + 1));
        if(!new_file_path) {
            printf("Error allocated file path");
            exit(1);
        }

        file_paths = new_file_path;

        file_paths[*num_files] = strdup(optarg);
        if(!file_paths[*num_files]) {
            printf("Error allocated new file path");
            exit(1);
        }

        *num_files += 1;
        
        reader(file_paths[0], &argument);
    }

    return file_paths;
}

void reader(char* file_path, arguments *argument) {
    FILE *file = fopen(file_path, "r");
    if(file) {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        char* buffer = (char *) malloc(file_size + 1);
        if(!buffer) {
            printf("Error allocated buffer");
            fclose(file);
            exit(1);
        } else {
            size_t bytes_read = fread(buffer, 1, file_size, file);
            if((long)bytes_read != file_size) {
                printf("Error reading files");
                free(buffer);
                fclose(file);
                exit(1);
            } else {
                int i = 0;
                int num_line = 1;
                buffer[file_size] = '\0';
                // printf("%s", buffer);
                while(buffer[i] != '\0') {
                    if(argument->n) {
                        if(num_line < 10) {
                            printf(" ");
                        }
                        printf("     %d  ", num_line);
                    }
                    while(buffer[i] != '\n' && buffer[i] != '\0') {
                        printf("%c", buffer[i]);
                        i++;
                    }
                    i++;
                    num_line++;
                    printf("\n");
                }
                free(buffer);
                fclose(file);
            }
        }
    } else {
        printf("cat: %s: No such file or directory\n", optarg);
    }
}

char* strdup(const char* str) {
    size_t length = strlen(str) + 1;
    char* new_str = malloc(length);
    if (new_str) {
        memcpy(new_str, str, length);
    }
    
    return new_str;
}
