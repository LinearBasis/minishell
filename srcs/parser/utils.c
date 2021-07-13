#include "parser.h"

t_operation		parser__is_operation(const char *str)
{
	t_operation out;

	out = OP_NONE;
	if (*str == '|')
		out = OP_PIPE;
	else if (*str == '<')
	{
		if (str[1] == '<')
			out = OP_REDIR2L;
		else
			out = OP_REDIRL;
	}
	else if (*str == '>')
	{
		if (str[1] == '>')
			out = OP_REDIR2R;
		else
			out = OP_REDIRR;
	}
	return (out);
}