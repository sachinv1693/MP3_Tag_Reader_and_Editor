#include "main.h"

OperationType check_operation_type(char* argv[])
{
		if (!strcmp(*argv, "-h"))//Check if argument is '-h'
				return e_help;
		else if (!strcmp(*argv, "-v"))//Check if argument is '-v'
				return e_view;
		else if (!strcmp(*argv, "-e"))//Check if argument is '-e'
				return e_edit;
		else
				return e_wrong_oper_type;//Some other argument
}

