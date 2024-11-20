#ifndef PARCER_ARGS_H
#define PARCER_ARGS_H

#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e, i, v, c, l, n, h, s, f,
      o;  //| 1 | -e | Шаблон. |
          //| 2 | -i | Игнорирует различия регистра.  |
          //| 3 | -v | Инвертирует смысл поиска соответствий. |
          //| 4 | -c | Выводит только количество совпадающих строк. |
          //| 5 | -l | Выводит только совпадающие файлы.  |
          //| 6 | -n | Предваряет каждую строку вывода номером строки из файла
          // ввода. | | 7 | -h | Выводит совпадающие строки, не предваряя их
          // именами файлов. | | 8 | -s | Подавляет сообщения об ошибках о
          // несуществующих или нечитаемых файлах. | | 9 | -f file | Получает
          // регулярные выражения из файла. | | 10 | -o | Печатает только
          // совпадающие (непустые) части совпавшей строки. |

} options_t;

typedef enum {
  VALID,
  UNKNOWN_OPT,
  FILEPATH_ALLOC,
  NO_FILE,
  COMPILE_REG,
} errors_t;

typedef struct {
  int valid_all_matchs;
  int valid_flags;
  int count_matchs;
  int count_line;
  int count_files;
} value_flag_t;

typedef struct {
  options_t opt;
  errors_t invalid;
  regex_t regex;
  value_flag_t value_flags;
  int num_files;
  int num_pattern;
  int num_lines;
  char** patterns;
  char** file_paths;
} data_t;

data_t parser(int argc, char** argv);
void parser_f_flags(data_t* data, char* patterns);
void move_line(char* line);
void switch_parser(int opt, data_t* data);
void alloc_filepaths(data_t* data, int argc, char** argv);
void alloc_parser(data_t* data, char* optarg);
char* strdup(const char* str);

#endif