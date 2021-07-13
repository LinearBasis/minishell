#include "parser.h"

/*
	syntax_analys function

	Analys quotes and specific operations between commands.
*/
static int	quotes_analys(const char *str);
static int	operations_analys(const char *str, t_operation *error_token);

int	parser__syntax_analys(const char *str, t_operation *error_token)
{
	if (quotes_analys(str) != CHECK_SUCCESS)
		return (CHECK_FAILED_QUOTES);
	else if (operations_analys(str, error_token) != CHECK_SUCCESS)
		return (CHECK_FAILED_OPERS);
	return (CHECK_SUCCESS);
}

static int	quotes_analys(const char *str)
{
	char	double_q;
	char	single_q;

	single_q = 0;
	double_q = 0;
	while (*str)
	{
		if (*str == '\"')
			double_q = !double_q;
		else if (*str == '\'' && !double_q)
			single_q = !single_q;
		str++;
	}
	if (double_q || single_q)
		return (CHECK_FAILED_QUOTES);
	return (CHECK_SUCCESS);
}

static int	operations_redirects_analys(const char *str,
				t_operation *error_token, int is_empty);
static int	operations_pipes_analys(const char *str,
				t_operation *error_token, int is_empty);

static int	operations_analys(const char *str, t_operation *error_token)
{
	if (operations_redirects_analys(str, error_token, 0) != CHECK_SUCCESS
		|| operations_pipes_analys(str, error_token, 1) != CHECK_SUCCESS)
		return (CHECK_FAILED_OPERS);
	return (CHECK_SUCCESS);
}

static int	operations_redirects_analys(const char *str,
				t_operation *error_token, int is_empty)
{
	t_operation	op;

	while (*str)
	{
		op = parser__is_oper(str);
		if (op != OP_NONE && op != OP_PIPE)
		{
			if (is_empty)
			{
				*error_token = op;
				return (CHECK_FAILED_OPERS);
			}
			else
				is_empty = 1;
		}
		else if (!ft_isspace(*str))
			is_empty = 0;
		str += 1 + (op == OP_REDIR2L || op == OP_REDIR2R);
	}
	if (is_empty)
	{
		*error_token = OP_NONE;
		return (CHECK_FAILED_OPERS);
	}
	return (CHECK_SUCCESS);
}

static int	operations_pipes_analys(const char *str,
				t_operation *error_token, int is_empty)
{
	t_operation	op;

	while (*str)
	{
		op = parser__is_oper(str);
		if (op == OP_PIPE)
		{
			if (is_empty)
			{
				*error_token = op;
				return (CHECK_FAILED_OPERS);
			}
			else
				is_empty = 1;
		}
		else if (!ft_isspace(*str))
			is_empty = 0;
		str++;
	}
	if (is_empty)
	{
		*error_token = OP_NONE;
		return (CHECK_FAILED_OPERS);
	}
	return (CHECK_SUCCESS);
}
