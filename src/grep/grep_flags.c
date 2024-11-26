#include "grep_flags.h"

void grep(data_t *data) {
  FILE *file = fopen(data->file_paths[data->value_flags.count_files], "r");
  if (file) {
    reader(file, data);

    fclose(file);
  } else {
    if (!data->opt.s) {
      fprintf(stderr, "grep: %s: No such file or directory\n",
              data->file_paths[data->value_flags.count_files]);
    }
    // data->invalid = NO_FILE;  // put it in a separate function later
  }
}

void reader(FILE *file, data_t *data) {
  char *line = NULL;
  size_t len = 0;
  data->num_lines = 1;
  data->value_flags.count_line = 0;
  data->value_flags.count_matchs = 0;
  int tmp_line = 0;

  while ((tmp_line = getline(&line, &len, file)) != -1) {
    outline(data, line, value_match(data, line));
  }

  flags_l_c(data);

  free(line);
}

int value_match(data_t *data, const char *line) {
  int matchs_count = 0;

  for (int i = 0; i < data->num_pattern && !matchs_count && !data->invalid;
       i++) {
    compiling_reg(data, i);

    if (!data->invalid) {
      matchs_count += matchs(data, line);

      if (matchs_count) {
        data->value_flags.count_matchs++;
        data->value_flags.valid_all_matchs = 1;
      }
    }

    regfree(&data->regex);
  }

  return matchs_count;
}

void outline(data_t *data, const char *line, int matchs_count) {
  if (!data->opt.v) {
    if (matchs_count) {
      value_out(data, line);
    }
  } else {
    if (!matchs_count) {
      value_out(data, line);
    }
  }

  data->num_lines++;
}

void value_o_flag(data_t *data, const char *line) {
  size_t len_patterns = 0;
  regmatch_t pmatch[1];

  for (int i = 0; i < data->num_pattern; i++) {
    len_patterns += strlen(data->patterns[i]);
    if (i < data->num_pattern - 1) {
      len_patterns += 1;
    }
  }

  char *patterns_line = malloc(len_patterns + 1);
  if (patterns_line == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    data->invalid = ALLOC_PATTERN;
    return;
  }

  patterns_line[0] = '\0';

  for (int i = 0; i < data->num_pattern; i++) {
    strcat(patterns_line, data->patterns[i]);
    if (i < data->num_pattern - 1) {
      strcat(patterns_line, "|");
    }
  }

  const char *line_reg = line;
  int find_match = 0;
  int start = 0;

  compiling_reg_o(data, patterns_line);

  while ((find_match = regexec(&data->regex, line_reg + start, 1, pmatch, 0)) ==
         0) {
    if (!data->opt.v) {
      value_h_flag(data);

      value_n_flag(data);

      printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
             line_reg + start + pmatch[0].rm_so);
    }
    start += pmatch[0].rm_eo;
  }

  if (find_match != REG_NOMATCH) {
    fprintf(stderr, "Regex match failed\n");
  }

  regfree(&data->regex);
  free(patterns_line);
}

void compiling_reg(data_t *data, int count_pattern) {
  int comp_reg = 0;

  if (data->opt.i) {
    comp_reg = regcomp(&data->regex, data->patterns[count_pattern], REG_ICASE);
  } else {
    comp_reg =
        regcomp(&data->regex, data->patterns[count_pattern], REG_NEWLINE);
  }

  if (comp_reg) {
    fprintf(stderr, "Could not compile regex\n");  // temporary check
    data->invalid = COMPILE_REG;
  }
}

void compiling_reg_o(data_t *data, char *patterns) {
  int comp_reg = 0;

  if (data->opt.i) {
    comp_reg = regcomp(&data->regex, patterns, REG_ICASE);
  } else {
    comp_reg = regcomp(&data->regex, patterns, REG_EXTENDED);
  }

  if (comp_reg) {
    fprintf(stderr, "Could not compile regex\n");  // temporary check
    data->invalid = COMPILE_REG;
  }
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

void value_out(data_t *data, const char *line) {
  if (data->opt.c || data->opt.l) {
    data->value_flags.count_line++;
  } else {
    if (data->opt.o) {
      value_o_flag(data, line);

    } else {
      value_h_flag(data);

      value_n_flag(data);

      output(line);
    }
  }
}

void output(const char *line) {
  if (line[strlen(line) - 1] == '\n') {
    printf("%s", line);
  } else {
    printf("%s\n", line);
  }
}

void value_h_flag(data_t *data) {
  if (data->num_files > 1 && !data->opt.h) {
    printf("%s:", data->file_paths[data->value_flags.count_files]);
  }
}

void value_n_flag(data_t *data) {
  if (data->opt.n) {
    printf("%d:", data->num_lines);
  }
}

void value_c_flag(data_t *data) {
  if (data->num_files > 1) {
    if (!data->opt.h) {
      printf("%s:%d\n", data->file_paths[data->value_flags.count_files],
             data->value_flags.count_line);
    } else {
      printf("%d\n", data->value_flags.count_line);
    }
  } else if (data->value_flags.count_matchs > 0) {
    printf("%d\n", data->value_flags.count_line);
  }
}

void flags_l_c(data_t *data) {
  if (!data->opt.v) {
    if (data->value_flags.valid_all_matchs) {
      if (data->value_flags.count_line && data->opt.l) {
        printf("%s\n", data->file_paths[data->value_flags.count_files]);
      } else if (data->opt.c && !data->opt.l) {
        value_c_flag(data);
      }
    }
  } else {
    if (data->value_flags.count_line && data->opt.l) {
      printf("%s\n", data->file_paths[data->value_flags.count_files]);
    } else if (data->opt.c && !data->opt.l) {
      value_c_flag(data);
    }
  }
}