#include "parser_args.h"

data_t parser(int argc, char **argv) {
  data_t data = {.opt = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, .num_pattern = 0};
  data.invalid = VALID;
  int opt = 0;

  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch_parser(opt, &data);
    if (optarg) {
      alloc_parser(&data, optarg);
    } else {
      printf("optarg - clear");
    }
  }

  alloc_filepaths(&data, argc, argv);

  return data;
}

void alloc_parser(data_t *data, char *optarg) {
  data->patterns =
      realloc(data->patterns, sizeof(char *) * (data->num_pattern + 1));
  if (!data->patterns) {
    data->invalid = FILEPATH_ALLOC;  // rename later
  }

  if (!data->invalid) {
    data->patterns[data->num_pattern] = strdup(optarg);
    if (!data->patterns[data->num_pattern]) {
      data->invalid = FILEPATH_ALLOC;
    }
  }

  data->num_pattern++;
}

void switch_parser(int opt, data_t *data) {
  switch (opt) {
    case 'e':
      data->opt.e = 1;
      break;
    case 'i':
      data->opt.i = 1;
      break;
    case 'v':
      data->opt.v = 1;
      break;
    case 'c':
      data->opt.c = 1;
      break;
    case 'l':
      data->opt.l = 1;
      break;
    case 'n':
      data->opt.n = 1;
      break;
    case 'h':
      data->opt.h = 1;
      break;
    case 's':
      data->opt.s = 1;
      break;
    case 'f':
      data->opt.f = 1;
      break;
    case 'o':
      data->opt.o = 1;
      break;
    default:
      data->invalid = UNKNOWN_OPT;
      break;
  }
}

void alloc_filepaths(data_t *data, int argc, char **argv) {
  if (!data->opt.e && !data->opt.f) {
    alloc_parser(data, *(argv + 1));
    optind++;
  }

  for (int index = optind; index < argc && !data->invalid; index++) {
    data->file_paths =
        realloc(data->file_paths, sizeof(char *) * (data->num_files + 1));
    if (!data->file_paths) {
      data->invalid = FILEPATH_ALLOC;
    }

    if (!data->invalid) {
      data->file_paths[data->num_files] = strdup(argv[index]);
      if (!data->file_paths[data->num_files]) {
        data->invalid = FILEPATH_ALLOC;
      }
    }

    data->num_files++;
  }
}

char *strdup(const char *str) {
  size_t length = strlen(str) + 1;
  char *new_str = malloc(length);
  if (new_str) {
    memcpy(new_str, str, length);
  }

  return new_str;
}
