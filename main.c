#include "s21_cat.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>


void process_line(const char *line, int line_number, int s_ends, int non_blank, int numb_all, int s_tabs, int s_non_print) {
    if (numb_all || (non_blank && line[0] != '\n')) {
        printf("%6d  ", line_number);
    }

    for (size_t i = 0; line[i] != '\0'; i++) {
        if (s_ends && line[i] == '\n') {
            printf("$\n"); 
        } else if (s_tabs && line[i] == '\t') {
            printf("^I");
        } else if (s_non_print && (line[i] < 32 || line[i] == 127)) {
            if (line[i] != '\n') { 
                printf("^%c", line[i] == 127 ? '?' : line[i] + '@');
            }
        } else {
            putchar(line[i]);
        }
    }
}

void process_file(FILE *file, int s_ends, int non_blank, int numb_all, int s_tabs, int squeeze_blank, int s_non_print) {
    char buffer[4096];
    int line_number = 0;
    int previous_blank = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        int is_blank = (buffer[0] == '\n');

        if (squeeze_blank && is_blank && previous_blank) {
            continue;
        }
        previous_blank = is_blank;

        if (numb_all || (non_blank && buffer[0] != '\n')) {
            line_number++;
        }

        process_line(buffer, line_number, s_ends, non_blank, numb_all, s_tabs, s_non_print);
    }
}

int main(int argc, char *argv[]) {
    int s_ends = 0;
    int non_blank = 0;
    int numb_all = 0;
    int s_tabs = 0;
    int squeeze_blank = 0;
    int s_non_print = 0;

    int opt;
    while ((opt = getopt(argc, argv, "benstTvE")) != -1) {
        switch (opt) {
            case 'b':
                non_blank = 1;
                numb_all = 0;
                break;
            case 'n':
                if (!non_blank) {
                    numb_all = 1;
                }
                break;
            case 'e':
                s_ends = 1;
                s_non_print = 1;
                break;
            case 'E':
                s_ends = 1;
                break;
            case 't':
                s_tabs = 1;
                s_non_print = 1;
                break;
            case 'T':
                s_tabs = 1;
                break;
            case 's':
                squeeze_blank = 1;
                break;
            case 'v':
                s_non_print = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-b|-n|-e|-E|-t|-T|-s|-v] [file...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind == argc) {
        process_file(stdin, s_ends, non_blank, numb_all, s_tabs, squeeze_blank, s_non_print);
    } else {
        for (int i = optind; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (!file) {
                perror(argv[i]);
                continue;
            }

            process_file(file, s_ends, non_blank, numb_all, s_tabs, squeeze_blank, s_non_print);
            fclose(file);
        }
    }

    return 0;
}
