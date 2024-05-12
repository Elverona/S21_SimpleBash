#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABULATION '\t'
#define IS_NEW_LINE '\n'
#define PALKA "|"
#define TRUE 1
#define FALSE 0

typedef struct {
  int e, i, v, c, l, n, h, s, f, o;
  char pattern[1024];
  int len_pattern;
} flag_option;

void pattern_add(flag_option* arg, char* pattern);
void add_reg_from_file(flag_option* arg, char* filepath);
void output_line(char* line, int n);
void print_math(flag_option arg, regex_t* re, char* line, char* path);
void processFile(flag_option arg, char* path, regex_t* reg);
void output(flag_option arg, int argc, char** argv);

flag_option arguments_parser(int argc, char* argv[]) {
  flag_option arg = {FALSE};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = TRUE;
        pattern_add(&arg, optarg);
        break;
      case 'i':
        arg.i = REG_ICASE;
        break;
      case 'v':
        arg.v = TRUE;
        break;
      case 'c':
        arg.c = TRUE;
        break;
      case 'l':
        arg.c = TRUE;
        arg.l = TRUE;
        break;
      case 'n':
        arg.n = TRUE;
        break;
      case 'h':
        arg.h = TRUE;
        break;
      case 's':
        arg.s = TRUE;
        break;
      case 'f':
        arg.f = TRUE;
        add_reg_from_file(&arg, optarg);
        break;
      case 'o':
        arg.o = TRUE;
        break;
    }
  }
  if (arg.len_pattern == FALSE) {
    pattern_add(&arg, argv[optind]);
    optind++;
  }
  if (argc - optind == TRUE) {
    arg.h = TRUE;
  }
  return arg;
}
#endif