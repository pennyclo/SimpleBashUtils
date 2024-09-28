#===============COMPILER===============

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11

#======================================

#===============FILES==================

ALL_FILES = *.c *.h
EXCRETION = s21_grep

#======================================

#===============PATHS==================

TESTS_PATH = tests/
VALTEST_PATH = Makefile

#======================================

#==============TESTS_CHECK=============

CPPFLAGS = —enable=all —suppress=missingIncludeSystem
CLANGFLAGS_N = -style=Google -n
CLANGFLAGS_I = -style=Google -i

#======================================

cpp:
	cppcheck $(CPPFLAGS) *.c

clang_check:
	clang-format $(CLANGFLAGS_N) $(ALL_FILES)

clang_edit:
	clang-format $(CLANGFLAGS_I) $(ALL_FILES)

#================TESTS=================

VALFLAGS = --tool=memcheck --leak-check=yes
PATTERN = s21_grep
FLAGS_TEST = -e

#======================================

val: 
	valgrind $(VALFLAGS)  ./$(EXCRETION) $(FLAGS_TEST) $(PATTERN) $(VALTEST_PATH)

test:
	bash $(TESTS_PATH)tests.sh

test_leaks:
	bash $(TESTS_PATH)test_leaks.sh

#===============BUILD==================

all: rebuild clean.o

s21_grep: install

install: main parser flags
	$(CC) $(CFLAGS) main.o parser_args.o grep_flags.o -o s21_grep

main:
	$(CC) $(CFLAGS) -c main.c

parser:
	$(CC) $(CFLAGS) -c parser_args.c

flags:
	$(CC) $(CFLAGS) -c grep_flags.c

rebuild: clean install

#======================================

#===============CLEAN==================

clean: clean.o
	rm $(EXCRETION)

clean.o:
	rm *.o

#======================================
