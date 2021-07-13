#include "parser.h"

int	parse_input(const char *str, t_commlist **out_commlist)
{
	t_operation	error_token;

	if (parser__syntax_analys(str, &error_token) != CHECK_SUCCESS)
	{
		parser__print_syntax_error(error_token);
		return (-1);
	}
	return (0);
}