
#include "grep_flags.h"

void grep(data_t *data, int file_count) {
  FILE *file = fopen(data->file_paths[file_count], "r");
  if (file) {
    reader(file, data);

    if (data->value_flags.count_matchs > 0 && data->opt.l) {
      printf("%s", data->file_paths[file_count]);
    }

    fclose(file);
  } else {
    printf("ERROR: no file\n");  // put it in a separate function later
  }
}

void reader(FILE *file, data_t *data) {
  char *line = NULL;
  size_t len = 0;
  data->value_flags.count_line = 0;
  data->value_flags.count_matchs = 0;
  int tmp_line = 0;

  while ((tmp_line = getline(&line, &len, file)) != -1) {
    outline(data, line);
  }

  if (data->opt.c) {
    printf("%d", data->value_flags.count_line);
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
      reti = regcomp(&data->regex, data->patterns[i], 0);
    }

    if (reti) {
      fprintf(stderr, "Could not compile regex\n");  // temporary check
      exit(1);
    }

    data->value_flags.match = matchs(data, line, reti);

    if (!data->opt.l) {
      if (data->value_flags.match && !data->opt.v && !data->opt.c) {
        printf("%s", line);
      } else if (!data->value_flags.match && data->opt.v) {
        printf("%s", line);
      } else if (data->value_flags.match && data->opt.c) {
        data->value_flags.count_line++;
      }
    }

    if (data->value_flags.match) {
      data->value_flags.count_matchs++;
    }

    regfree(&data->regex);
  }
}
