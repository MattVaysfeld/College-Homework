/*******************************************************************************
 * Name    : mtsumarray.c
 * Author  : Lukasz Asztemborski
 * Author  : Matthew Vaysfeld
 * Version : 1.0
 * Date    : April 16, 2021
 * Description : Sum an array with threading.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct arg_struct {
    int start_index;
    int length;
} thread_args;

pthread_mutex_t lock;
int *array, sum = 0;

/**
 * Generates a random integer in range [low, high].
 */
int random_int_in_range(int low, int high) {
    return low + rand() % (high - low + 1);
}

/**
 * Displays an array of integers on the screen.
 */
void display_array(int *array, const int length) {
    printf("[");
    if (length > 0) {
        printf("%d", *array);
    }
    for (int *ptr = array + 1, *end = array + length; ptr < end; ptr++) {
        printf(", %d", *ptr);
    }
    printf("]\n");
}

/**
 * The function for the thread.
 * TODO:
 *   Cast the void pointer to a thread_args pointer.
 *   Create a local int variable called partial_sum to accumulate the sum.
 *   Use the thread_args to loop over the values in the array. One thread should
 *   add all the values at even indexes, the other should add all the values at
 *   odd indexes. Proper use of thread_args will enable you to write one loop.
 *   Increment the global variable sum after aquiring the lock.
 *   You must have the following error messages:
 *     "Warning: Cannot lock mutex. %s.\n"
 *     "Warning: Cannot unlock mutex. %s.\n"
 *   %s is the strerror of the return value of the corresponding functions.
 *   Exit from the thread.
 */
void *sum_array(void *ptr) {
    thread_args * t = (thread_args *)ptr;
    int partial_sum, retval;
    for (int i = t->start_index; i < t->length; i+=2) {
        partial_sum = array[i];
        if ((retval = pthread_mutex_lock(&lock)) != 0) {
            fprintf(stderr, "Warning: Cannot lock mutex. %s.\n", strerror(retval));
        }
        sum += partial_sum;
        if ((retval = pthread_mutex_unlock(&lock)) != 0) {
            fprintf(stderr, "Warning: Cannot unlock mutex. %s.\n", strerror(retval));
        }       
    }
    pthread_exit(NULL);
    // return NULL; would fix valgrind issues, but dr. b said not to worry about it
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num values>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int num_values = atoi(argv[1]);
    if (num_values <= 0) {
        fprintf(stderr, "Error: Invalid number of values '%s'.\n", argv[1]);
        return EXIT_FAILURE;
    }
    srand(time(NULL));
    if ((array = (int *)malloc(num_values * sizeof(int))) == NULL) {
        fprintf(stderr,
            "Error: Cannot allocate memory for array of size '%s'. %s.\n",
            argv[1], strerror(errno));
        return EXIT_FAILURE;
    }
    for (int i = 0; i < num_values; i++) {
        array[i] = random_int_in_range(0, 9);
    }
    printf("Random Array:\n");
    display_array(array, num_values);

    int retval;
    if ((retval = pthread_mutex_init(&lock, NULL)) != 0) {
        fprintf(stderr, "Error: Cannot create mutex. %s.\n", strerror(retval));
        free(array);
        return EXIT_FAILURE;
    }

    pthread_t threads[2];
    thread_args targs[2];

    // TODO:
    // In a loop, create 2 threads:
    //   One thread should add all the values at even indexes, the other should
    //   add all the values at odd indexes.
    //   Set targs[i].start_index and targs[i].length accordingly.
    //   Create the thread, passing in targs[i].
    //   If the thread fails to be created, display the following message and
    //   exit in failure:
    //     "Error: Cannot create thread %d. %s.\n", where
    //        %d is either 1 or 2 and
    //        %s is the strerror of the return value of the corresponding
    //           function.
    //   Note: Make sure you avoid a memory leak in this section of code!
    for (int i = 0; i < 2; i++) {
        if ((retval = pthread_create(&threads[i], NULL, sum_array, (void *)&targs[i])) != 0) {
            fprintf(stderr, "Error: Cannot create thread %d. %s.\n", i+1, strerror(retval));
            free(array);
            return EXIT_FAILURE;
        }
        targs[i].start_index = i % 2; 
        targs[i].length = num_values;
    }


    for (int i = 0; i < 2; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Warning: Thread %d did not join properly.\n",
                    i + 1);
        }
    }

    if ((retval = pthread_mutex_destroy(&lock)) != 0) {
        fprintf(stderr, "Error: Cannot destroy mutex. %s.\n", strerror(retval));
        free(array);
        return EXIT_FAILURE;
    }

    printf("Sum with threads: %d\n", sum);
    int sum_check = 0;
    for (int i = 0; i < num_values; i++) {
        sum_check += array[i];
    }
    printf("Sum without threads: %d\n", sum_check);

    free(array);
    return EXIT_SUCCESS;
}
