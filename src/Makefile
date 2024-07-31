CC = gcc
CFLAGS = -Wextra -Wall -std=c11
BUILD = ../build/
DIRCAT = cat_util/
EXCRETION = main
FLAGS_TEST = -b
TEST_PATH = Makefile Makefile

all:

install: cat_main



cat_main: cat
	$(CC) $(CFLAGS) main.c cat.o -o $(BUILD)cat_util

main:
	$(CC) $(CFLAGS) main.c -o $(BUILD)main

cat:
	$(CC) $(CFLAGS) -c $(DIRCAT)cat.c

clean:
	rm -rf $(BUILD)* *.o

rebuild: clean install

val: main
	valgrind --tool=memcheck --leak-check=yes  ./$(BUILD)$(EXCRETION) $(FLAGS_TEST) $(TEST_PATH)

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c