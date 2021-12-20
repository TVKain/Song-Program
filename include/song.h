#ifndef SONG_H
#define SONG_H

typedef struct song_s 
{
	char name[64];
	char singer[64];
	char songwriter[64];
	int year;
} song_t;

song_t create_song(char *n, char *si, char *sw, int y);



#endif