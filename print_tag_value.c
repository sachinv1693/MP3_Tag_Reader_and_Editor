#include "main.h"

void print_tag_value(ModifierType modifier, long seek_from)
{
		if (seek_from == -1)//Simply return is tag is not present
				return;
		//Move to the specific file offset
		fseek(mp3_fptr, seek_from, SEEK_SET);
		fseek(mp3_fptr, 7L, SEEK_CUR);//Move by 3 byte + 4 byte tag size to read size
		char size;//Variable to store the size
		fread(&size, sizeof(size), 1, mp3_fptr);//Read 1 byte size value
		//printf("Size = %d\n", size);
		char buf[size += 2];//Create a buffer string of obtained size + pad bytes
		fread(buf, size, 1, mp3_fptr);//Read & store content onto buffer string
		char extracted[size];//Remove unwanted characters in the string
		char i = 0,//Index of string to be filled out
			 j = 0;//Index of actual string with unwanted characters
		while (j != size)//Fill up the extracted string
		{
				//Skip NUL & non-printable protection characters
				if (buf[j] >= ' ')//Consider more than or equal to space character
				{
						extracted[i++] = buf[j];
				}
				j++;//Continue scanning next byte
		}
		extracted[i] = '\0';//Put a terminating NUL byte
		switch (modifier)//Print respective value
		{
				case e_title://Title
						printf("Title  : ");
						break;
				case e_track://Track
						printf("Track  : ");
						break;
				case e_artist://Artist
						printf("Artist : ");
						break;
				case e_album://Album
						printf("Album  : ");
						break;
				case e_year://Year
						printf("Year   : ");
						break;
				case e_comment://Comment
						printf("Comment: ");
						break;
				case e_genre://Genre
						printf("Genre  : ");
		}
		printf("%s\n", extracted);//Print extracted string, implicitly return
		rewind(mp3_fptr);
}

