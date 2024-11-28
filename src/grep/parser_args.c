#include "parser_args.h"

data_t parser(int argc, char **argv) {
  data_t data = {0};
  data.invalid = VALID;
  data.patterns = NULL;
  int opt = 0;

  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch_parser(opt, &data);
    if (data.opt.f && optarg) {
      parser_f_flags(&data, optarg);
    }

    if (data.opt.e && optarg) {
      alloc_parser(&data, optarg);
    }
  }

  if (!data.invalid) {
    alloc_filepaths(&data, argc, argv);
  }

  return data;
}

void parser_f_flags(data_t *data, const char *patterns) {
  char *line_ptrn = NULL;
  size_t len_ptrn = 0;

  FILE *file_patterns = fopen(patterns, "r");

  if (file_patterns) {
    int count_line_ptrn = 0;

    while ((count_line_ptrn = getline(&line_ptrn, &len_ptrn, file_patterns)) !=
           -1) {
      move_line(line_ptrn);
      alloc_parser(data, line_ptrn);
    }
  } else {
    fprintf(stderr, "grep: %s: No such file or directory\n", patterns);
    data->invalid = NO_FILE;
  }

  if (file_patterns) {
    free(line_ptrn);
    fclose(file_patterns);
  }
}

void alloc_parser(data_t *data, const char *optarg) {
  data->patterns =
      realloc(data->patterns, sizeof(char *) * (data->num_pattern + 1));
  if (!data->patterns) {
    data->invalid = ALLOC_PATTERN;
  }

  if (!data->invalid && optarg) {
    data->patterns[data->num_pattern] = strdup(optarg);
    if (!data->patterns[data->num_pattern]) {
      data->invalid = ALLOC_PATTERN;
    }
  }

  data->num_pattern++;
}

void switch_parser(int opt, data_t *data) {
  data->valid_flags = 0;

  switch (opt) {
    case 'e':
      data->opt.e = 1;
      data->valid_flags = 1;
      break;
    case 'i':
      data->opt.i = 1;
      data->valid_flags = 1;
      break;
    case 'v':
      data->opt.v = 1;
      data->valid_flags = 1;
      break;
    case 'c':
      data->opt.c = 1;
      data->valid_flags = 1;
      break;
    case 'l':
      data->opt.l = 1;
      data->valid_flags = 1;
      break;
    case 'n':
      data->opt.n = 1;
      data->valid_flags = 1;
      break;
    case 'h':
      data->opt.h = 1;
      data->valid_flags = 1;
      break;
    case 's':
      data->opt.s = 1;
      data->valid_flags = 1;
      break;
    case 'f':
      data->opt.f = 1;
      data->valid_flags = 1;
      break;
    case 'o':
      data->opt.o = 1;
      data->valid_flags = 1;
      break;
    default:
      data->invalid = UNKNOWN_OPT;
      break;
  }
}

void alloc_filepaths(data_t *data, int argc, char **argv) {
  if (!data->valid_flags) {
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

char *alloc_patterns_o(data_t *data, size_t len_patterns) {
  char *patterns_line = malloc(len_patterns + 1);

  if (patterns_line) {
    patterns_line[0] = '\0';
  } else {
    fprintf(stderr, "Memory allocation failed\n");
    data->invalid = ALLOC_PATTERN;
  }

  return patterns_line;
}
