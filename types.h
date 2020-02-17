#ifndef TYPES_H
#define TYPES_H

/* User defined types */
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned char* uchar_ptr;

/* Status will be used in function return type */
typedef enum
{
    e_failure,
	e_success
} Status;

/* Operation type enum */
typedef enum
{
    e_help,
    e_view,
    e_edit,
	e_wrong_oper_type
} OperationType;

/* Modifier type enum */
typedef enum
{
    e_title,
    e_track,
    e_artist,
	e_album,
	e_year,
	e_comment,
	e_genre,
	e_wrong_mod_type
} ModifierType;

#endif

