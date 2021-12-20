/*
	Helper functions for the program front-end
*/

#ifndef MGRAPHIC_H
#define MGRAPHIC_H

#include <stdlib.h> // system();
#include <stdio.h>


#define CENTER 'c'
#define LEFT 'l'
#define ALIGN char

#ifdef _WIN32
	#define clear_screen() system("cls")
#elif __linux__ 
	#define clear_screen() system("clear")
#endif

#define print_line(pad, msg) 												\
	do {																	\
		for (size_t j = 0; j < (pad); ++j) 									\
			printf(" ");													\
		printf("%s", (msg));												\
	} while (0)			
#define print_line_center(pad, msg)											\
	do {																	\
		print_line((pad), (msg));											\
		for (size_t j = 0; j < (pad); ++j)									\
			printf(" ");													\
	} while (0)
#define print_pad(size) print_symbol((size), ' ')
#define print_symbol(size, sym)												\
	do {																	\
		for (size_t p = 0; p < (size); ++p) 								\
			printf("%c", sym);												\
	} while (0)

void print_block(size_t size, char *a[size], size_t length, size_t padding, ALIGN opt);
void print_error_block(size_t size, char *a[size], size_t length, size_t padding);

#endif