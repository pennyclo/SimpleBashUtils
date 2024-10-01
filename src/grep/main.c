#include "grep_flags.h"
#include "parser_args.h"

// void out_pattern(data_t *data);

int main(int argc, char **argv) {
  data_t data = parser(argc, argv);

  // out_pattern(&data);
  for (data.value_flags.count_files = 0;
       data.value_flags.count_files < data.num_files;
       data.value_flags.count_files++) {
    grep(&data);
  }

  if (data.file_paths) {  // later in function destroy
    for (int i = 0; i < data.num_files; i++) {
      if (data.file_paths[i]) {
        free(data.file_paths[i]);
      }
    }

    free(data.file_paths);
  }

  if (data.patterns) {  // later in function destroy
    for (int i = 0; i < data.num_pattern; i++) {
      if (data.patterns[i]) {
        free(data.patterns[i]);
      }
    }

    free(data.patterns);
  }

  return 0;
}

// void out_pattern(data_t *data) {
//   printf("out patterns: \n");
//   for (int i = 0; i < data->num_pattern; i++) {
//     printf("%s\n", data->patterns[i]);
//   }

//   printf("file paths: \n");

//   for (int i = 0; i < data->num_files; i++) {
//     printf("%s\n", data->file_paths[i]);
//   }
// }