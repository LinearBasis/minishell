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

	while (ft_isspace(*str))
		++str;
	count = 0;
	while (*str && parser__is_oper(str) == OP_NONE)
	{
		while (*str && !ft_isspace(*str) && parser__is_oper(str) == OP_NONE)
			str++;
		++count;
		while (*str && ft_isspace(*str))
			str++;
	}
	return (count);
}
static size_t	parser__get_word__get_len(char **str);
static void		parser__get_word__copy_word(char **s, char *dst);

char	*parser__get_word(char **str)
{
	size_t	size;
	char	*out;

	size = parser__get_word__get_len(str);
	out = malloc(sizeof(char) * (size + 1));
	if (!out)
		return (NULL);
	parser__get_word__copy_word(str, out);
	out[size] = '\0';
	return (out);
}

static size_t	parser__get_word__get_len(char **str)
{
	size_t	size;
	char	*tmp;
	char	qoute_flag;
	char	curr_quote;

	while (ft_isspace(**str))
		++(*str);
	curr_quote = 1;
	qoute_flag = 0;
	size = 0;
	tmp = *str;
	while (*tmp && !ft_isspace(*tmp) && parser__is_oper(tmp) == OP_NONE)
	{
		if (qoute_flag && *tmp == curr_quote)
		{
			qoute_flag = 0;
			curr_quote = 1;
		}
		else if (!qoute_flag && (*tmp == '\'' || *tmp == '\"'))
		{
			qoute_flag = 1;
			curr_quote = *tmp;
		}
		else if (*tmp != curr_quote)
			++size;
		++tmp;
	}
	return (size);
}

static void	parser__get_word__copy_word(char **str, char *dest)
{
	char	qoute_flag;
	char	curr_quote;

	curr_quote = 1;
	qoute_flag = 0;
	while (**str && !ft_isspace(**str) && parser__is_oper(*str) == OP_NONE)
	{
		if (qoute_flag && **str == curr_quote)
		{
			qoute_flag = 0;
			curr_quote = 1;
		}
		else if (!qoute_flag && (**str == '\'' || **str == '\"'))
		{
			qoute_flag = 1;
			curr_quote = **str;
		}
		else if (**str != curr_quote)
		{
			*dest = **str;
			++dest;
		}
		++(*str);
	}
}
