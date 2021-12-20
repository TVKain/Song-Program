#include "mfunctions.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "mgraphics.h"


/* check number of arguments */
void arg_check(int argc, int num)
{
	if (argc < num) {
		#ifdef _WIN32
			printf("Usage:\n\tprog [FILE_NAME]\n");
		#elif __linux__ 
			printf("Usage:\n\t./prog [FILE_NAME]\n");
		#endif
		exit(EXIT_FAILURE);
	}
}

/* Compare song */
static int cmp_song(const void *a, const void *b)
{
	song_t x = *(song_t*)a;
	song_t y = *(song_t*)b;
	return strcmp(x.name, y.name);
}

/* Compare singer */
static int cmp_singer(const void *a, const void *b)
{
	song_t x = *(song_t*)a;
	song_t y = *(song_t*)b;
	return strcmp(x.singer, y.singer);
}

/* Compare song writer */
static int cmp_songwriter(const void *a, const void *b)
{
	song_t x = *(song_t*)a;
	song_t y = *(song_t*)b;
	return strcmp(x.songwriter, y.songwriter);
}

/* Compare year */
static int cmp_year(const void *a, const void *b)
{
	song_t x = *(song_t*)a;
	song_t y = *(song_t*)b;

	return x.year - y.year;
}

void sort_song(cvector(song_t) vec)
{
	qsort(vec, size(vec), sizeof(song_t), cmp_song);
}

void sort_singer(cvector(song_t) vec)
{
	qsort(vec, size(vec), sizeof(song_t), cmp_singer);
}

void sort_songwriter(cvector(song_t) vec)
{
	qsort(vec, size(vec), sizeof(song_t), cmp_songwriter);
}

void sort_year(cvector(song_t) vec)
{
	qsort(vec, size(vec), sizeof(song_t), cmp_year);
}

/* END OF SORTING FUNCTIONS */


/* Write the vector to the file */
void write_song(cvector(song_t) vec, const char *fname)
{
	FILE *fptr = fopen(fname, "w");

	for (size_t i = 0; i < size(vec); ++i) {
		fprintf(fptr, "%s#*#%s#*#%s#*#%d\n", 
			vec[i].name, vec[i].singer, vec[i].songwriter, vec[i].year);
	}

	fclose(fptr);
}

/* Core menu functions */

void list_song(cvector(song_t) vec)
{
	int choice;

	for (;;) {
		print_block(1, (char*[]){"LIST SONGS"}, 32, 36, CENTER);
		print_block(5, (char*[]){"[1] By song name",
								 "[2] By singer",
								 "[3] By songwriter", 
								 "[4] By year",
								 "[5] Exit"}, 
								 40, 32, LEFT);

		print_line(32, "Enter your choice: ");
		scanf("%d", &choice);
		getchar();

		if (choice == 5) 
			break;

		if (choice < 1 || choice > 5) { 
			printf("Invalid choice!\n");
			continue;
		}

		char *msg;

		switch(choice) {
			case 1: 
				msg = "SONGS LIST (BASED ON SONGS)";
				sort_song(vec); 
				break;
			case 2:
				msg = "SONGS LIST (BASED ON SINGERS)"; 
				sort_singer(vec); 
				break;
			case 3:
				msg = "SONGS LIST (BASED ON SONGWRITERS)"; 
				sort_songwriter(vec); 
				break;
			case 4:
				msg = "SONGS LIST (BASED ON YEARS)";	
				sort_year(vec); 
				break;
			default: break;
		}

		clear_screen();
		print_block(1, (char*[]){msg}, 102, 0, CENTER);
		print_symbol(104, '-');
		printf("\n");
		printf("%-4s%-32s%-32s%-32s%-4s", "ID", "SONG", "SINGER", "SONGWRITER", "YEAR");
		printf("\n");
		print_symbol(104, '-');
		printf("\n");
		print_svec(vec);
		printf("\n");
		print_symbol(104, '-');
		printf("\n\n");
		printf("PRESS ENTER TO CONTINUE...");
		getchar();
		clear_screen();
	}
}

void sort_function(cvector(song_t) vec)
{
	int choice;
	char attrib[64];

	for (;;) {
		print_block(1, (char*[]){"SORTING ATTRIBUTE"}, 32, 36, CENTER);
		print_block(5, (char*[]){"[1] Song name", "[2] Singer", 
			"[3] Songwriter", "[4] Year", "[5] Exit"}, 40, 32, LEFT);
		print_line(32, "Enter your choice: ");
		scanf("%d", &choice);
		getchar();

		if (choice == 5) 
			break;

		if (choice < 1 || choice > 5) {
			printf("Invalid choice!\n");
			continue;
		}

		char *str = "Enter a string: ";

		if (choice == 4)
			str = "Enter a number: ";

		print_line(32, str);
		scanf("%s", attrib);
		getchar();

		int x;
		clear_screen();
		print_block(1, (char*[]){"SORTED LIST"}, 102, 0, CENTER);
		print_symbol(104, '-');
		printf("\n");
		printf("%-4s%-32s%-32s%-32s%-4s", "ID", "SONG", "SINGER", "SONGWRITER", "YEAR");
		printf("\n");
		print_symbol(104, '-');
		printf("\n");

		switch(choice) {
			case 1:
				sort_song(vec);
				print_svec_if_str(vec, name, attrib); 
				break;
			case 2:
				sort_singer(vec); 
				print_svec_if_str(vec, singer, attrib);
				break;
			case 3: 
				sort_songwriter(vec);
				print_svec_if_str(vec, songwriter, attrib);
				break;
			case 4: 
				x = atoi(attrib);
				sort_year(vec);
				print_svec_if_num(vec, year, x); 
				break;
			default: break;
		}
		printf("\n");
		print_symbol(104, '-');

		printf("\n\n");
		printf("PRESS ENTER TO CONTINUE...");
		getchar();
		clear_screen();
	}
}

void delete_song_function(cvector(song_t) vec, const char *fname)
{
	int choice;
	int del;
	char confirm;

	for (;;) {
		print_block(1, (char*[]){"DELETE A SONG"}, 32, 36, CENTER);
		print_block(2, (char*[]){"[1] Delete a song", "[2] Exit"}, 40, 32, LEFT);
		print_line(32, "Enter your choice: ");
		scanf("%d", &choice);
		getchar();

		if (choice == 2)
			break;

		if (choice < 1 || choice > 2) {
			printf("Invalid choice!\n");
			continue;
		}

		clear_screen();
		print_block(1, (char*[]){"LIST OF SONGS"}, 102, 0, CENTER);
		print_symbol(104, '-');
		printf("\n");
		printf("%-4s%-32s%-32s%-32s%-4s", "ID", "SONG", "SINGER", "SONGWRITER", "YEAR");
		printf("\n");
		print_symbol(104, '-');
		printf("\n");
		print_svec(vec);
		printf("\n");
		print_symbol(104, '-');
		printf("\n\n");

		do {
			printf("Choose a song to delete: ");
			scanf("%d", &del);
			getchar();
			if (del < 1 || del > size(vec)) {
				printf("Invalid choice!\n");
			}
		} while (del < 1 || del > size(vec));

		printf("The following song will be deleted:\n");
		print_symbol(104, '-'); 
		printf("\n\n");
		print_song(vec[del - 1], (size_t) del);
		printf("\n");
		print_symbol(104, '-');
		printf("\n");
		printf("Are you sure you want to delete this song ? (y/n) ");
		scanf("%c", &confirm);
		getchar();

		if (confirm == 'y' || confirm == 'Y') { 
			erase(vec, del - 1);
			write_song(vec, fname);
			print_block(2, (char*[]){"Selected song has been delete", 
									"Changes to file has been made"}, 
									40, 32, CENTER);
		} else {
			print_block(1, (char*[]){"Cancelled deleting song"}, 40, 32, CENTER);
		}
		printf("PRESS ENTER TO CONTINUE...");
		getchar();
		clear_screen();
	}
}

/* End of core menu functions */


