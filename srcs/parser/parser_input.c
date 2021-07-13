#include "parser.h"

static int		fill_commlist(char *str, t_commlist **commlist);
static int		fill_commlist__push_elem(char **str, t_commlist **commlist,
					t_operation oper);

int	parse_input(char *str, t_commlist **out_commlist, t_envp *envp)
{
	t_operation	error_token;

	if (parser__syntax_analys(str, &error_token) != CHECK_SUCCESS)
	{
		parser__print_syntax_error(error_token);
		return (-1);
	}
	// if (parser__envp_replace(&str, envp) != 0)
		// return (-2);
	if (fill_commlist(str, out_commlist) != 0)
		return (-3);
	return (0);
}

static int	fill_commlist(char *str, t_commlist **commlist)
{
	t_operation	op;

	*commlist = NULL;
	while (ft_isspace(*str))
		++str;
	while (*str)
	{
		op = parser__is_oper(str);
		if (op != OP_NONE)
			str += 1 + (op == OP_REDIR2L || op == OP_REDIR2R);
		if (fill_commlist__push_elem(&str, commlist, op) != 0)
		{
			commlist_clear(*commlist);
			return (-1);
		}
		while (ft_isspace(*str))
			++str;
	}
	return (0);
}

static int	fill_commlist__push_elem(char **str, t_commlist **commlist,
				t_operation oper)
{
	t_commlist	*tmp;
	char		**argv;

	argv = parser__get_argv(str);
	if (!argv)
		return (-1);
	tmp = commlist_create(argv);
	if (!tmp)
		return (-1);
	commlist_push_back(commlist, tmp);
	tmp->op_prev = oper;
	if (tmp->prev)
		tmp->prev->op_next = oper;
	return (0);
}
