#include "cat_flags.h"
#include "parser_args.h"

static void reader(data_t *data, int *cnt_lines);
static void destroy_data(data_t *data);
static void invalid_switch(const data_t *data);

int main(int argc, char **argv) {
  data_t data = parser(argc, argv);
  int cnt_lines = 1;

  for (int i = 0; i < data.num_files && !data.invalid; i++) {
    write_buffer(&data, i);
    if (!data.invalid && data.buffer) {
      reader(&data, &cnt_lines);
    }
    free(data.buffer);
  }

  destroy_data(&data);

  return 0;
}

static void reader(data_t *data, int *cnt_lines) {
  int i = 0;

  while (i < data->lenght) {
    if (*cnt_lines) {
      if (data->opt.b) {
        optional_b(data, i);
      } else if (data->opt.n) {
        optional_n(data);
      }

      if (data->opt.s) {
        optional_s(data, &i);
      }

      *cnt_lines = 0;
    }

    if (data->opt.E) {
      optional_E(data, i);
    }

    if (data->opt.T) {
      optional_T(data, i);
    }

    if (data->buffer[i] == '\n') {
      *cnt_lines = 1;
    }

    if (data->opt.v) {
      optional_v(data, i);
    }

    printf("%c", data->buffer[i]);
    i++;
  }
}

static void destroy_data(data_t *data) {
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
}

static void invalid_switch(const data_t *data) {
  switch (data->invalid) {
    case UNKNOWN_OPT:
      fprintf(stderr, "Try 'cat --help' for more information.\n");
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