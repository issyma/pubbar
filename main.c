#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

void printFile(FILE *file) {
    char buffer[4096];
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
}

void flag_b(FILE *file) {
    int linesNumbered = 1;
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if(buffer[0] != '\n') {
            printf("%6d  %s", linesNumbered, buffer);
            linesNumbered++;
        } else {
            printf("%s", buffer);
        }
    }
}

void flag_e(FILE *file) {
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '$';
            printf("%s\n", buffer); 
        } else {
            printf("%s", buffer);
        }
    }
}

void flag_n(FILE *file) {
    int linesNumbered = 1;
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%6d  %s", linesNumbered, buffer);
        linesNumbered++;
    }
}

void flag_t(FILE *file) {
    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        for (size_t i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] == '\t') {
                printf("^I");
            } else {
                printf("%c", buffer[i]);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int opt;
    int numb_b = 0;
    int numb_n = 0;
    int bux = 0;
    int tab = 0;

    while ((opt = getopt(argc, argv, "bneEtT")) != -1) {
        switch (opt) {
            case 'b':
                numb_b = 1;
                break;
            case 'n':
                numb_n = 1;
                break;
            case 'e':
            case 'E':
                bux = 1;
                break;
            case 't':
            case 'T':
                tab = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-b||-n||-e||-E||-t||-T] [file...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind == argc) {
        if (bux) {
            flag_e(stdin);
        } else if (numb_b) {
            flag_b(stdin);
        } else if (numb_n) {
            flag_n(stdin);
        } else if (tab) {
            flag_t(stdin);
        } else {
            printFile(stdin);
        }
    } else {
        for (int i = optind; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (file == NULL) {
                perror("fopen");
                continue;
            }

            if (bux) {
                flag_e(file);
            } else if (numb_b) {
                flag_b(file);
            } else if (numb_n) {
                flag_n(file);
            } else if (tab) {
                flag_t(file);
            } else {
                printFile(file);
            }

            fclose(file);
        }
    }

    return 0;
}
