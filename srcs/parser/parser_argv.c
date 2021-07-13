#include "parser.h"

static size_t	count_words(char *str);
static char		*get_word(char **str);

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
		argv[index] = get_word(str);
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

static char	*get_word(char **str)
{
	size_t	size;
	char	*out;
	char	*tmp;

	while (ft_isspace(**str))
		++(*str);
	size = 0;
	tmp = *str;
	while (*tmp && !ft_isspace(*tmp) && parser__is_oper(tmp) == OP_NONE)
	{
		++tmp;
		++size;
	}
	out = malloc(sizeof(char) * (size + 1));
	out[size] = '\0';
	if (!out)
		return (NULL);
	tmp = out;
	while (size--)
	{
		*tmp = **str;
		++tmp;
		++(*str);
	}
	return (out);
}
