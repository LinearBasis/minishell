#include "parser.h"

static size_t	count_words(char *str);

char	**parser__get_argv(char **str)
{
	size_t		argc;
	size_t		index;
	char		**argv;

	argc = count_words(*str);
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	argv[argc] = NULL;
	index = 0;
	while (index < argc)
	{
		argv[index] = parser__get_word(str);
		if (!argv[index])
		{
			while (index--)
				free(argv[index]);
			free(argv);
			return (NULL);
		}
		index++;
	}
	return (argv);
}

static size_t	count_words(char *str)
{
	size_t	count;
	char	qoute_flag;

	while (ft_isspace(*str))
		++str;
	count = 0;
	while (*str && parser__is_oper(str) == OP_NONE)
	{
		qoute_flag = 0;
		if (*str == '\'' || *str == '\"')
		{
			qoute_flag = *str;
			++str;
		}
		while (*str && ((qoute_flag && *str != qoute_flag) || (!qoute_flag
			&& !ft_isspace(*str) && parser__is_oper(str) == OP_NONE)))
			str++;
		if (qoute_flag)
			str++;
		++count;
		while (*str && ft_isspace(*str))
			str++;

	}
	return (count);
}

char	*parser__get_word(char **str)
{
	size_t	size;
	char	*out;
	char	*tmp;
	char	qoute_flag;

	while (ft_isspace(**str))
		++(*str);
	qoute_flag = 0;
	if (**str == '\'' || **str == '\"')
	{
		qoute_flag = **str;
		++(*str);
	}
	size = 0;
	tmp = *str;
	while (*tmp && ((qoute_flag && *tmp != qoute_flag) || (!qoute_flag
		&& !ft_isspace(*tmp)&& parser__is_oper(tmp) == OP_NONE)))
	{
		++tmp;
		++size;
	}
	out = malloc(sizeof(char) * (size + 1));
	if (!out)
		return (NULL);
	out[size] = '\0';
	tmp = out;
	while (size--)
	{
		*tmp = **str;
		++tmp;
		++(*str);
	}
	if (qoute_flag)
		++(*str);
	return (out);
}
