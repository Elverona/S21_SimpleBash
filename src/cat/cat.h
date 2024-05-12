#ifndef CAT_H
#define CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define TABULATION '\t'
#define IS_NEW_LINE '\n'
#define MONY '$'
#define TRUE 1
#define FALSE 0

typedef struct {
  int b, n, s, E, T, v;
} flag;

char v_output(char ch);
void outline(flag* arg, char* line, int n);
void output(flag* arg, char** argv);

flag flag_parser(int argc, char** argv) {
  flag arg = {FALSE};
  struct option log_options[] = {{"number", no_argument, NULL, 'n'},
                                 {"number-nonblank", no_argument, NULL, 'b'},
                                 {"squeeze-blank", no_argument, NULL, 's'},
                                 {0, 0, 0, 0}};
  int opt;
  while ((opt = getopt_long(argc, argv, "bEensTtv", log_options, 0)) != -1) {
    switch (opt) {
      case 'b':
        arg.b = TRUE;
        break;
      case 'E':
        arg.E = TRUE;
        break;
      case 'e':
        arg.E = TRUE;
        arg.v = TRUE;
        break;
      case 'n':
        arg.n = TRUE;
        break;
      case 's':
        arg.s = TRUE;
        break;
      case 't':
        arg.T = TRUE;
        arg.v = TRUE;
        break;
      case 'T':
        arg.T = TRUE;
        break;
      case '?':
        perror("ERROR");
        exit(1);
        break;
      default:
        break;
    }
  }
  if ((arg.b == TRUE) && (arg.n == TRUE)) arg.n = FALSE;
  return arg;
}
#endif