#include "main.h"

Status open_file(char* argv[])
{
		//Open the given mp3 file with proper error handling
		if ((mp3_fptr = fopen((const char*)(*argv), "r+")) == NULL)
		{
				perror("open");
				fprintf(stderr, "ERROR: Unable to open file %s\nThis file may not be present in the current project directory.\n\n", *argv);
				return e_failure;
		}
		//Check if file is empty
		else if (get_file_size() == 0)
		{
				printf("ERROR: %s is an empty file!\nPlease enter a non-empty file\n\n", *argv);
				return e_failure;
		}
		//Check if file is having ID3v2.4 version. This project does not support this version
		fseek(mp3_fptr, 3L, SEEK_SET);
		char version_num;
		fread(&version_num, 1 , 1, mp3_fptr);
		if (version_num == 4)
		{
				printf("ERROR: mp3 file with version ID3v2.4 is not supported by this program\nPlease try with either ID3v2.2 or ID3v2.3 file\n\n");
				return e_failure;
		}
		rewind(mp3_fptr);
		return e_success;//No error found
}

