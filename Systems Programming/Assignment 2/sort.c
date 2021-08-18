/*******************************************************************************
 * Name        : sort.c
 * Author      : Lukasz Asztemborski
 * Author      : Matthew Vaysfeld
 * Date        : March 2, 2021
 * Description : Uses quicksort to sort a file of either ints, doubles, or
 *               strings.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"

#define MAX_STRLEN     64 // Not including '\0'
#define MAX_ELEMENTS 1024

typedef enum {
    STRING,
    INT,
    DOUBLE
} elem_t;

static char * program_name;

void print_usage(const int EXIT_CODE) {
    printf("Usage: %s [-i|-d] filename\n", program_name);
    puts("   -i: Specifies the file contains ints");
    puts("   -d: Specifies the file contains doubles.");
    puts("   filename: The file to sort.");
    puts("   No flags defaults to sorting strings.");
    exit(EXIT_CODE);
}

/**
 * Basic structure of sort.c:
 *
 * Parses args with getopt.
 * Opens input file for reading.
 * Allocates space in a char** for at least MAX_ELEMENTS strings to be stored,
 * where MAX_ELEMENTS is 1024.
 * Reads in the file
 * - For each line, allocates space in each index of the char** to store the
 *   line.
 * Closes the file, after reading in all the lines.
 * Calls quicksort based on type (int, double, string) supplied on the command
 * line.
 * Frees all data.
 * Ensures there are no memory leaks with valgrind. 
 */

/**
 * Reads data from filename into an already allocated 2D array of chars.
 * Exits the entire program if the file cannot be opened.
 */
size_t read_data(char *filename, char **data) {
    // Open the file.
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: Cannot open '%s'. %s.\n", filename,
                strerror(errno));
        free(data);
        exit(EXIT_FAILURE);
    }

    // Read in the data.
    size_t index = 0;
    char str[MAX_STRLEN + 2];
    char *eoln;
    while (fgets(str, MAX_STRLEN + 2, fp) != NULL) {
        eoln = strchr(str, '\n');
        if (eoln == NULL) {
            str[MAX_STRLEN] = '\0';
        } else {
            *eoln = '\0';
        }
        // Ignore blank lines.
        if (strlen(str) != 0) {
            data[index] = (char *)malloc((MAX_STRLEN + 1) * sizeof(char));
            strcpy(data[index++], str);
        }
    }

    // Close the file before returning from the function.
    fclose(fp);

    return index;
}

int main(int argc, char **argv) {
    program_name = argv[0];
    if (argc==1) print_usage(EXIT_FAILURE);


    int opt, index = 1;
    elem_t flag = STRING;

    opterr = 0;
    while ((opt = getopt(argc, argv, "id")) != -1) 
    {
        switch (opt) 
        {
        case 'i':
            if (flag!=STRING) {
                fprintf(stderr, "Error: Too many flags specified.\n");
                return EXIT_FAILURE;
            }
            flag = INT;
            index=2;
            break;
        case 'd':
            if (flag!=STRING) {
                fprintf(stderr, "Error: Too many flags specified.\n");
                return EXIT_FAILURE;
            }
            flag = DOUBLE;
            index=2;
            break;
        default:
            fprintf(stderr, "Error: Unknown option '%s' received.\n", argv[optind-1]);
            print_usage(EXIT_FAILURE);
        }
    }

    char * filename;
    if (argv[index]) filename = argv[index];
    else {
        fprintf(stderr, "Error: No input file specified.\n");
        return EXIT_FAILURE;
    }

    if (++index != argc) {
        fprintf(stderr, "Error: Too many files specified.\n"); // fprintf?
        return EXIT_FAILURE;
    }

    char ** data;
    data = malloc(MAX_ELEMENTS * (MAX_STRLEN +1) * sizeof(char));
    for (size_t i = 0; i < MAX_ELEMENTS; ++i) {
        data[i] = NULL;
    }
    size_t data_max_index = read_data(filename, data);

    if (flag == STRING) {
        quicksort(data, data_max_index, sizeof(data), str_cmp);
        for (size_t i = 0; i < data_max_index; i++) {
            puts(data[i]);
        }
    }
    else if (flag == INT) {
        int * int_data;
        int_data = malloc(data_max_index * sizeof(int));
        for (int i = 0; i < data_max_index; i++) {
            int_data[i] = atoi(data[i]);
        }
        quicksort(int_data, data_max_index, sizeof(int), int_cmp);
        for (int i = 0; i < data_max_index; i++) {
            printf("%d\n", int_data[i]);
        }
        free(int_data);
    }
    else {
        double * double_data;
        double temp;
        double_data = malloc(data_max_index * sizeof(double));
        for (int i = 0; i < data_max_index; i++) {
            sscanf((char * )data[i], "%lf", &temp);
            double_data[i] = temp;
        }
        quicksort(double_data, data_max_index, sizeof(double), dbl_cmp);
        for (int i = 0; i < data_max_index; i++) {
            printf("%f\n", double_data[i]);
        }
        free(double_data);
    }


    
    for (int i = 0; i < MAX_ELEMENTS; i++) {
        if (data[i]) free(data[i]);
    }
    free(data);
    return EXIT_SUCCESS;
}
