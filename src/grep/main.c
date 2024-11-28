#include "grep_flags.h"
#include "parser_args.h"

static void destroy(data_t *data);
static void invalid_switch(data_t *data);

int main(int argc, char **argv) {
  if (argc > 2) {
    data_t data = parser(argc, argv);
    data.value_counts.count_matchs = 0;
    data.valid_all_matchs = 0;

    for (data.value_counts.count_files = 0;
         data.value_counts.count_files < data.num_files;
         data.value_counts.count_files++) {
      grep(&data);
    }

    destroy(&data);

  } else {
    fprintf(stderr, "./s21_grep [OPTION]... PATTERNS [FILE]...");
  }

  return 0;
}

static void destroy(data_t *data) {
  invalid_switch(data);

  if (data->file_paths) {
    for (int i = 0; i < data->num_files; i++) {
      if (data->file_paths[i]) {
        free(data->file_paths[i]);
        data->file_paths[i] = NULL;
      }
    }

    free(data->file_paths);
    data->file_paths = NULL;
  }

  if (data->patterns) {
    for (int i = 0; i < data->num_pattern; i++) {
      if (data->patterns[i]) {
        free(data->patterns[i]);
        data->patterns[i] = NULL;
      }
    }

    free(data->patterns);
    data->patterns = NULL;
  }
}

static void invalid_switch(data_t *data) {
  switch (data->invalid) {
    case 1:
      fprintf(stderr, "Error allocated memory for file paths");
      break;
    case 2:
      fprintf(stderr, "Could not compile regex");
      break;
    case 3:
      fprintf(stderr, "Error alocated memory for patterns line");
      break;
    case 4:
      fprintf(stderr, "Regex match failed");
      break;
    default:
      break;
  }
}