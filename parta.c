#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        puts("ERROR: No arguments");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (i > 1) putchar(',');
        for (const char* p = argv[i]; *p; p++)
            putchar(toupper((unsigned char)*p));
    }

    putchar('\n');
    return 0;
}