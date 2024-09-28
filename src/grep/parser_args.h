#ifndef PARCER_ARGS_H
#define PARCER_ARGS_H

#include <getopt.h>
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

} errors_t;

typedef struct {
  options_t opt;
  errors_t invalid;
  int num_files;
  char* pattern;
  char** file_paths;
  int num_lines;
} data_t;

data_t parser(int argc, char** argv);
void switch_parser(int opt, data_t* data);
void alloc_filepaths(data_t* data, int argc, char** argv);
char* strdup(const char* str);

#endif