# Name : makefile
# Author : Lukasz Asztemborski
# Author : Matthew Vaysfeld
# Date : February 28, 2021
# Description : makefile for sort.c, quicksort.c, and quicksort.h
# Pledge : I pledge my honor that I have abided by the Stevens Honor System.

sort: sort.o quicksort.o
	gcc sort.o quicksort.o -o sort
sort.o: sort.c
	gcc -Wall -Werror -pedantic-errors -c sort.c
quicksort.o: quicksort.c quicksort.h
	gcc -Wall -Werror -pedantic-errors -c quicksort.c
clean:
	rm -f *.o sort sort.exe
