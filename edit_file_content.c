#include "main.h"

Status edit_file_content(char* filename, ModifierType modifier, char* new_content)
{
		//Start searching for given tag from the beginning of the file
		fseek(mp3_fptr, 0L, SEEK_SET);
		long seek_from;//To hold file offset value of beginning of the tag
		switch (modifier)//Tag to be modified
		{
				case e_title://Title
						seek_from = get_tag_position("TIT2");
						break;
				case e_track://Track
						seek_from = get_tag_position("TRCK");
						break;
				case e_artist://Artist
						seek_from = get_tag_position("TPE1");
						break;
				case e_album://Album
						seek_from = get_tag_position("TALB");
						break;
				case e_year://Year
						seek_from = get_tag_position("TYER");
						break;
				case e_comment://Comment
						seek_from = get_tag_position("COMM");
						break;
				case e_genre://Genre
						seek_from = get_tag_position("TCON");
		}
		if (seek_from == -1)
		{
				printf("ERROR: This tag field is not present in this mp3 file\n");
				return e_failure;
		}
		//printf("File offset after reading tag: %ld\n", ftell(mp3_fptr));
		//Note that there is no need to copy remaining data for year & track since they are fixed in size
		if (modifier == e_year)//Year edit
		{
				//Leave 7 bytes
				fseek(mp3_fptr, 7L, SEEK_CUR);
				//printf("File offset after leaving 7 bytes (4 byte year is to be read from here): %ld\n", ftell(mp3_fptr));
				fwrite(new_content, 4, 1, mp3_fptr);//Write new content
				//printf("File offset after writing year: %ld\n", ftell(mp3_fptr));
				return e_success;
		}
		else if (modifier == e_track)//Track edit
		{
				//Leave 4 bytes
				fseek(mp3_fptr, 7L, SEEK_CUR);
				//printf("File offset after leaving 7 bytes (2 byte track is to be read from here): %ld\n", ftell(mp3_fptr));
				fwrite(new_content, 2, 1, mp3_fptr);//write new content
				//printf("File offset after writing track: %ld\n", ftell(mp3_fptr));
				return e_success;
		}
		else//Let's follow 5-byte-gap scheme for writing new content
		{
				//Move the file offset by 7 bytes (3 NUL bytes + 4 byte tag size)
				fseek(mp3_fptr, 3L, SEEK_CUR);
				//printf("Leaving 3 bytes (size is read from here): %ld\n", ftell(mp3_fptr));
				//get the old string size
				char size;
				fread(&size, 1, 1, mp3_fptr);
				//printf("File offset after reading old string size: %ld\n", ftell(mp3_fptr));
				//printf("Old string size = %d\n", size);
				//Leave 3 bytes
				fseek(mp3_fptr, 3L, SEEK_CUR);
				//printf("File offset after leaving 3 bytes : %ld\n", ftell(mp3_fptr));
				//Get the file offset value after end of string by advancing size - 1 bytes
				fseek(mp3_fptr, size - 1, SEEK_CUR);
				//printf("Leaving bytes equivalent to size of old string (copy remaining bytes from here): %ld\n", ftell(mp3_fptr));
				//No. of bytes to be copied in the end including EOF byte
				long copy_bytes = eof - ftell(mp3_fptr) + 1;
				//Copy remaining data
				char remaining_bytes[copy_bytes];
				fread(remaining_bytes, copy_bytes, 1, mp3_fptr);
				//printf("After copying remaining bytes into a buffer: %ld\n", ftell(mp3_fptr));
				//Go back to offset position where size is written
				fseek(mp3_fptr, seek_from, SEEK_SET);
				//printf("File offset back to tag: %ld\n", ftell(mp3_fptr));
				fseek(mp3_fptr, 7L, SEEK_CUR);
				//printf("Leaving 7 bytes from tag: %ld\n", ftell(mp3_fptr));
				//printf("File offset where size is written: %ld\n", ftell(mp3_fptr));
				//printf("String to replace: %s\n", new_content);
				size = strlen(new_content);
				//printf("Actual string size = %d\n", size);
				//New string size by padding with NUL bytes (2 in the beginning & 3 in the end) + 1 NUL size
				size += 6;
				//printf("New size value = %d\n", size);
				fwrite(&size, 1, 1, mp3_fptr);//Write new size
				//printf("File offset after writing new string size : %ld\n", ftell(mp3_fptr));
				//Leave 3 bytes
				fseek(mp3_fptr, 3L, SEEK_CUR);
				//printf("File offset after leaving 3 bytes : %ld\n", ftell(mp3_fptr));
				char nul_beginning[2] = {'\0'};
				//Write 2 NUL bytes in the beginning of original string
				fwrite(nul_beginning, 2, 1, mp3_fptr);
				//printf("File offset after adding first 2 NUL bytes : %ld\n", ftell(mp3_fptr));
				//Write exact string with original size
				fwrite(new_content, size - 6, 1, mp3_fptr);
				//printf("After writing new string : %ld\n", ftell(mp3_fptr));
				//Putting NUL in last 3 bytes
				char last_nul_bytes[3] = {'\0'};
				fwrite(last_nul_bytes, 3, 1, mp3_fptr);
				//printf("Adding last 3 NUL bytes (remaining bytes are copied back from this offset): %ld\n", ftell(mp3_fptr));
				//Now copy the remaining bytes
				fwrite(remaining_bytes, copy_bytes, 1, mp3_fptr);
				printf("INFO: File size modified to = %ld bytes\n", ftell(mp3_fptr));
		}
}

