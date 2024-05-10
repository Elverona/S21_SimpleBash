#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct arguments {
    int b, n, s, E, T, v;
}arguments;


arguments argument_parser(int argc, char** argv) {
    arguments arg = {0};
    struct option log_options[] = {
        {"number", no_argument, NULL, 'n'},
        {"number-nonblank", no_argument, NULL, 'b'},
        {"squeeze-blank", no_argument, NULL, 's'},
        {0, 0, 0, 0}
    };
    int opt;
    while ((opt = getopt_long(argc, argv, "bEensTtv", log_options, 0)) != -1) {
    switch (opt) {
        case 'b':
            arg.b = 1;
            break;
        case 'E':
            arg.E = 1;
            break;      
        case 'e':
            arg.E = 1;
            arg.v = 1;
            break;
        case 'n':
            arg.n = 1;
            break;
        case 's':
            arg.s = 1;
            break;
        case 't':
            arg.T = 1;
            arg.v = 1;
            break;
        case 'T':
            arg.T = 1;
            break;
        case '?':
            perror("ERROR");
            exit(1);
            break;
        default:
            break;
    }
    }
    if ((arg.b == 1) && (arg.n == 1)) 
        arg.n = 0;
    return arg;
}

char v_output(char ch) {
    if (ch == '\n' || ch == '\t') return ch;

    if (ch <= 31) {
        putchar('^');
        ch += 64;
    }
    else if (ch == 127) {
        putchar('^');
        ch = '?';
    }
    return ch;
}

void outline(arguments *arg, char* line, int n) {
    for (int i = 0; i < n; i++) {
        if (arg->T && line[i] == '\t') printf("^I");
        else {
        if (arg->E && line[i] == '\n') {
            putchar('$');
        }
        if (arg->v) {
            line[i] = v_output(line[i]);
        }
        putchar(line[i]);
        }
    }
}

void output(arguments* arg, char** argv) {
    FILE* f = fopen(argv[optind], "r");
    char* line = NULL;
    size_t memline = 0;
    int read = 0;

    int line_cout = 1;
    int empty_count = 0;
    read = getline(&line, &memline, f);
    while(read != -1) {
        if (line[0] == '\n') 
            empty_count++;
        else 
            empty_count = 0;
        if (arg->s && empty_count > 1){
        }
        else {
        if (arg->n || arg->b) {
            if (arg->b && line[0] != '\n') {
                printf("%6d\t", line_cout);
                line_cout++;
            }
            else if (arg->n) {
                printf("%6d\t", line_cout);
                line_cout++;
            }
        }
        outline(arg, line, read);
        }
        read = getline(&line, &memline, f);
    }
    free(line);
    fclose(f);
}

void readfile() {

}

int main (int argc, char* argv[]) {
    arguments arg = argument_parser(argc, argv);
    output(&arg, argv);
    
    
    return 0;
}