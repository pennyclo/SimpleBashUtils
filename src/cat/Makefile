SHELL := /bin/bash
CC = gcc
CFLAGS =-Wextra -Wall -pedantic -std=c11
EXCRETION = s21_cat
FLAGS_TEST = -n -b -s -v -T -E
TEST_PATH = tests/tests_files/test_1_cat.txt tests/tests_files/nofile.txt tests/tests_files/test_2_cat.txt
FILE = test/test.txt
ALL_FILES = *.c *.h

all: s21_cat clean.o

install: s21_cat

s21_cat: main parser_args cat_flags
	$(CC) $(CFLAGS) main.o parser_args.o cat_flags.o -o s21_cat

main:
	$(CC) $(CFLAGS) -c main.c

parser_args:
	$(CC) $(CFLAGS) -c parser_args.c

cat_flags:
	$(CC) $(CFLAGS) -c cat_flags.c

clean: clean.o clean.log
	rm -rf $(EXCRETION) analysis/*

clean.o:
	rm -rf *.o

clean.log:
	rm -rf tests/tests_log/*

rebuild: clean install

val: s21_cat
	valgrind --tool=memcheck --leak-check=yes  ./$(EXCRETION) $(FLAGS_TEST) $(TEST_PATH)

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h


test:
	bash tests_cat.sh

clang_check:
	clang-format -style=Google -n $(ALL_FILES)
