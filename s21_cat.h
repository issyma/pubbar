#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct options_sss {
  int b, e, v, n, s, t, error;
} opt_t;

opt_t p_arg(int argc, char* argv[]);
void print_file(const char* filename, opt_t opt);

#endif
