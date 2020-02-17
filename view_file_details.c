#include "main.h"

void view_file_details(char* argv[])
{
		//Print the version
		fseek(mp3_fptr, 0L, SEEK_SET);
		//Read 3 bytes & display
		char version[4];//String to store the version value + NUL byte
		version[3] = '\0';
		fread(version, 3, 1, mp3_fptr);
		printf("\n-----------------------------------------------------------------------\n");
		printf("Version: %s\n", version);
		rewind(mp3_fptr);
		//Get the tag position
		print_tag_value(e_title, get_tag_position("TIT2"));
		print_tag_value(e_track, get_tag_position("TRCK"));
		print_tag_value(e_artist, get_tag_position("TPE1"));
		print_tag_value(e_album, get_tag_position("TALB"));
		print_tag_value(e_year, get_tag_position("TYER"));
		print_tag_value(e_comment, get_tag_position("COMM"));
		print_tag_value(e_genre, get_tag_position("TCON"));
		printf("-----------------------------------------------------------------------\n\n");
}
