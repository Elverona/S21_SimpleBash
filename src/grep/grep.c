#define _GNU_SOURCE
#include "grep.h"

void pattern_add(flag_option* arg, char* pattern) {
  if (arg->len_pattern != FALSE) {
    strcat(arg->pattern + arg->len_pattern, PALKA);
    arg->len_pattern++;
  }
  arg->len_pattern += sprintf(arg->pattern + arg->len_pattern, "(%s)", pattern);
}

void add_reg_from_file(flag_option* arg, char* filepath) {
  FILE* f = fopen(filepath, "r");
  if (f == NULL) {
    if (!arg->s) perror(filepath);
    exit(1);
  }
  char* line = NULL;
  size_t memlen = 0;
  int read = getline(&line, &memlen, f);
  while (read != -1) {
    if (line[read - 1] == IS_NEW_LINE) line[read - 1] = '\0';
    pattern_add(arg, line);
    read = getline(&line, &memlen, f);
  }
  free(line);
  fclose(f);
}

void output_line(char* line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != IS_NEW_LINE) putchar(IS_NEW_LINE);
}

void print_math(flag_option arg, regex_t* re, char* line, char* path) {
  regmatch_t math;
  int offset = FALSE;
  while (TRUE) {
    int result = regexec(re, line + offset, TRUE, &math, FALSE);
    if (result != FALSE) {
      break;
    }
    if (!arg.h) printf("%s:", path);
    for (int i = math.rm_so; i < math.rm_eo; i++) {
      putchar(line[offset + i]);
    }
    putchar(IS_NEW_LINE);
    offset += math.rm_eo;
  }
}

void processFile(flag_option arg, char* path, regex_t* reg) {
  FILE* f = fopen(path, "r");
  if (f == NULL) {
    if (!arg.s) perror(path);
    exit(1);
  }
  char* line = NULL;
  size_t memlen = 0;
  int read = 0;
  int line_number = 1;
  int c = FALSE;
  read = getline(&line, &memlen, f);

  while (read != -1) {
    int result = regexec(reg, line, 0, NULL, 0);
    if ((result == FALSE && !arg.v) || (arg.v && result != FALSE)) {
      if (!arg.c && !arg.l) {
        if (!arg.h && !arg.o) printf("%s:", path);
        if (arg.n) printf("%d:", line_number);
        if (arg.o) {
          print_math(arg, reg, line, path);
        } else {
          output_line(line, read);
        }
      }
      c++;
    }

    read = getline(&line, &memlen, f);
    line_number++;
  }
  free(line);
  if (arg.c && arg.l && !arg.h) {
    printf("%s:%d\n", path, c);
  }
  if (arg.c && !arg.l) {
    if (!arg.h) printf("%s:", path);
    printf("%d\n", c);
  }
  if (arg.l && c > 0) printf("%s\n", path);
  fclose(f);
}

void output(flag_option arg, int argc, char** argv) {
  regex_t re;
  int error = regcomp(&re, arg.pattern, REG_EXTENDED | arg.i);
  if (error) perror("Error");
  for (int i = optind; i < argc; i++) {
    processFile(arg, argv[i], &re);
  }
  regfree(&re);
}

int main(int argc, char** argv) {
  flag_option arg = arguments_parser(argc, argv);
  output(arg, argc, argv);
  // free(arg.pattern);
  return FALSE;
}