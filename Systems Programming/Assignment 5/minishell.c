/*******************************************************************************
 * Name    : minishell.c
 * Author  : Lukasz Asztemborski
 * Author  : Matthew Vaysfeld
 * Version : 1.0
 * Date    : April 14, 2021
 * Description : A great small minishell program.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <wait.h>
#include <sys/types.h>
#include <pwd.h>

#define BRIGHTBLUE "\x1b[34;1m"
#define DEFAULT "\x1b[0m"
#define MAX_COMMAND_LENGTH 10
#define MAX_ARGS 100


volatile sig_atomic_t signal_val = 0;

void catch_signal(int sig) {
    signal_val = 1;
    if (write(STDOUT_FILENO, "\n", 1) == -1) {
        fprintf(stderr, "Error: write() failed. %s.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

int rest_helper(char * str, int len) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != '\0' && str[i] != ' ' && str[i] != '"') {
            return -2;
        }
        if (str[i] == '"') count++;
    }
    return count;
}

int parse_path(char * path, char * input, const int len) {
    int quote_count = 0;
    bzero(path, PATH_MAX*2);
    char store[PATH_MAX*2];
    for (int i = 0; i < len; i++) {
        if (input[i] == ' ' || input[i] == '\0') {
            if (quote_count && (quote_count % 2) == 0) {
                int retval = rest_helper(&input[i], len-i);
                if (retval == -2) {
                    bzero(store, PATH_MAX*2);
                    return retval;
                }
                else {
                    if (retval % 2 == 0) {
                        break;
                    } else {
                        bzero(store, PATH_MAX*2);
                        return -1;
                    }
                }
            }
            store[i-quote_count] = ' ';
        }
        else if (input[i] == '"') {
            quote_count++;
        }
        else {
            store[i-quote_count] = input[i];
        }

    }
    if ((quote_count % 2) != 0) {
        bzero(store, PATH_MAX*2);
        return -1;
    }
    store[len-quote_count] = '\0';
    memcpy(path, store, len);
    bzero(store, PATH_MAX*2);

    return 2;
}

int split(char * str, char ** array){
    int retval = 0, i = 0;
    char * p = strtok(str, " ");
    while(p != NULL){
        array[i++] = p;
        p = strtok(NULL," ");
        retval++;
    }
    return retval;
}

void cd(int argc, char * argv[], char * buffer, int len) {
    uid_t uid = getuid();
    struct passwd * p;
    if ((p = getpwuid(uid)) == NULL) {
        fprintf(stderr, "Error: Cannot get passwd entry. %s.\n", strerror(errno));
        return;
    }
    char * home_dir = p->pw_dir, *dir = argv[1];

    if (argc == 1) {
        if (chdir(home_dir) == -1) {
            fprintf(stderr, "Error: Cannot change directory to '%s'. %s.\n", home_dir, strerror(errno));
        }
        return;
    }

    if (strchr(buffer, '"') == NULL) {
        if (argc > 2) {
            fprintf(stderr, "Error: Too many arguments to cd.\n");
            return;
        }
        if (dir[0] == '~') {
            if (strcmp(dir, "~") == 0) { // Due to how logical or is computed, this should never segfault.
                if (chdir(home_dir) == -1) {
                    fprintf(stderr, "Error: Cannot change directory to '%s'. %s.\n", home_dir, strerror(errno));
                }
                return;
            }
            char replace[PATH_MAX*2];
            replace[0] = '\0';
            strcat(replace, home_dir);
            strcat(replace, &dir[1]);
            if (chdir(replace) == -1) {
                fprintf(stderr, "Error: Cannot change directory to '%s'. %s.\n", replace, strerror(errno));
            }
            bzero(replace, PATH_MAX*2);
            return;
        }
        if (chdir(dir) == -1) {
            fprintf(stderr, "Error: Cannot change directory to '%s'. %s.\n", dir, strerror(errno));
            return;
        }
    }
    else {
        char path[PATH_MAX * 2];
        argc = parse_path(path, buffer, len-3);

        if (argc > 2 || argc == -2) {
            fprintf(stderr, "Error: Too many arguments to cd.\n");
            return;
        }

        if (argc == -1) {
            fprintf(stderr, "Error: Malformed command.\n");
            return;
        }

        if (path[0] == '~') {
            if (strcmp(path, "~") == 0) { // Due to how logical or is computed, this should never segfault.
                if (chdir(home_dir) == -1) {
                    fprintf(stderr, "Error: Cannot change directory to '%s'. %s.\n", home_dir, strerror(errno));
                }
                return;
            }
            char replace[PATH_MAX*2];
            replace[0] = '\0';
            strcat(replace, home_dir);
            strcat(replace, &path[1]);
            if (chdir(replace) == -1) {
                fprintf(stderr, "Error: Cannot change directory to '%s'. %s.\n", replace, strerror(errno));
            }
            bzero(replace, PATH_MAX*2);
            return;
        }

        if (chdir(path) == -1) {
            fprintf(stderr, "Error: Cannot change directory to '%s'. %s.\n", path, strerror(errno));
            return;
        }
        
    }
}


int main(void) {
    char wd[PATH_MAX], buffer[PATH_MAX+(MAX_COMMAND_LENGTH+1)*MAX_ARGS], *args[MAX_ARGS]; 
    bzero(buffer, PATH_MAX+(MAX_COMMAND_LENGTH+1)*MAX_ARGS);
    bzero(args, sizeof(args));
    ssize_t bytes;
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = catch_signal;

    if (sigaction(SIGINT, &action, NULL) == -1) {
        fprintf(stderr, "Error: Cannot register signal handler. %s.\n", strerror(errno));
        return EXIT_FAILURE;
    }

    while (1) {
        bzero(args, MAX_ARGS);
        if (getcwd(wd, sizeof(wd)) == NULL) {
            fprintf(stderr, "Error: Cannot get current working directory. %s.\n", strerror(errno));
            exit(EXIT_FAILURE);
        } 
        printf("[%s%s%s]$ ", BRIGHTBLUE, wd, DEFAULT);

        if (fflush(stdout) == EOF) {
            fprintf(stderr, "Error: fflush() failed. %s.\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        bzero(buffer, PATH_MAX+(MAX_COMMAND_LENGTH+1)*MAX_ARGS);

        if ((bytes = read(STDIN_FILENO, buffer, sizeof(buffer))) == -1) {
            if (signal_val == 1) {
                signal_val = 0;
                continue;
            }
            fprintf(stderr, "Error: Failed to read from stdin. %s.\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        if (bytes == 0) {
            puts("");
            exit(EXIT_SUCCESS);
        }
        buffer[bytes-1] = '\0';

        int count;
        if ((count = split(buffer, args)) == 0) {
            continue;
        } else {
            if (strcmp(args[0], "cd") == 0) { 
                cd(count, args, &buffer[3], bytes-1);
                continue;
            } else if (strcmp(args[0], "exit") == 0) {
                exit(EXIT_SUCCESS);
            } else {
                pid_t pid;
                if ((pid = fork()) < 0) {
                    fprintf(stderr, "Error: fork() failed. %s.\n", strerror(errno)); 
                    return EXIT_FAILURE;
                } else if (pid == 0) {
                    if (execvp(args[0], &args[0]) < 0) {
                        fprintf(stderr, "Error: exec() failed. %s.\n", strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                } else {
                    int status; // check if wait has SIGINTERRUPTED
                    if (waitpid(pid, &status, 0) < 0) {
                        if (signal_val == 1) {
                            signal_val = 0;
                            if (wait(NULL) < 0) {
                                fprintf(stderr, "Error: wait() failed. %s.\n", strerror(errno));
                                exit(EXIT_FAILURE);        
                            }
                            continue;
                        }
                        fprintf(stderr, "Error: wait() failed. %s.\n", strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                }
                
            }
        }
    }
    return EXIT_SUCCESS;
}