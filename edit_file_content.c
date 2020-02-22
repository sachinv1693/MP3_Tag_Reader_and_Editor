#include "main.h"

Status edit_file_content(char* filename, ModifierType modifier, char* new_content)
{
		/* printf() statements would be useful for debugging the code */
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
		if (seek_from == -1)//Check if Tag is not present
		{
				printf("ERROR: This tag field is not present in this mp3 file\n");
				return e_failure;
		}
		fseek(mp3_fptr, seek_from, SEEK_SET);//Seek to the address of Tag
		//printf("File offset of Tag: %ld\n", ftell(mp3_fptr));
		//printf("File offset after reading tag: %ld\n", ftell(mp3_fptr));
		//Move the file offset by 7 bytes (4 byte tag size + 3 byte tag size)
		fseek(mp3_fptr, 7L, SEEK_CUR);
		//printf("Leaving 7 bytes (size is read from here): %ld\n", ftell(mp3_fptr));
		//get the old string size
		char size;
		fread(&size, 1, 1, mp3_fptr);
		//printf("File offset after reading old string size: %ld\n", ftell(mp3_fptr));
		//printf("Old string size = %d\n", size);
		//Get the file offset value after end of string by advancing size + 2 bytes
		fseek(mp3_fptr, size + 2, SEEK_CUR);
		//printf("Leaving bytes equivalent to size of old string + 2 pad bytes (copy remaining bytes from here): %ld\n", ftell(mp3_fptr));
		//No. of bytes to be copied in the end including EOF byte
		long copy_bytes = eof - ftell(mp3_fptr) + 1;
		//Copy remaining data into the heap memory area
		char* remaining_bytes = malloc(copy_bytes * sizeof(long));
		fread(remaining_bytes, copy_bytes, 1, mp3_fptr);
		//printf("After copying remaining bytes into heap: %ld\n", ftell(mp3_fptr));
		//Go back to offset position where size is written
		fseek(mp3_fptr, seek_from, SEEK_SET);
		//printf("File offset back to tag: %ld\n", ftell(mp3_fptr));
		fseek(mp3_fptr, 7L, SEEK_CUR);
		//printf("File offset after leaving 7 bytes from tag where size is to be written: %ld\n", ftell(mp3_fptr));
		//printf("String to replace: %s\n", new_content);
		size = strlen(new_content);
		//printf("Actual string size = %d\n", size);
		//New string size including a NUL byte size
		size += sizeof(char);
		//printf("New size value = %d\n", size);
		fwrite(&size, sizeof(size), 1, mp3_fptr);//Write new size
		//printf("File offset after writing new string size : %ld\n", ftell(mp3_fptr));
		char nul_beginning[3] = {'\0'};//An array to store 3 NUL bytes (for padding)
		//Write 3 NUL bytes in the beginning of original string
		fwrite(nul_beginning, 3, 1, mp3_fptr);
		//printf("File offset after adding first 3 NUL bytes : %ld\n", ftell(mp3_fptr));
		//Write exact string with original size
		fwrite(new_content, size - 1, 1, mp3_fptr);
		//printf("File offset after writing new string : %ld\n", ftell(mp3_fptr));
		//Now copy the remaining bytes
		fwrite(remaining_bytes, copy_bytes, 1, mp3_fptr);
		free(remaining_bytes);
		printf("INFO: File size modified to = %ld bytes\n", ftell(mp3_fptr));
}

