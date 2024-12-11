#include "s21_cat.h"


opt_t p_arg(int argc, char* argv[]) {
  opt_t opt = {};
  const char short_options[] = "bsvneEtT";
  struct option long_options[] = {{"number-nonblank", 0, NULL, 'b'}, {"number", 0, NULL, 'n'}, {"squeeze-blank", 0, NULL, 's'}, {0, 0, 0, 0}};
 
  int oppos;
  while ((oppos = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
    switch (oppos) {
      case 'b':
        opt.b = 1;
        opt.n = 0;
        break;

      case 's':
        opt.s = 1;
        break;

      case 'v':
        opt.v = 1;
        break;

      case 'n':
        opt.n = !opt.b;
        break;

      case 'e':
        opt.e = 1;
        opt.v = 1;
        break;

      case 'E':
        opt.e = 1;
        break;
        
      case 't':
        opt.v = 1;
        opt.t = 1;
        break;
        
      case 'T':
        opt.t = 1;
        break;
        default:
    }
  }
  return opt;
}

void print_file(const char* filename, opt_t opt) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    printf("ERROR\n");
    return;
  }

int main(int argc, char* argv[]) {
  opt_t opt = p_arg(argc, argv);
  for (int i = optind; i < argc; i++) {
    print_file(argv[i], opt);
  }
  return 0;

}
  int non_empty_lines = 1;
  int non_empty_flag = '\n';
  int string_copression = 0;
  while ((fgetc(file)) != EOF) {
    if (opt.s && fgetc(file) == '\n' && non_empty_flag == '\n') {
      string_copression++;
      if (string_copression > 1) {
        continue;
      }
    } else {
      string_copression = 0;
    }
    if (opt.b && fgetc(file) != '\n' && non_empty_flag == '\n') {
      printf("%6d\t", non_empty_lines++);
    }
    if (opt.n && non_empty_flag == '\n') {
      printf("%6d\t", non_empty_lines++);
    }
    if (opt.e && fgetc(file) == '\n') {
      putchar('$');
    }
    if (opt.t && fgetc(file) == '\t') {
      putchar('^');
      c = 'I';
    }
    if (opt.v) {
      if (c < 32 && c != '\n' && c != '\t') {
        putchar('^');
        c += 64;
      } else {
        if (c == 127) {
          putchar('^');
          c = '?';
        }
      }
    }
    putchar(c);
    non_empty_flag = c;
  }
  fclose(file);
}
