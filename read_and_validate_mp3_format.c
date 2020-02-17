#include "main.h"

Status read_and_validate_mp3_format(char* argv[])
{
		//Pointer to hold address of '.mp3' part from given argument
		const char* mp3_holder = strstr(*argv, ".mp3");
		if (mp3_holder)//Error handling
		{
				//If '.mp3' part is found, then check if string exactly ends with '.mp3'
				return (**argv != '.' && !strcmp(mp3_holder, ".mp3")) ? e_success : e_failure;
		}
		return e_failure;//NULL address which means '.mp3' part is not found
}

