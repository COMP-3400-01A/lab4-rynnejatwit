#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, const char* argv[]) {
    if (argc == 1) { printf("ERROR: No arguments\n"); return 1; }
    if (argc != 3) { printf("Usage: %s <word> <file>\n", argv[0]); return 1; }

    const char* word = argv[1];
    const char* file = argv[2];

    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {
        char* gargs[] = { "grep", "-s", "-q", (char*)word, (char*)file, NULL };
        execv("/usr/bin/grep", gargs);
        perror("exec");
        _exit(127);
    }

    int status;
    wait(&status);
    if (WIFEXITED(status)) {
        int code = WEXITSTATUS(status);
        if (code == 0) { printf("FOUND: %s\n", word);     return 0; }
        if (code == 1) { printf("NOT FOUND: %s\n", word); return 0; }
        printf("ERROR: %s doesn't exist\n", file);         return 2;
    }
    return 1;
}