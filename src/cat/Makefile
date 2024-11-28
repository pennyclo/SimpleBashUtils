#==================================COMPILER====================================

CC = gcc
CFLAGS = -Werror -Wextra -Wall -pedantic -std=c11

#==============================================================================

#===================================FILES======================================

ALL_FILES = *.c *.h
EXECUTABLE = s21_cat
SOURCES = main.c cat_flags.c parser_args.c
OBJECTS = $(SOURCES:.c=.o)
TESTS = tests/tests_cat.sh

#==============================================================================

#================================TESTS_CHECK===================================

VAL_FLAGS = --tool=memcheck --leak-check=yes --track-origins=yes
FLAGS_TEST ?= 
TEST_PATH ?=  
FILE = test/test.txt

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

clean: clean.o clean.log
	rm -rf $(EXECUTABLE) analysis/*

clean.o:
	rm -rf *.o

clean.log:
	rm -rf tests/tests_log/*

#==============================================================================

#=================================TESTS_VAL====================================

val: $(EXECUTABLE)
	valgrind $(VAL_FLAGS) ./$(EXECUTABLE) $(FLAGS_TEST) $(TEST_PATH)

#==============================================================================

#================================TESTS_CHECK===================================

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem $(ALL_FILES)

test:
	bash $(TESTS)

clang_check:
	clang-format -style=Google -n $(ALL_FILES)

#==============================================================================
