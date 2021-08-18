/*******************************************************************************
 * Name    : mtsieve.c
 * Author  : Lukasz Asztemborski
 * Author  : Matthew Vaysfeld
 * Version : 1.0
 * Date    : April 23, 2021
 * Description : Sieve algorithm with multithreading.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#include <sys/sysinfo.h>

typedef struct arg_struct {
    int start;
    int end;
} thread_args;

int total_count = 0;
pthread_mutex_t lock;
pthread_t * threads;

bool two_or_more(int n) {
    int count = 0;
    while (n) {
        if (n % 10 == 3) count++;
        n /= 10;
        if (count >= 2) return 1;
    }
    return 0;
}

void *sieve(void * ptr) {
    thread_args * t = (thread_args *)ptr;
    int retval, partial_sum = 0, sqrt_ = sqrt(t->end);

    bool * low_primes;
    if ((low_primes = malloc(sizeof(bool) * (sqrt_ + 3))) == NULL) {
        fprintf(stderr, "Error: malloc() failed. Cannot allocate memory.\n");
        free(t);
        free(threads);
        exit(EXIT_FAILURE);
    }
    memset(low_primes, 1, sizeof(bool) * sqrt_ + 1);
    low_primes[sqrt_+2] = NULL;

    for (int i = 2; i <= sqrt(sqrt_) + 1; i++) {
        if (low_primes[i]) {
            for (int j = i*i; j <= sqrt_; j+=i) {
                low_primes[j] = 0;
            }
        }
    }

    bool * high_primes;
    if ((high_primes = malloc(sizeof(bool) * (t->end-t->start+2))) == NULL) {
        fprintf(stderr, "Error: malloc() failed. Cannot allocate memory.\n");
        free(t);
        free(low_primes);
        free(threads);
        exit(EXIT_FAILURE);
    }
    memset(high_primes, 1, sizeof(bool) * (t->end-t->start+1));
    high_primes[t->end-t->start+1] = NULL;

    int a;
    for (int i = 2; i <= sqrt_; i++) {
        if (low_primes[i]) {
            a = ceil((double)t->start/i) * i - t->start;
            if (t->start <= i) {
                a += i;
            }
            for (int j = a; j < t->end-t->start+1; j+=i) {
                high_primes[j] = 0;
            }
        }
    }
    for (int i = 0; i < t->end-t->start+1; i++) {
        if (high_primes[i] && two_or_more(i+t->start)) partial_sum++;
    }

    free(high_primes);
    free(low_primes);

    if ((retval = pthread_mutex_lock(&lock)) != 0) {
        fprintf(stderr, "Warning: Cannot lock mutex. %s.\n", strerror(retval));
    }
    total_count += partial_sum;
    if ((retval = pthread_mutex_unlock(&lock)) != 0) {
        fprintf(stderr, "Warning: Cannot unlock mutex. %s.\n", strerror(retval));
    }
    pthread_exit(NULL);
}

/*
 * Function taken from 'readints.c' in Week 5 on Canvas Modules. 
 */
bool is_integer(char *input) {
    int start = 0, len = strlen(input);

    if (len >= 1 && input[0] == '-') {
        if (len < 2) {
            return false;
        }
        start = 1;
    }
    for (int i = start; i < len; i++) {
        if (!isdigit(input[i])) {
            return false;
        }
    }
    return true;
}


int main(int argc, char ** argv) {
    if (argc == 1) {
        fprintf(stderr, "Usage: %s -s <starting value> -e <ending value> -t <num threads>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    opterr = 0;
    int opt, start, end, numthreads = 0, num_processors;
    unsigned int flags = 0;
    long check;
    while ((opt = getopt(argc, argv, ":s:e:t:")) != -1) 
    {
        switch (opt) 
        {
        case 's':
            if (!is_integer(optarg)) {
                fprintf(stderr,"Error: Invalid input '%s' received for parameter '-%c'.\n", optarg, 's');
                return EXIT_FAILURE;
            }
            start = atoi(optarg);
            if ((check = atol(optarg)) != (long)start) {
                fprintf(stderr, "Error: Integer overflow for parameter '-%c'.\n", 's');
                return EXIT_FAILURE;
            }
            flags |= 1;
            break;
        case 'e':
            if (!is_integer(optarg)) {
                fprintf(stderr,"Error: Invalid input '%s' received for parameter '-%c'.\n", optarg, 'e');
                return EXIT_FAILURE;
            }
            end = atoi(optarg);
            if ((check = atol(optarg)) != (long)end) {
                fprintf(stderr, "Error: Integer overflow for parameter '-%c'.\n", 'e');
                return EXIT_FAILURE;
            }
            flags |= 2;
            break;
        case 't':
            if (!is_integer(optarg)) {
                fprintf(stderr,"Error: Invalid input '%s' received for parameter '-%c'.\n", optarg, 't');
                return EXIT_FAILURE;
            }
            numthreads = atoi(optarg);
            if ((check = atol(optarg)) != (long)numthreads) {
                fprintf(stderr, "Error: Integer overflow for parameter '-%c'.\n", 't');
                return EXIT_FAILURE;
            }
            flags |= 4;
            break;
        case ':':
            if (optopt == 'e' || optopt == 's' || optopt == 't') {
                fprintf(stderr, "Error: Option -%c requires an argument.\n", optopt);
            } else if (isprint(optopt)){
                fprintf(stderr, "Error: Unknown option '-%c'.\n", optopt);
            } else {
                fprintf(stderr, "Error: Unknown option character '\\x%x'.\n", optopt);
            }
            return EXIT_FAILURE;
        case '?':
            if (optopt == 'e' || optopt == 's' || optopt == 't') {
                fprintf(stderr, "Error: Option -%c requires an argument.\n", optopt);
            } else if (isprint(optopt)){
                fprintf(stderr, "Error: Unknown option '-%c'.\n", optopt);
            } else {
                fprintf(stderr, "Error: Unknown option character '\\x%x'.\n", optopt);
            }
            return EXIT_FAILURE;
        }
    }

    if (optind <= argc - 1) {
        fprintf(stderr, "Error: Non-option argument '%s' supplied.\n", argv[optind]);
        return EXIT_FAILURE;
    }
    if (!(flags & 1)) {
        fprintf(stderr, "Error: Required argument <starting value> is missing.\n");
        return EXIT_FAILURE;
    }
    if (start < 2) {
        fprintf(stderr, "Error: Starting value must be >= 2.\n");
        return EXIT_FAILURE;
    }
    if (!(flags & 2)) {
        fprintf(stderr, "Error: Required argument <ending value> is missing.\n");
        return EXIT_FAILURE;
    }
    if (end < 2) {
        fprintf(stderr, "Error: Ending value must be >= 2.\n");
        return EXIT_FAILURE;
    }
    if (end < start) {
        fprintf(stderr, "Error: Ending value must be >= starting value.\n");
        return EXIT_FAILURE;
    }
    if (!(flags & 4)) {
        fprintf(stderr, "Error: Required argument <num threads> is missing.\n");
        return EXIT_FAILURE;
    }
    if (numthreads < 1) {
        fprintf(stderr, "Error: Number of threads cannot be less than 1.\n");
        return EXIT_FAILURE;
    }
    if ((num_processors = get_nprocs()) * 2 < numthreads) {
        fprintf(stderr, "Error: Number of threads cannot exceed twice the number of processors(%d).\n",
                num_processors);
        return EXIT_FAILURE;
    }

    const int range = end-start+1;
    int min_nums, remainder = 0; 
    if (numthreads > range) {
        numthreads = range;
        remainder = 0;
        min_nums = 1;
    } 
    else {
        remainder = (range % numthreads); 
        min_nums = range / numthreads;
    }

    printf("Finding all prime numbers between %d and %d.\n", start, end);
    printf("%d segment%s\n", numthreads, numthreads==1?":":"s:");

    if ((threads = malloc(sizeof(pthread_t) * numthreads)) == NULL) {
        fprintf(stderr, "Error: malloc() failed. Cannot allocate memory.\n");
        return EXIT_FAILURE;
    }

    thread_args * targs;
    if ((targs = malloc(sizeof(thread_args) * numthreads)) == NULL) {
        fprintf(stderr, "Error: malloc() failed. Cannot allocate memory.\n");
        goto bad_exit;
    }

    int retval;
    if ((retval = pthread_mutex_init(&lock, NULL)) != 0) { // not listed as a warning in requirements doc?
        fprintf(stderr, "Error: Cannot create mutex. %s.\n", strerror(retval));
        goto bad_exit;
    }

    for (int i = 0, s = start, e = start + min_nums + (remainder!=0?0:-1);
        i < numthreads; ++i, s = e + 1, e += min_nums + (--remainder>0?1:0)) {
        targs[i].start = s;
        targs[i].end = e;
        printf("   [%d, %d]\n", s, e);
        if ((retval = pthread_create(&threads[i], NULL, sieve, (void *)&targs[i])) != 0) {
            fprintf(stderr, "Error: Cannot create thread %d. %s.\n", i+1, strerror(retval));
            goto bad_exit;
        }
    }

    for (int i = 0; i < numthreads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Warning: Thread %d did not join properly.\n", i + 1);
        }
    }

    if ((retval = pthread_mutex_destroy(&lock)) != 0) {
        fprintf(stderr, "Warning: Cannot destroy mutex. %s.\n", strerror(retval));
    }

    printf("Total primes between %d and %d with two or more '3' digits: %d\n", start, end, total_count);
    free(threads);
    free(targs);
    return EXIT_SUCCESS;

bad_exit:
    if (threads) free(threads);
    if (targs) free(targs);
    exit(EXIT_FAILURE);
}