/*******************************************************************************
 * Name    : mpsumarray.c
 * Author  : Lukasz Asztemborski
 * Author  : Matthew Vaysfeld
 * Version : 1.0
 * Date    : April 30, 2021
 * Description : does anyone read this? Summing an array.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>
#include "semaphore.h"

int *array, *sum;
int semid;

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
 * The function for the child process.
 * TODO:
 *   Create a local int variable called partial_sum to accumulate the sum.
 *   One child process should add all the values at even indexes, the other
 *   should add all the values at odd indexes.
 *   Proper use of start_index and length will enable you to write one loop.
 *   Use P and V from the semaphore library, and increment the global variable
 *   after ensuring mutual exclusion.
 *   No error messages are required, as they come from the library.
 */
void sum_array(int *array, const int start_index, const int length) {
    int partial_sum = 0;
    for (int i = start_index; i < length; i+=2) {
        partial_sum += *(array + i);
    }

    P(semid);
    (*sum) += partial_sum;
    V(semid);
}

int main(int argc, char *argv[]) {
    int retval = EXIT_SUCCESS;
    int shmid = -1;
    void *shm = (void *)-1;

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

    // TODO: Create a key for the shared memory using ftok(), the current
    // directory, and the character 'a'.
    // If it fails, print the error message:
    //   "Error: Cannot create shared memory key. '%s'.\n",
    //   Set the return value to EXIT_FAILURE
    //   Transfer execution of code to the cleanup section of main().
    key_t key;
    if ((key = ftok("./", 'a')) == -1) {
        fprintf(stderr, "Error: Cannot create shared memory key. '%s'.\n",
                strerror(errno));
        retval = EXIT_FAILURE;
        goto EXIT;
    }

    // TODO: Create the semaphore semid. If it fails,
    //   Set the return value to EXIT_FAILURE
    //   Transfer execution of code to the cleanup section of main().
    if ((semid = create_semaphore(key)) == -1) {
        retval = EXIT_FAILURE;
        goto EXIT;
    }

    if ((retval = set_sem_value(semid, 1)) == EXIT_FAILURE) {
        goto EXIT;
    }

    if ((shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT)) == -1) {
        fprintf(stderr, "Error: Cannot get shared memory. '%s'.\n",
                strerror(errno));
        retval = EXIT_FAILURE;
        goto EXIT;
    }
    if ((shm = shmat(shmid, NULL, 0)) == (void *)-1) {
        fprintf(stderr, "Error: Cannot attach shared memory. '%s'.\n",
                strerror(errno));
        retval = EXIT_FAILURE;
        goto EXIT;
    }
    // TODO: Cast and initialize sum.
    sum = (int *)shm;
    *(sum) = 0;

    pid_t pid;
    int num_started = 0;
    for (int i = 0; i < 2; i++) {
        // TODO: Fork. If fork fails, print to standard error:
        //   "Error: process[%d] failed. %s.\n", where %d is 1 or 2
        //   (not 0 or 1), %s is the strerror of errno.
        // If fork succeeds and you are in the child process, sum up half of
        //   the array. sum_array() called with i == 0 sums up the values at
        //   even indices, while the function called with i == 1 sums up the
        //   values at odd indices. Don't forget to free the array in the child
        //    too.
        // If fork succeeds and you are in the parent, keep track of the
        // number of processes started.
        if ((pid = fork()) < 0) {
            fprintf(stderr, "Error: process[%d] failed. %s.\n", 
                    i + 1, strerror(errno));
        } else if (pid == 0) {
            sum_array(array, i, num_values);
            free(array);
            exit(EXIT_SUCCESS);
        } else {
            num_started++;
        }
    }

    // TODO: Wait for num_started children to complete.
    // If waiting fails,
    //   Print to standard error, "Warning: wait() failed. %s.\n".
    for (int i = 0; i < num_started; i++) {
        if (wait(NULL) < 0) {
            fprintf(stderr, "Warning: wait() failed. %s.\n", strerror(errno));
        }
    }

    printf("Sum with multiprocessing: %d\n", *sum);
    int sum_check = 0;
    for (int i = 0; i < num_values; i++) {
        sum_check += array[i];
    }
    printf("Sum without multiprocessing: %d\n", sum_check);

EXIT:
    free(array);
    if (shm != (void *)-1 && shmdt(shm) == -1) {
        fprintf(stderr, "Error: Cannot detach shared memory. '%s'.\n",
                strerror(errno));
        retval = EXIT_FAILURE;
    }
    // TODO: Free the shared memory, if shmid warrants freeing it.
    // If it fails, print to standard error,
    // "Error: Cannot free shared memory. '%s'.\n" and set the return value to
    // EXIT_FAILURE.
    // Check from the terminal with "ipcs" to ensure the shared memory has been
    // freed.
    if (semid != -1 && shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "Error: Cannot free shared memory. '%s'.\n", strerror(errno));
        retval = EXIT_FAILURE;
    }

    if (semid != -1 && del_sem_value(semid) == EXIT_FAILURE) {
        retval = EXIT_FAILURE;
    }
    return retval;
}
