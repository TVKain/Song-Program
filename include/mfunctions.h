/* Helper library with all of the menu backend functions */

#ifndef MFUNCTIONS_H
#define MFUNCTIONS_H

#include "cvector.h"
#include "song.h"
#include "mgraphics.h"
#include <errno.h>
#include <stdio.h>

#define BUFF_SIZE 512

#define read_song(fname, vec)												\
	do {																	\
		FILE *fptr = fopen(fname, "r");										\
		if (fptr == NULL) {													\
			fprintf(stderr, "Error: %s", strerror(errno));					\
			exit(EXIT_FAILURE);												\
		}																	\
		char buffer[512];													\
		char *delim = "#*#";												\
		while (fgets(buffer, sizeof(buffer), fptr)) {						\
			buffer[strlen(buffer) - 1] = 0;									\
			char *n = strtok(buffer, delim);								\
			char *si = strtok(NULL, delim);									\
			char *sw = strtok(NULL, delim);									\
			int y = atoi(strtok(NULL, delim));								\
			song_t tmp = create_song(n, si, sw, y);							\
			push_back((vec), tmp);											\
		}																	\
		fclose(fptr);														\
	} while (0)

#define print_song(s, index) 												\
	printf("%-4zu%-32s%-32s%-32s%-4d\n", index, s.name,						\
			s.singer, s.songwriter, s.year);

#define print_svec_if_str(vec, type, str) 									\
	do {																	\
		size_t j = 1;														\
		for (size_t i = 0; i < size(vec); ++i) {							\
			if (strstr(vec[i].type, str) != NULL) {							\
				printf("\n");												\
				print_song(vec[i], j);										\
				j++;														\
			}																\
		}																	\
	} while (0)

#define print_svec_if_num(vec, type, num)									\
	do {																	\
		size_t j = 1;														\
		for (size_t i = 0; i < size(vec); ++i) {							\
			if (vec[i].type >= num) {										\
				printf("\n");												\
				print_song(vec[i], j);										\
				j++;														\
			}																\
		}																	\
	} while (0)		

#define print_svec(vec)														\
	do {																	\
		for (size_t i = 0; i < size(vec); ++i) {							\
			printf("\n");													\
			print_song(vec[i], i + 1);										\
		}																	\
	} while (0)


/*
	One of the core menu functions 
	The reason it is a macro involves 
	in the push_back implementation of the cvector
*/
#define add_song_function(vec, fname)										\
	do {																	\
		int choice;															\
		for (;;) {															\
			print_block(1, (char*[]){"ADD A SONG"}, 32, 36, CENTER);		\
			print_block(2, (char*[]){"[1] Add a song", "[2] Exit"}, 		\
							40, 32, LEFT);									\
			print_line(32, "Enter your choice: ");							\
			scanf("%d", &choice);											\
			getchar();														\
			if (choice < 1 || choice > 2) {									\
				printf("Invalid choice\n"); 								\
				continue;													\
			}																\
			if (choice == 2) 												\
				break;														\
			clear_screen();													\
			char name[64];													\
			char singer[64];												\
			char songwriter[64];											\
			int year;														\
			print_block(1, (char*[]){"INPUT SONG INFO"}, 32, 36, CENTER);	\
			print_line(32, "Input song's name: ");				 			\
			fgets(name, sizeof(name), stdin);								\
			name[strlen(name) - 1] = 0;										\
			print_line(32, "Input singer's name: ");						\
			fgets(singer, sizeof(singer), stdin);							\
			singer[strlen(singer) - 1] = 0;									\
			print_line(32, "Input songwriter's name: ");					\
			fgets(songwriter, sizeof(songwriter), stdin);					\
			songwriter[strlen(songwriter) - 1] = 0;							\
			print_line(32, "Input year: ");									\
			scanf("%d", &year);												\
			getchar();														\
			song_t tmp = create_song(name, singer, songwriter, year);		\
			push_back(vec, tmp);											\
			print_block(2, (char*[]){"Successfully added the song", 		\
				"Changes to file has been made"}, 32, 36, CENTER);			\
			write_song(vec, fname);											\
			printf("PRESS ENTER TO CONTINUE...");							\
			getchar();														\
			clear_screen();													\
		}																	\
	} while (0)


void arg_check(int argc, int num);

void sort_song(cvector(song_t) vec);
void sort_singer(cvector(song_t) vec);
void sort_songwriter(cvector(song_t) vec);
void sort_year(cvector(song_t) vec);

void write_song(cvector(song_t) vec, const char *fname);

void list_song(cvector(song_t) vec);
void sort_function(cvector(song_t) vec);
void delete_song_function(cvector(song_t) vec, const char *fname);

#endif
