#include <stdio.h>
#include <stdlib.h>

#include "song.h"
#include "cvector.h"
#include "mfunctions.h"
#include "mgraphics.h"


int main(int argc, char *argv[])
{
	clear_screen();
	arg_check(argc, 2);

	cvector(song_t) vec = cvector_init(sizeof(song_t));
	read_song(argv[1], vec);

	int choice;

	for (;;) {
		print_block(2, (char*[]){"SONG PROGRAM", "MENU"}, 32, 36, CENTER);
		print_block(5, (char*[]){"[1] List Songs", "[2] Sort Songs", 
			"[3] Delete a song", "[4] Add a song", "[5] Exit"}, 40, 32, LEFT); 

		print_line(32, "Enter your choice: ");
		scanf("%d", &choice);
		getchar();

		if (choice == 5) {
			print_block(1, (char*[]){"THANK YOU HAVE A NICE DAY"}, 40, 32, CENTER);
			break;
		}
		
		if (choice < 1 || choice > 5) {
			printf("Invalid choice!\n");
			continue;
		}

		clear_screen();
		switch(choice) {
			case 1:
				list_song(vec);
				break;
			case 2: 
				sort_function(vec);
				break;
			case 3:
				delete_song_function(vec, argv[1]);
				break;
			case 4: 
				add_song_function(vec, argv[1]);
				break;
			default: break;
		}
		clear_screen();
	}

	cvector_free(vec);
	return 0;
}








