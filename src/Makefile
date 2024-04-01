SHELL = /bin/sh

CC=gcc
FLAGS=-Wall -Wextra -Werror -std=c11
CFLAGS:=$(FLAGS)
GCOV:=$(FLAGS) --coverage
SRC=maze.c #$(wildcard *.c)
HEADERS=maze.h
OBJS=$(patsubst %.c,%.o,$(SRC))
TEST_SRC=$(wildcard tests/*.c)
TEST_OBJS=$(patsubst %.c,%.o,$(wildcard tests/*.c))
BUILD=build/
NAME=s21_maze

.PHONY: all install uninstall clean test gcov_report ext1_flag ext2_flag base_flag

all: $(BUILD)$(NAME)

install: all
	sudo cp $(BUILD)$(NAME) /usr/bin/$(NAME)

uninstall:
	sudo rm -f /usr/bin/$(NAME)

clean:
	-rm -rf $(BUILD)*.*

tests: # ToDo
	#$(CC) $(CFLAGS) $^ -o test -lcheck -lm -lsubunit -Lbuild -l:XXXXXX.a
	#-clear
	#-./test

$(BUILD)$(NAME): $(BUILD)$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	$@
	make clean

$(BUILD)$(OBJS): $(SRC)
	$(CC) $(CFLAGS) -c $^ -o $@

# ToDo
#gcov_report: clean ext1_flag build/s21_tetris.a base_flag build/s21_test_lib.o ext2_flag test
#	-rm -rf report/
#	-lcov --rc lcov_branch_coverage=1 -t "s21_maze_report" -o s21_maze_report.info -c -d .
#	-genhtml --rc lcov_branch_coverage=1 -o report s21_maze_report.info
#	-make clean

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem --check-config $(SRC) $(HEADERS)
	@cp ../materials/linters/.clang-format .
	clang-format -n $(SRC) $(HEADERS)

ext1_flag:
	$(eval CFLAGS:=$(GCOV))
ext2_flag:
	$(eval CFLAGS:=$(GCOV))
base_flag:
	$(eval CFLAGS:=$(FLAGS))