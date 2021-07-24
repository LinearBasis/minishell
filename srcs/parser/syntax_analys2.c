#include "parser.h"

static int	operations_redirects_analys(char *str,
				t_operation *error_token, int is_empty);
static int	operations_pipes_analys(char *str,
				t_operation *error_token, int is_empty);
static int	check_empty(int *is_empty, t_operation *error_token);

int	parser__syntax_analys__operations(char *str, t_operation *error_token)
{
	if (operations_redirects_analys(str, error_token, 0) != EX_OK
		|| operations_pipes_analys(str, error_token, 1) != EX_OK)
		return (EX_MISUSE_BUILTIN);
	return (EX_OK);
}

static int	operations_redirects_analys(char *str,
				t_operation *error_token, int is_empty)
{
	t_operation	op;
	char		quote_flag;
	char		curr_quote;

	quote_flag = 0;
	curr_quote = -1;
	while (*str)
	{
		parser__get_word__check_quote(str, &quote_flag, &curr_quote);
		op = parser__is_oper(str);
		if (!quote_flag && op != OP_NONE && op != OP_PIPE)
		{
			if (check_empty(&is_empty, error_token) != EX_OK)
				return (EX_MISUSE_BUILTIN);
		}
		else if (!ft_isspace(*str))
			is_empty = 0;
		str += 1 + (op == OP_REDIR2L || op == OP_REDIR2R);
	}
	if (is_empty)
	{
		*error_token = OP_NONE;
		return (EX_MISUSE_BUILTIN);
	}
	return (EX_OK);
}

static int	operations_pipes_analys(char *str,
				t_operation *error_token, int is_empty)
{
	t_operation	op;
	char		quote_flag;
	char		curr_quote;

	quote_flag = 0;
	curr_quote = -1;
	while (*str)
	{
		parser__get_word__check_quote(str, &quote_flag, &curr_quote);
		op = parser__is_oper(str);
		if (!quote_flag && op == OP_PIPE)
		{
			if (check_empty(&is_empty, error_token) != EX_OK)
				return (EX_MISUSE_BUILTIN);
		}
		else if (!ft_isspace(*str))
			is_empty = 0;
		str++;
	}
	if (check_empty(&is_empty, error_token) != EX_OK)
		return (EX_MISUSE_BUILTIN);
	return (EX_OK);
}

static int	check_empty(int *is_empty, t_operation *error_token)
{
	if (*is_empty)
	{
		*error_token = OP_NONE;
		return (EX_MISUSE_BUILTIN);
	}
	else
		*is_empty = 1;
	return (EX_OK);
}
