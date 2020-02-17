#include "main.h"

//Returns file size including EOF byte
long get_file_size(void)
{
		if (mp3_fptr)
		{
				//Seek to the end of file
				fseek(mp3_fptr, 0L, SEEK_END);
				eof = ftell(mp3_fptr);//Last byte value in the file
				printf("INFO: Original file size = %ld bytes\n", eof);
				return eof;
		}
		return -1;
}

