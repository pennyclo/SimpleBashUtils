#include "grep_flags.h"

void grep(data_t *data) {
  FILE *file = fopen(data->file_paths[data->value_flags.count_files], "r");
  if (file) {
    reader(file, data);

    if (data->value_flags.count_matchs > 0 && data->opt.l) {
      printf("%s\n", data->file_paths[data->value_flags.count_files]);
    } else if (data->opt.c) {
      if (data->value_flags.count_matchs > 0 && data->num_files > 1) {
        printf("%s:%d\n", data->file_paths[data->value_flags.count_files],
               data->value_flags.count_line);
      } else if (data->value_flags.count_matchs > 0) {
        printf("%d\n", data->value_flags.count_line);
      }
    }

    fclose(file);
  } else {
    fprintf(stderr, "grep: %s: No such file or directory\n",
            data->file_paths[data->value_flags.count_files]);
    // data->invalid = NO_FILE;  // put it in a separate function later
  }
}

void reader(FILE *file, data_t *data) {
  char *line = NULL;
  size_t len = 0;
  data->num_lines = 1;
  data->value_flags.count_line = 0;
  int tmp_line = 0;

  while ((tmp_line = getline(&line, &len, file)) != -1) {
    outline(data, line, value_match(data, line));
  }

  free(line);
}

void outline(data_t *data, const char *line, int matchs_count) {
  if (!data->opt.l && !data->opt.o) {  // ДЕКОМПОЗИЦИЯ!!!
    if (matchs_count) {
      if (!data->opt.v) {
        if (data->opt.c) {
          data->value_flags.count_line++;
        } else {
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
    } else {
      if (data->opt.v) {
        if (data->opt.c) {
          data->value_flags.count_line++;
        } else {
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
    }
  } else if (data->opt.o) {
    for (int i = 0; line[i] != '\0'; i++) {
      for (int tmp = 0; tmp < data->num_pattern; tmp++) {
        char *result = strstr(line + i, data->patterns[tmp]);
        if (result != NULL && result == line + i) {
          if (data->num_files > 1 && !data->opt.h) {
            printf("%s:", data->file_paths[data->value_flags.count_files]);
          }
          if (data->opt.n) {
            printf("%d:", data->num_lines);
          }

          printf("%s\n", data->patterns[tmp]);
        }
      }
    }
  }

  data->num_lines++;
}

int value_match(data_t *data, const char *line) {
  int matchs_count = 0;

  for (int i = 0; i < data->num_pattern && !matchs_count && !data->invalid;
       i++) {
    int comp_reg = 0;

    if (data->opt.i) {
      comp_reg = regcomp(&data->regex, data->patterns[i], REG_ICASE);
    } else {
      comp_reg = regcomp(&data->regex, data->patterns[i], REG_EXTENDED);
    }

    if (comp_reg) {
      fprintf(stderr, "Could not compile regex\n");  // temporary check
      data->invalid = COMPILE_REG;
    }

    if (!data->invalid) {
      matchs_count += matchs(data, line);

      if (matchs_count) {
        data->value_flags.count_matchs++;
      }
    }

    regfree(&data->regex);
  }

  return matchs_count;
}

int matchs(data_t *data, const char *line) {
  int match = 0;
  int value_match = 0;

  value_match = regexec(&data->regex, line, 0, NULL, 0);
  if (!value_match) {
    match = 1;
  } else if (value_match != REG_NOMATCH) {
    fprintf(stderr, "Regex match failed\n");
  }

  return match;
}
