#==================================COMPILER====================================

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11

#==============================================================================

#==================================FILES=======================================

ALL_FILES = *.c *.h
EXECUTABLE = s21_grep
SOURCES = main.c parser_args.c grep_flags.c
OBJECTS = $(SOURCES:.c=.o)

#==============================================================================

#================================TESTS_CHECK===================================

CPPFLAGS = --enable=all --suppress=missingIncludeSystem
CLANGFLAGS_N = -style=Google -n

#==============================================================================

cpp:
	cppcheck $(CPPFLAGS) $(ALL_FILES)

clang_check:
	clang-format $(CLANGFLAGS_N) $(ALL_FILES)

#==============================================================================

#=================================TESTS_VAL====================================

VALFLAGS = --tool=memcheck --leak-check=yes --track-origins=yes
override PATTERN ?=
override FLAGS_TEST ?=
override VALTEST_PATH ?=

#==============================================================================

val: $(EXECUTABLE)
	valgrind $(VALFLAGS) ./$(EXECUTABLE) $(FLAGS_TEST) $(PATTERN) $(VALTEST_PATH)

#==============================================================================

#================================TESTS_FILES===================================

test:
	bash tests/tests.sh

test_leaks:
	bash tests/test_leaks.sh

#==============================================================================

#===================================BUILD======================================

all: rebuild

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

rebuild: clean $(EXECUTABLE)

#==============================================================================

#===================================CLEAN======================================

clean: clean.o
	rm -f $(OBJECTS) $(EXECUTABLE)

clean.o:
	rm -f *.log *.txt

#==============================================================================

#===================================PHONY======================================

.PHONY: all clean rebuild s21_grep

#==============================================================================
