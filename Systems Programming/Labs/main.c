/*******************************************************************************
 * Name    : main.c
 * Author  : Lukasz Asztemborski
 * Author  : Matthew Vaysfeld
 * Version : 1.0
 * Date    : May 7, 2021
 * Description : lab 12
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define MAX_ARR_LEN 10

int main() {
    void *handle;
    int (*sum_array)(int*, const int);

    /* TODO: Dynamically open the shared library libsum.so. If it fails,
     * print the system-generated error message, and return from the program
     * with the failure exit code. */
    if ((handle = dlopen("./libsum.so", RTLD_LAZY)) == NULL) {
        fprintf(stderr, "Error: %s.\n", dlerror());
        return EXIT_FAILURE;
    }


    /* TODO: Get a pointer to the sum_array() function we just loaded. If it
     * fails, print the system-generated error message, and return from the
     * program with the failure exit code.
     * Heavy casting is needed to avoid errors when compiling with -pedantic. */
    *(int **)&sum_array = dlsym(handle, "sum_array");
    if (sum_array == NULL) {
        fprintf(stderr, "Error: %s.\n", dlerror());
        return EXIT_FAILURE;
    }

    int array[MAX_ARR_LEN];
    for (int i = 0; i < MAX_ARR_LEN; i++) {
        *(array + i) = i + 1;
    }
    /* Expected output:
       sum{1..1}: 1
       sum{1..2}: 3
       sum{1..3}: 6
       sum{1..4}: 10
       sum{1..5}: 15
       sum{1..6}: 21
       sum{1..7}: 28
       sum{1..8}: 36
       sum{1..9}: 45
       sum{1..10}: 55
    */
    for (int i = 0; i < MAX_ARR_LEN; i++) {
        printf("sum{%d..%d}: %d\n", 
               *array, *(array + i), sum_array(array, i+1));
    }

    /* TODO: Close the shared library.  If it fails, print the system-generated
     * error message, and return from the program with the failure exit code. */
    if (dlclose(handle) < 0) {
        fprintf(stderr, "Error: %s.\n", dlerror());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
