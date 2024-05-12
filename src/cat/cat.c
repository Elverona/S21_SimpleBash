#define _GNU_SOURCE
#include "cat.h"

char v_output(char ch) {
  if (ch == IS_NEW_LINE || ch == TABULATION) return ch;

  if (ch <= 31) {
    putchar('^');
    ch += 64;
  } else if (ch == 127) {
    putchar('^');
    ch = '?';
  }
  return ch;
}

void outline(flag* arg, char* line, int n) {
  for (int i = 0; i < n; i++) {
    if (arg->T && line[i] == TABULATION)
      printf("^I");
    else {
      // if (arg->E && line[i] == IS_NEW_LINE) putchar(MONY);
      if (arg->b == FALSE && arg->E && line[i] == IS_NEW_LINE) putchar(MONY);
      if (arg->b == TRUE && arg->E && line[0] == IS_NEW_LINE) {
        char ch = MONY;
        printf("%9c\t", ch);
      }
      if (arg->b == TRUE && arg->E && line[0] != IS_NEW_LINE &&
          line[i] == IS_NEW_LINE)
        putchar(MONY);
      if (arg->v) line[i] = v_output(line[i]);
      putchar(line[i]);
    }
  }
}

void output(flag* arg, char** argv) {
  FILE* f = fopen(argv[optind], "r");
  char* line = NULL;
  size_t memline = 0;
  int read = 0;

  int line_number = 1;
  int empty_line = 0;
  read = getline(&line, &memline, f);
  while (read != -1) {
    if (line[0] == IS_NEW_LINE)
      empty_line++;
    else
      empty_line = 0;
    if (arg->s && empty_line > 1) {
    } else {
      if (arg->n || arg->b) {
        if (arg->b && line[0] != IS_NEW_LINE) {
          printf("%6d\t", line_number);
          line_number++;
        } else if (arg->n) {
          printf("%6d\t", line_number);
          line_number++;
        }
      }
      outline(arg, line, read);
    }
    read = getline(&line, &memline, f);
  }
  free(line);
  fclose(f);
}

int main(int argc, char* argv[]) {
  flag arg = flag_parser(argc, argv);
  output(&arg, argv);
  return FALSE;
}