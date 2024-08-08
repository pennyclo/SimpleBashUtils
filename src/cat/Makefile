CC = gcc
CFLAGS = -Werror -Wextra -Wall -std=c11
EXCRETION = s21_cat
FLAGS_TEST = -v
TEST_PATH = test/test test/test.txt 

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

clean:
	rm -rf s21_cat *.o

rebuild: clean install

val: s21_cat
	valgrind --tool=memcheck --leak-check=yes  ./$(EXCRETION) $(FLAGS_TEST) $(TEST_PATH)

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c