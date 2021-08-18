/*******************************************************************************
 * Name    : pfind.c
 * Author  : Lukasz Asztemborski
 * Auhtor  : Matthew Vaysfeld
 * Version : 1.0
 * Date    : March 16, 2021
 * Description : Permission finder.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

#define fail return EXIT_FAILURE

static char * program_name;
int perms[] = {S_IRUSR, S_IWUSR, S_IXUSR,
               S_IRGRP, S_IWGRP, S_IXGRP,
               S_IROTH, S_IWOTH, S_IXOTH};
unsigned int perms_binary;

void display_usage() {
    printf("Usage: %s -d <directory> -p <permissions string> [-h]\n", program_name);
}

unsigned int statbuf_to_bin(struct stat *statbuf) {
    unsigned int ans = (statbuf->st_mode & perms[0])?1:0;
    int permission_valid;
    for (int i = 1; i < 9; i++) {
        permission_valid = statbuf->st_mode & perms[i];
        ans = (ans << 1);
        if (permission_valid) ans+=1;
    }
    return ans;
}

bool validate_perms(const char * str) {
    int len = strlen(str);
    if (len == 9) {
        for (;(len);len-=3) {
            if (str[len-1] != '-' && str[len-1] != 'x') return 0;
            if (str[len-2] != '-' && str[len-2] != 'w') return 0;
            if (str[len-3] != '-' && str[len-3] != 'r') return 0;
        }
        return 1;
    }
    return 0;
}

unsigned int str_to_bin(const char * str) {
    unsigned int ans = 0;
    for (int i = 0; i < 8; i++) {
        if (str[i]!='-') ans+=1;
        ans = (ans << 1);
    }
    return (str[8]=='-'?ans:ans+1);
}

void print_sol(char * path) {
    DIR * dir;
    if (!(dir = opendir(path))) { 
        fprintf(stderr, "Error: Cannot open directory '%s'. %s.\n",
                path, strerror(errno));
        return;
    }

    struct stat sb;
    char * full_filename;
    full_filename = malloc((PATH_MAX + 1) * sizeof(char)); 
    struct dirent * entry;
    size_t pathlen = 0;

    full_filename[0] = '\0';
    if (strcmp(path, "/")) {
        strncpy(full_filename, path, PATH_MAX);
    }

    pathlen = strlen(full_filename) + 1;
    full_filename[pathlen - 1] = '/';
    full_filename[pathlen] = '\0';

    while ((entry = readdir(dir))) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) { continue; }
        strncpy(full_filename + pathlen, entry->d_name, PATH_MAX - pathlen);
        if (lstat(full_filename, &sb) < 0) {
            fprintf(stderr, "Error: Cannot stat file '%s'. %s\n",
                    full_filename, strerror(errno));
            continue;
        }

        if (statbuf_to_bin(&sb) == perms_binary) {
            printf("%s\n", full_filename);
        }
        if (entry->d_type == DT_DIR) {
            print_sol(full_filename);
        }
    }
    free(full_filename);
    closedir(dir);
}


int main(int argc, char ** argv) {
    program_name = argv[0];
    if (!(argc ^ 1)) {
        display_usage();
        fail;
    }

    char path[PATH_MAX], * ps = NULL;

    int opt;
    opterr = 0;
    char * dflag = NULL;

    while ((opt = getopt(argc, argv, "d:p:h")) != -1) 
    {
        switch (opt) 
        {
        case 'd':
            dflag = optarg;
            break;
        case 'p':
            if (!dflag) {
                fprintf(stderr, "Error: Required argument -d <directory> not found.\n");
                fail;
            }
            ps = optarg;
            break;
        case 'h':
            display_usage();
            return EXIT_SUCCESS;
        default:
            if (optopt == 'd') {
                fprintf(stderr, "Error: Required argument -d <directory> not found.\n");
                fail;
            } else if (!dflag && optopt == 'p') { 
                fprintf(stderr, "Error: Required argument -d <directory> not found.\n");
                fail;
            }
            else if (optopt == 'p') {
                fprintf(stderr, "Error: Required argument -p <permissions string> not found.\n");
                fail;
            }
            fprintf(stderr, "Error: Unknown option '%s' received.\n", argv[optind-1]);
            fail;
        }
    }

    if (!ps) {
        fprintf(stderr, "Error: Required argument -p <permissions string> not found.\n");
        fail;
    }
	
	if (!realpath(dflag, path)) {
        fprintf(stderr, "Error: Cannot stat '%s'. %s.\n",
                dflag, strerror(errno));
        fail;
    }

    

    if (!validate_perms(ps)) {
        fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", ps);
        fail;
    }

    perms_binary = str_to_bin(ps);

    print_sol(path);

    return EXIT_SUCCESS;
}