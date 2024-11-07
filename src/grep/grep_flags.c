#include "grep_flags.h"

void grep(data_t *data) {
  FILE *file = fopen(data->file_paths[data->value_flags.count_files], "r");
  if (file) {
    reader(file, data);

    if (data->value_flags.count_matchs > 0 && data->opt.l) {
      printf("%s\n", data->file_paths[data->value_flags.count_files]);
    }

    if (data->opt.c) {
      if (data->value_flags.count_matchs > 0 && data->num_files > 1) {
        printf("%s:%d\n", data->file_paths[data->value_flags.count_files],
               data->value_flags.count_line);
      } else if (data->value_flags.count_matchs > 0) {
        printf("%d\n", data->value_flags.count_line);
      }
    }

    fclose(file);
  } else {
    printf("ERROR: no file\n");  // put it in a separate function later
  }
}

void reader(FILE *file, data_t *data) {
  char *line = NULL;
  size_t len = 0;
  data->num_lines = 1;
  data->value_flags.count_line = 0;
  int tmp_line = 0;

  while ((tmp_line = getline(&line, &len, file)) != -1) {
    outline(data, line);
  }

  free(line);
}

int matchs(data_t *data, char *line, int reti) {
  int match = 0;

  reti = regexec(&data->regex, line, 0, NULL, 0);
  if (!reti) {
    match = 1;
  }

  return match;
}

void outline(data_t *data, char *line) {
  data->value_flags.match = 0;

  for (int i = 0; i < data->num_pattern && !data->value_flags.match; i++) {
    int reti = 0;

    if (data->opt.i) {
      reti = regcomp(&data->regex, data->patterns[i], REG_ICASE);
    } else {
      reti = regcomp(&data->regex, data->patterns[i], REG_EXTENDED);
    }

    if (reti) {
      fprintf(stderr, "Could not compile regex\n");  // temporary check
      exit(1);
    }

    data->value_flags.match += matchs(data, line, reti);

    if (data->value_flags.match) {
      data->value_flags.count_matchs++;
    }

    regfree(&data->regex);
  }

  if (!data->opt.l) {
    if (data->value_flags.match && data->opt.c &&
        data->value_flags.valid_flags) {
      data->value_flags.count_line++;
    } else if (!data->value_flags.match && data->opt.v &&
               data->value_flags.valid_flags) {
      if (data->num_files > 1 && !data->opt.h) {
        printf("%s:", data->file_paths[data->value_flags.count_files]);
      }

      if (data->opt.n) {
        printf("%d:", data->num_lines);
      }

      if (line[strlen(line) - 1] == '\n') {
        printf("%s", line);
      } else {
        printf("%s\n", line);
      }

    } else if (data->value_flags.match && !data->opt.v &&
               data->value_flags.valid_flags) {
      if (data->num_files > 1 && !data->opt.h) {
        printf("%s:", data->file_paths[data->value_flags.count_files]);
      }

      if (data->opt.n) {
        printf("%d:", data->num_lines);
      }

      if (line[strlen(line) - 1] == '\n') {
        printf("%s", line);
      } else {
        printf("%s\n", line);
      }
    }
  }

  data->num_lines++;
}
