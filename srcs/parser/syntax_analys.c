#include "parser.h"

/*
	syntax_analys function

	Analys quotes and specific operations between commands.
*/
int	parser__syntax_analys(char *str, t_operation *error_token)
{
	while (ft_isspace(*str))
		str++;
	if (!*str)
		return (EX_OK);
	*error_token = OP_NONE;
	if (parser__syntax_analys__quotes(str) != EX_OK)
		return (EX_MISUSE_BUILTIN);
	else if (parser__syntax_analys__operations(str, error_token) != EX_OK)
		return (EX_MISUSE_BUILTIN);
	return (EX_OK);
}

int	parser__syntax_analys__quotes(char *str)
{
	char	double_q;
	char	single_q;

	single_q = 0;
	double_q = 0;
	while (*str)
	{
		if (!single_q && *str == '\"')
			double_q = !double_q;
		else if (!double_q && *str == '\'')
			single_q = !single_q;
		str++;
	}
	if (double_q || single_q)
		return (EX_MISUSE_BUILTIN);
	return (EX_OK);
}
