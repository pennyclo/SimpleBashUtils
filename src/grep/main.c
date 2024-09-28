#include "grep_flags.h"
#include "parser_args.h"

int main(int argc, char **argv) {
  data_t data = parser(argc, argv);

  for (int i = 0; i < data.num_files; i++) {
    grep(&data, i);
  }

  if (data.file_paths) {
    for (int i = 0; i < data.num_files; i++) {
      if (data.file_paths[i]) {
        free(data.file_paths[i]);
      }
    }

    free(data.file_paths);
  }

  return 0;
}