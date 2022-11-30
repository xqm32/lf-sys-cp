#include <stdint.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Bad usage
    if (argc != 3) {
        printf("Usage: lfcp SOURCE DEST\n");
        return -1;
    }

    // See https://en.cppreference.com/w/c/io/fopen
    FILE* rfd = fopen(argv[1], "r");
    if (rfd == NULL) {
        printf("lfcp: %s: Error", argv[1]);
        return -1;
    }

    FILE* wfd = fopen(argv[2], "w");
    if (wfd == NULL) {
        printf("lfcp: %s: Error", argv[2]);
        return -1;
    }

    int c;
    while ((c = fgetc(rfd)) != EOF) {
        // See https://en.cppreference.com/w/c/io/ferror
        if (ferror(rfd)) {
            printf("lfcp: %s: Error", argv[1]);
            return -1;
        }

        fputc(c, wfd);
        if (ferror(wfd)) {
            printf("lfcp: %s: Error", argv[2]);
            return -1;
        }
    }

    return 0;
}