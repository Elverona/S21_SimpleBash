SHELL := /bin/bash
CC = gcc
TEST_FILE = test_cat.txt
CFLAGS = -Wall -Werror -Wextra -std=c11
CHECK = 2>&1 valgrind --tool=memcheck --leak-check=yes


all: s21_cat work_test

s21_cat: clean
	$(CC) $(CFLAGS) cat.c -o s21_cat

work_test:
	-diff <(./s21_cat $(TEST_FILE)) <(cat $(TEST_FILE))
	-diff <(./s21_cat -b $(TEST_FILE)) <(cat -b $(TEST_FILE))
	-diff <(./s21_cat -e $(TEST_FILE)) <(cat -e $(TEST_FILE))
	-diff <(./s21_cat -n $(TEST_FILE)) <(cat -n $(TEST_FILE))
	-diff <(./s21_cat -s $(TEST_FILE)) <(cat -s $(TEST_FILE))
	-diff <(./s21_cat -t $(TEST_FILE)) <(cat -t $(TEST_FILE))
	-diff <(./s21_cat --number-nonblank $(TEST_FILE)) <(cat -b $(TEST_FILE))
	-diff <(./s21_cat --number $(TEST_FILE)) <(cat -n $(TEST_FILE))
	-diff <(./s21_cat --squeeze-blank $(TEST_FILE)) <(cat -s $(TEST_FILE))
	# -diff <(./s21_cat -benst $(TEST_FILE)) <(cat -benst $(TEST_FILE))

	# $(CHECK) ./s21_cat $(TEST_FILE) | grep ERROR
	# $(CHECK) ./s21_cat -b $(TEST_FILE) | grep ERROR
	# $(CHECK) ./s21_cat -e $(TEST_FILE) | grep ERROR
	# $(CHECK) ./s21_cat -n $(TEST_FILE) | grep ERROR
	# $(CHECK) ./s21_cat -s $(TEST_FILE) | grep ERROR
	# $(CHECK) ./s21_cat -t $(TEST_FILE) | grep ERROR
	# $(CHECK) ./s21_cat -benst $(TEST_FILE) | grep ERROR

clean:
	rm -rf s21_cat

rebuild: clean all
