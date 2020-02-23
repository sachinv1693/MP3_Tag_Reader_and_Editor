#include "main.h"

/* Global variables which can be externed into other files */
//File pointer to access the file & to perform operations on a given file
FILE* mp3_fptr = NULL;

long eof = 0;//Last byte value in the file

int main(int argc, char* argv[])
{
		//Verify the inputs given from command line
		printf("\nINFO: Verifying input..\n");
		//Check if it is ./mp3_tag_reader_editor -h
		if (argc == 2 && check_operation_type(argv + 1) == e_help)
		{
				printf("INFO: Valid input!\n");
				help_menu();//Display help menu
		}
		//Else check if it is view(-v) or edit(-e) option
		else if (argc == 3 && check_operation_type(argv + 1) == e_view)
		{
				printf("INFO: Valid input!\n");
				//Read and validate .mp3 file format
				//Extract only filename from given path if any
				argv[2] = basename(argv[2]);
				printf("INFO: Verifying if the given file is a .mp3 file..\n");
				if (read_and_validate_mp3_format(argv + 2) == e_failure)
				{
						printf("ERROR: Invalid filename provided in the 2nd command line argument. It must be a valid named '.mp3' file\n\n");
						exit(e_success);
				}
				printf("INFO: Valid filename provided!\n");
				printf("INFO: Opening the the given file..\n");
				if (open_file(argv + 2) == e_success)
						printf("INFO: Given file is successfully opened!\n");
			   	else
						exit(e_success);
				printf("INFO: Printing the details in the given .mp3 file..\n");
				//Pass the filename as argument to view the file details
				view_mp3_tags();
		}
		else if (argc == 5 && check_operation_type(argv + 1) == e_edit)
		{
				printf("INFO: Valid input!\n");
				//Read and validate .mp3 file format
				//Extract only filename from given path if any
				argv[2] = basename(argv[2]);
				printf("INFO: Verifying if the given file is a .mp3 file..\n");
				if (read_and_validate_mp3_format(argv + 2) == e_failure)
				{
						printf("ERROR: Invalid filename provided in the 2nd command line argument. It must be a valid named '.mp3' file\n\n");
						exit(e_success);
				}
				printf("INFO: Valid filename provided!\n");
				printf("INFO: Opening the the given file..\n");
				if (open_file(argv + 2) == e_success)
						printf("INFO: Given file is successfully opened.\n");
			   	else
						exit(e_success);
				printf("INFO: Performing edit operation on the given .mp3 file..\n");
				if (edit_mp3_tag(check_modifier_type(argv + 3), argv[4]) == e_failure)
				{
						printf("ERROR: Failed to edit the file with given information!\n");
						exit(e_success);
				}
				printf("INFO: File is successfully modified!\n\n");
		}
		else//Insufficient command line arguments
		{
				printf("ERROR: Invalid command line arguments.\n");
				printf("USAGE: ./mp3_tag_reader_editor -h for help\n\n");
				exit(e_success);
		}
		//Close the mp3 file if it is opened
		if (mp3_fptr)
		{
				printf("INFO: Closing the mp3 file..\n");
				fclose(mp3_fptr);
				printf("INFO: File is successfully closed!\n\n");
		}
		return 0;
}

