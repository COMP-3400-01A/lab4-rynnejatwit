#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        const char* msg = "ERROR: No arguments\n";
        write(2, msg, strlen(msg));
        return 1;
    }

    int n = argc - 1, start, count;
    if (n % 2) { start = 1 + n / 2; count = 1; }   // odd
    else       { start = n / 2;     count = 2; }   // even

    char* eargs[4];
    int k = 0;
    eargs[k++] = "echo";
    for (int i = 0; i < count; i++)
        eargs[k++] = (char*)argv[start + i];
    eargs[k] = NULL;

    execv("/usr/bin/echo", eargs);
    perror("exec");
    return 1;
}