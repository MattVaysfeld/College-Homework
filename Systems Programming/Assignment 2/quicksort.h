/*******************************************************************************
 * Name        : quicksort.h
 * Author      : Lukasz Asztemborski
 * Author      : Matthew Vaysfeld
 * Date        : February 28, 2021
 * Description : Quicksort header.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#ifndef QUICKSORT_H_
#define QUICKSORT_H_

void quicksort(void *array, size_t len, size_t elem_sz,
               int (*comp) (const void*, const void*));

int int_cmp(const void *a, const void *b);
int str_cmp(const void *a, const void *b);
int dbl_cmp(const void *a, const void *b);

#endif
