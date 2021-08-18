#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool starts_with(const char *str, const char *prefix) {
    /* TODO:
       Return true if the string starts with prefix, false otherwise.
       Note that prefix might be longer than the string itself.
    */
	if (strlen(str) < strlen(prefix)) return 0;
	for (const char * s = str, * p = prefix; (*p); p++, s++) {
		if (*p != *s) return 0;
	}
	return 1;
}

int main() {
    /* TODO:
       Open "cat /proc/cpuinfo" for reading, redirecting errors to /dev/null.
       If it fails, print the string "Error: popen() failed. %s.\n", where
       %s is strerror(errno) and return EXIT_FAILURE.
    */
	FILE *fp = popen("cat /proc/cpuinfo 2>/dev/null", "r");
	if (!fp) {
		fprintf(stderr, "Error: popen() failed. %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}

    /* TODO:
       Allocate an array of 256 characters on the stack.
       Use fgets to read line by line.
       If the line begins with "model name", print everything that comes after
       ": ".
       For example, with the line:
       model name      : AMD Ryzen 9 3900X 12-Core Processor
       print
       AMD Ryzen 9 3900X 12-Core Processor
       including the new line character.
       After you've printed it once, break the loop.
    */
	char buf[256];
	while (fgets(buf, sizeof(buf), fp)) {
		if (starts_with(buf, "model name")) {
			char * ind = strchr(buf, ':');
			if (*(ind = ind + 2)) printf("%s", ind);
			break;
		}
	}

    /* TODO:
       Close the file descriptor and check the status.
       If closing the descriptor fails, print the string
       "Error: pclose() failed. %s.\n", where %s is strerror(errno) and return
       EXIT_FAILURE.
    */
	int status = pclose(fp);
	if (status == -1) {
		fprintf(stderr, "Error: pclose() failed. %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}

    return !(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS);
}
