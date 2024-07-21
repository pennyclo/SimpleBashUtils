CC = gcc
CFLAGS = -Werror -Wextra -Wall -std=c11
BUILD = /build/
DIRCAT = /cat_util/

all:

install: cat_main

cat_main: cat
	$(CC) $(CFLAGS) main.c cat.o -o $(BUILD)cat_util

cat:
	$(CC) $(CFLAGS) -c $(DIRCAT)cat.c

clean:
	rm -rf $(BUILD)* *.o

rebuild: clean install