#include "main.h"

void print_tag_value(ModifierType modifier, long seek_from)
{
		if (seek_from == -1)//Simply return is tag is not present
				return;
		//Move to the specific file offset
		fseek(mp3_fptr, seek_from, SEEK_SET);
		if (modifier == e_year)//Year
		{
				char year[5];//4 byte string + NUL character in the end
				year[4] = '\0';
				fseek(mp3_fptr, 11L, SEEK_CUR);//Move by 7 byte + 4 byte tag size to read content
				fread(year, 4, 1, mp3_fptr);//Read 4 bytes of year string
				printf("Year   : %s\n", year);//Display year & return
				return;
		}
		else if (modifier == e_track)//Track
		{
				char track[3];//2 byte string + NUL character in the end
				track[2] = '\0';
				fseek(mp3_fptr, 11L, SEEK_CUR);//Move by 7 byte + 4 byte tag size to read content
				fread(track, 2, 1, mp3_fptr);//Read 2 bytes of track string
				printf("Track  : %s\n", track);//Display track & return
				return;
		}
		fseek(mp3_fptr, 7L, SEEK_CUR);//Move by 3 byte + 4 byte tag size to read size
		char size;//Variable to store the size
		fread(&size, 1, 1, mp3_fptr);//Read 1 byte size value
		//printf("Size = %d\n", size);
		char buf[size];//Create a buffer string of obtained size
		buf[size - 1] = '\0';//Append NUL to the end of this string
		fseek(mp3_fptr, 3L, SEEK_CUR);//Move by 3 bytes & read the content
		fread(buf, size, 1, mp3_fptr);//Read & store content onto buffer string
		char extracted[size];//Remove unwanted characters in the string
		char i = 0,//Index of string to be filled out
			 j = 0,//Index of actual string with unwanted characters
			 l = 0;//To get the gap of extra characters (3 or 5 typically)
		           //(l = 0 for gap of 3) & (l = 2 for gap of 5)
		//Increment index j & variant l till an alphabet is found
		while(!isalpha(buf[j]))
		{
				j++, l++;
		}
		if (!l)//Need 1 byte lesser size for gap of 3 (l = 0)
				size--;
		while(j != size - l)//Fill up the extracted string
		{
				if (buf[j] != '\0')//Skip NUL & negative value characters
				{
						if (buf[j] < 0)
								buf[j] = ' ';
						extracted[i++] = buf[j];
				}
				j++;//Continue scanning next byte
		}
		extracted[i] = '\0';//Put a terminating NUL byte
		switch (modifier)
		{
				case e_title://Title
						printf("Title  : ");
						break;
				case e_artist://Artist
						printf("Artist : ");
						break;
				case e_album://Album
						printf("Album  : ");
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

