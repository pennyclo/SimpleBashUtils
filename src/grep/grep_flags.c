#define _GNU_SOURCE

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
  size_t memline = 0;
  int count_line = 0;

  count_line = getline(&line, &memline, file);

  while (count_line != -1) {
    if (data->opt.e) {
      e_flag(data, line);
    }
    count_line = getline(&line, &memline, file);
  }

  free(line);
}

int matchs(data_t *data, char *line) {
  int match = 0;
  regex_t regex;
  int reti = regcomp(&regex, data->pattern, 0);

  if (reti) {
    fprintf(stderr, "Could not compile regex\n");  // temporary check
    exit(1);
  }

  reti = regexec(&regex, line, 0, NULL, 0);
  if (!reti) {
    match = 1;
  }

  regfree(&regex);

  return match;
}

// void outline(char *line, size_t count_char) {
//   for (int i = 0; i < (int)count_char; i++) {
//     printf("%c", *(line + i));
//   }
// }

void e_flag(data_t *data, char *line) {
  int match = matchs(data, line);
  if (match) {
    printf("%s", line);
  }
}