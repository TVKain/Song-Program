#include "song.h"
#include <string.h>
#include <stdlib.h>

song_t create_song(char *n, char *si, char *sw, int y)
{
	song_t ret;

	strcpy(ret.name, n);
	strcpy(ret.singer, si);
	strcpy(ret.songwriter, sw);
	ret.year = y;

	return ret;
}
