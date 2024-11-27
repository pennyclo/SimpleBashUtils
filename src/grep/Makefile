#===============COMPILER===============

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11
# CFLAGS = -Wall -Wextra -pedantic -std=c11 -g

#======================================

#===============FILES==================

ALL_FILES = *.c *.h
EXCRETION = s21_grep

#======================================

#===============PATHS==================

TESTS_PATH = tests/
VALTEST_PATH = -noe "\)" test_files/test_5_grep.txt

#======================================

#==============TESTS_CHECK=============

CPPFLAGS = —enable=all —suppress=missingIncludeSystem
CLANGFLAGS_N = -style=Google -n

#======================================

cpp:
	cppcheck $(CPPFLAGS) *.c

clang_check:
	clang-format $(CLANGFLAGS_N) $(ALL_FILES)

#================TESTS_VAL=================

VALFLAGS = --tool=memcheck --leak-check=yes
PATTERN = 
FLAGS_TEST = 

#======================================

val: s21_grep
	valgrind $(VALFLAGS)  ./$(EXCRETION) $(FLAGS_TEST) $(PATTERN) $(VALTEST_PATH)

#================TESTS_FILES=================

#test:
#	bash $(TESTS_PATH)grep_tests.sh

test:
	bash tests.sh

test_leaks:
	bash test_leaks.sh
#======================================


#===============BUILD==================

all: rebuild

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

clean: clean_excr clean.o

clean_excr: 
	rm -f $(EXCRETION)

clean.o:
	rm -f *.o *.log *.txt

#======================================


#===============PHONY==================

.PHONY: s21_grep clean clean_excr clean.o

#======================================
