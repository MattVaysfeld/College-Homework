/*******************************************************************************
 * Name    : spfind.c
 * Author  : Lukasz Asztemborski
 * Author  : Matthew Vaysfeld
 * Version : 1.0
 * Date    : March 31, 2021
 * Description : Sorting the output of pfind using system calls and other C functions.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

bool starts_with(const char *str, const char *prefix) { 
    if (strlen(str) < strlen(prefix)) return 0;
    for (const char * s = str, * p = prefix; (*p); p++, s++) {
        if (*p != *s) return 0;
    }
    return 1;
}

int main(int argc, char ** argv) {
    if (argc == 1) {
        fprintf(stderr, "Usage: %s -d <directory> -p <permissions string> [-h]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int pipes[2][2];

    if (pipe(pipes[0]) < 0) {
        fprintf(stderr, "Error: Cannot create pipe. %s.\n", strerror(errno));
        return EXIT_FAILURE;
    }

    if (pipe(pipes[1]) < 0) {
        fprintf(stderr, "Error: Cannot create pipe. %s.\n", strerror(errno));
        return EXIT_FAILURE;
    }

    pid_t pid[2];

    if ((pid[0] = fork()) < 0) {
        fprintf(stderr, "Error: Failed to fork. %s.\n", strerror(errno)); 
        return EXIT_FAILURE;
    }
    else if (!pid[0]) {
        /*  First process: pfind  */
        close(pipes[0][0]);
        close(pipes[1][0]);
        close(pipes[1][1]);

        if (dup2(pipes[0][1], STDOUT_FILENO) < 0) {
            fprintf(stderr, "Error: Failed to dup2 pfind.\n");
            close(pipes[0][1]);
            exit(EXIT_FAILURE);
        }

        if (execv("./pfind", argv) < 0) {
            fprintf(stderr, "Error: pfind failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    if ((pid[1] = fork()) < 0) {
        fprintf(stderr, "Error: Failed to fork. %s.\n", strerror(errno)); 
        return EXIT_FAILURE;
    }
    else if (!pid[1]) {
        /*  For sorting now  */
        close(pipes[0][1]);
        close(pipes[1][0]);
        if (dup2(pipes[0][0], STDIN_FILENO) < 0) {
            fprintf(stderr, "Error: Failed to dup2 sort.\n");
            close(pipes[1][1]);
            close(pipes[0][0]);
            exit(EXIT_FAILURE);
        }
        if (dup2(pipes[1][1], STDOUT_FILENO) < 0) {
            fprintf(stderr, "Error: Failed to dup2 sort.\n");
            close(pipes[1][1]);
            close(pipes[0][0]);
            exit(EXIT_FAILURE);
        }

        if (execlp("sort", "sort", (char *)NULL) < 0) {
            fprintf(stderr, "Error: sort failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    close(pipes[1][1]);
    close(pipes[0][0]);
    close(pipes[0][1]);

    char buffer[4096];
    ssize_t count;

    int file_count = 0;
    /* Built upon from canvas file */
    while (true) {
        count = read(pipes[1][0], buffer, sizeof(buffer));
        if (count == -1) {
            if (errno = EINTR) {
                continue;
            } else {
                perror("read()");
                exit(EXIT_FAILURE);
            }
        }
        else if (count == 0) {
            break;
        }
        else {
            for (int i = 0; i < count; i++) {
                if (buffer[i] == 'E') { // Adding at least some benchmark to run starts_with just so it doesn't have to run count times
                    if (starts_with(&buffer[i], "Error: ")) {
                        file_count--;
                    }
                }
                if (buffer[i] == '\n') {
                    file_count++;
                }
            }
            if (write(STDOUT_FILENO, buffer, count) == -1) {
                fprintf(stderr, "Error: write failed.\n");
                return EXIT_FAILURE;
            }
        }
    }

    close(pipes[1][0]);

    int status;
    if (wait(&status) < 0) {
        fprintf(stderr, "Error: Wait failed.\n");
        return EXIT_FAILURE;
    }
    if (status && WEXITSTATUS(status) == 1) {
        // Error will be printed from failed process (pfind return code was EXIT_FAILURE).
        exit(EXIT_FAILURE);
    }
    if (wait(NULL) < 0) {
        fprintf(stderr, "Error: Wait failed.\n");
        return EXIT_FAILURE;
    }

    printf("Total matches: %d\n", file_count);

    return EXIT_SUCCESS;
}