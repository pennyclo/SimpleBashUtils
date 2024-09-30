
#include "grep_flags.h"

void grep(data_t *data, int file_count) {
  FILE *file = fopen(data->file_paths[file_count], "r");
  if (file) {
    reader(file, data);

    fclose(file);
  } else {
    printf("ERROR: no file\n");  // put it in a separate function later
  }
}

void reader(FILE *file, data_t *data) {
  char *line = NULL;
  size_t len = 0;
  int count_line = 0;

  while ((count_line = getline(&line, &len, file)) != -1) {
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
  int match = 0;

  for (int i = 0; i < data->num_pattern && !match; i++) {
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

    match = matchs(data, line, reti);

    if (match) {
      printf("%s", line);
    }
    regfree(&data->regex);
  }
}
