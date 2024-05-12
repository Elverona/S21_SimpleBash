SHELL := /bin/bash
CC = gcc
TEST_FILE = ../test_files/grep/*.txt
CFLAGS = -Wall -Werror -Wextra -std=c11
PATTERNS = patterns.reg


all: s21_grep

s21_grep: clean
	$(CC) $(CFLAGS) grep.c -o s21_grep

work_test:
	-diff <(./s21_grep he $(TEST_FILE)) <(grep he $(TEST_FILE))
	-diff <(./s21_grep -v he $(TEST_FILE)) <(grep -v he $(TEST_FILE))
	-diff <(./s21_grep -i he $(TEST_FILE)) <(grep -i he $(TEST_FILE))
	-diff <(./s21_grep -iv he $(TEST_FILE)) <(grep -iv he $(TEST_FILE))
	-diff <(./s21_grep -in he $(TEST_FILE)) <(grep -in he $(TEST_FILE))
	-diff <(./s21_grep -in he $(TEST_FILE)) <(grep -in he $(TEST_FILE))
	-diff <(./s21_grep -ie "^he" $(TEST_FILE)) <(grep -ie "^he" $(TEST_FILE))
	-diff <(./s21_grep -ince "^he" $(TEST_FILE)) <(grep -ince "^he" $(TEST_FILE))
	-diff <(./s21_grep -lh se $(TEST_FILE)) <(grep -lh se $(TEST_FILE))
	-diff <(./s21_grep -hc e $(TEST_FILE)) <(grep -hc e $(TEST_FILE))
	-diff <(./s21_grep -e He -e he $(TEST_FILE)) <(grep -e He -e he $(TEST_FILE))
	-diff <(./s21_grep -s he badfile) <(grep -s he badfile)
	-diff <(./s21_grep -f $(PATTERNS) $(TEST_FILE)) <(grep -f $(PATTERNS) $(TEST_FILE))
	-diff <(./s21_grep -oi he $(TEST_FILE)) <(grep -oi he $(TEST_FILE))
	-diff <(./s21_grep -ohf $(PATTERNS) $(TEST_FILE)) <(grep -ohf $(PATTERNS) $(TEST_FILE))
	-diff <(./s21_grep -oinc he $(TEST_FILE)) <(grep -oinc he $(TEST_FILE))
	
clean:
	rm -f s21_grep

rebuild: clean all