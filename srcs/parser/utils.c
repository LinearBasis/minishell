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

void	parser__print_syntax_error(t_operation error_token)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	if (error_token == OP_NONE)
		write(2, "newline", 7);
	else if (error_token == OP_PIPE)
		write(2, "|", 1);
	else if (error_token == OP_REDIRR)
		write(2, "<", 1);
	else if (error_token == OP_REDIRL)
		write(2, ">", 1);
	else if (error_token == OP_REDIR2R)
		write(2, "<<", 2);
	else if (error_token == OP_REDIR2L)
		write(2, ">>", 2);
	write(2, "\'\n", 2);
}
