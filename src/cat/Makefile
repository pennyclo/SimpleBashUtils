SHELL := /bin/bash
CC = gcc
CFLAGS =-Wextra -Wall -std=c11 -g
EXCRETION = s21_cat
FLAGS_TEST = -n
TEST_PATH = tests/tests_files/test_1_cat.txt tests/tests_files/nofile.txt tests/tests_files/test_2_cat.txt
FILE = test/test.txt

all:

install: s21_cat

s21_cat: main parser_args cat_flags
	$(CC) $(CFLAGS) cat_main.o parser_args.o cat_flags.o -o s21_cat

main:
	$(CC) $(CFLAGS) -c cat_main.c

parser_args:
	$(CC) $(CFLAGS) -c parser_args.c

cat_flags:
	$(CC) $(CFLAGS) -c cat_flags.c

clean: clean.o
	rm -rf $(EXCRETION)

clean.o:
	rm -rf *.o

rebuild: clean install

val: s21_cat
	valgrind --tool=memcheck --leak-check=yes  ./$(EXCRETION) $(FLAGS_TEST) $(TEST_PATH)

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c


test:
	bash tests_cat.sh > 3.txt
	cat 3.txt
	rm 3.txt
	# bash analysis_test_cat.sh