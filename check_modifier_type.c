#include "main.h"

ModifierType check_modifier_type(char* argv[])
{
		if (!strcmp(*argv, "-t"))//Check if argument is '-t'
				return e_title;
		else if (!strcmp(*argv, "-T"))//Check if argument is '-T'
				return e_track;
		else if (!strcmp(*argv, "-a"))//Check if argument is '-a'
				return e_artist;
		else if (!strcmp(*argv, "-A"))//Check if argument is '-A'
				return e_album;
		else if (!strcmp(*argv, "-y"))//Check if argument is '-y'
				return e_year;
		else if (!strcmp(*argv, "-C"))//Check if argument is '-C'
				return e_comment;
		else if (!strcmp(*argv, "-g"))//Check if argument is '-g'
				return e_genre;
		else
				return e_wrong_mod_type;//Some other argument
}

