#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libgen.h>
#include "types.h"

/* Make file pointer accessible from all project files */
extern FILE* mp3_fptr;

extern long eof;//Extern end of file byte value

/* Function prototypes */
/* Display help menu */
void help_menu(void);

/* Check operation type */
OperationType check_operation_type(char* argv[]);

/* Check modifier type */
ModifierType check_modifier_type(char* argv[]);

/* Read and validate mp3 format */
Status read_and_validate_mp3_format(char* argv[]);

/* Read and validate mp3 format */
Status open_file(char* argv[]);

/* Display the file details when (-v) option is given */
void view_file_details(char* argv[]);

/* Edit the file content when (-e) option is given */
Status edit_file_content(char* filename, ModifierType modifier, char* new_content);

/* Get the tag position in the file */
long get_tag_position(const char* tag_name);

/* Print the tag value */
void print_tag_value(ModifierType modifier, long seek_from);

/* Get the size of the mp3 file */
long get_file_size(void);
#endif

