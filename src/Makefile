SHELL = /bin/sh

CC=gcc
FLAGS=-Wall -Wextra -Werror -std=c11
CFLAGS:=$(FLAGS)
GCOV:=$(FLAGS) --coverage
SRC=$(wildcard *.c)
HEADERS=$(wildcard *.h)
OBJS=$(patsubst %.c,%.o,$(SRC))
TEST_SRC=$(wildcard tests/*.c)
TEST_OBJS=$(patsubst %.c,%.o,$(wildcard tests/*.c))
BUILD=build/
NAME=s21_maze

.PHONY: all install uninstall clean tests gcov_report ext1_flag ext2_flag base_flag

all: $(BUILD)$(NAME)

install: $(BUILD)$(NAME)

uninstall: clean

clean:
	-rm -rf $(BUILD)*.* $(BUILD)s21_maze *.o s21_maze tests/*.o tests/test *.gcno *.gcda *.info test

tests: $(OBJS) $(TEST_OBJS)
	rm -f main.o
	$(CC) $(CFLAGS) *.o $(TEST_OBJS) -o test -lcheck -lm -lsubunit -Lbuild
	-clear
	./test

$(BUILD)$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	make

$(OBJS): $(SRC)

gcov_report: clean ext1_flag $(OBJS) base_flag $(TEST_OBJS) ext2_flag
	-rm -rf report/ main.o
	$(CC) $(CFLAGS) *.o $(TEST_OBJS) -o test -lcheck -lm -lsubunit -Lbuild
	./test
	-lcov --rc lcov_branch_coverage=1 -t "s21_maze_report" -o s21_maze_report.info -c -d .
	-genhtml --rc lcov_branch_coverage=1 -o report s21_maze_report.info
	-make clean

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