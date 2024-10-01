#include "parser_args.h"

data_t parser(int argc, char **argv) {
  data_t data = {.opt = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, .num_pattern = 0};
  data.invalid = VALID;
  int opt = 0;

  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch_parser(opt, &data);

    if (data.opt.f) {
      parser_f_flags(&data, optarg);
    }
    if (data.opt.e) {
      alloc_parser(&data, optarg);
      data.opt.e = 0;
    }
  }

  alloc_filepaths(&data, argc, argv);

  return data;
}

void parser_f_flags(data_t *data, char *patterns) {
  char *line_ptrn = NULL;
  size_t len_ptrn = 0;
  int count_line_ptrn = 0;

  FILE *file_patterns = fopen(patterns, "r");

  if (file_patterns) {
    while ((count_line_ptrn = getline(&line_ptrn, &len_ptrn, file_patterns)) !=
           -1) {
      move_line(line_ptrn);
      alloc_parser(data, line_ptrn);
    }
  }

  if (file_patterns) {
    fclose(file_patterns);
    free(line_ptrn);
  }
}

void alloc_parser(data_t *data, char *optarg) {
  data->patterns =
      realloc(data->patterns, sizeof(char *) * (data->num_pattern + 1));
  if (!data->patterns) {
    data->invalid = FILEPATH_ALLOC;  // rename later
  }

  if (!data->invalid && optarg) {
    data->patterns[data->num_pattern] = strdup(optarg);
    if (!data->patterns[data->num_pattern]) {
      data->invalid = FILEPATH_ALLOC;
    }
  }

  data->num_pattern++;
}

void switch_parser(int opt, data_t *data) {
  data->value_flags.valid_flags = 0;

  switch (opt) {
    case 'e':
      data->opt.e = 1;
      data->value_flags.valid_flags = 1;
      break;
    case 'i':
      data->opt.i = 1;
      data->value_flags.valid_flags = 1;
      break;
    case 'v':
      data->opt.v = 1;
      data->value_flags.valid_flags = 1;
      break;
    case 'c':
      data->opt.c = 1;
      data->value_flags.valid_flags = 1;
      break;
    case 'l':
      data->opt.l = 1;
      data->value_flags.valid_flags = 1;
      break;
    case 'n':
      data->opt.n = 1;
      data->value_flags.valid_flags = 1;
      break;
    case 'h':
      data->opt.h = 1;
      data->value_flags.valid_flags = 1;
      break;
    case 's':
      data->opt.s = 1;
      data->value_flags.valid_flags = 1;
      break;
    case 'f':
      data->opt.f = 1;
      data->value_flags.valid_flags = 1;
      break;
    case 'o':
      data->opt.o = 1;
      data->value_flags.valid_flags = 1;
      break;
    default:
      data->invalid = UNKNOWN_OPT;
      break;
  }
}

void alloc_filepaths(data_t *data, int argc, char **argv) {
  if (!data->value_flags.valid_flags) {
    alloc_parser(data, *(argv + 1));
    optind++;
  } else if (!data->opt.e && !data->opt.f) {
    alloc_parser(data, argv[optind]);
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

void move_line(char *line) {
  size_t len = strlen(line);
  if (len > 0 && line[len - 1] == '\n') {
    line[len - 1] = '\0';
  }
}