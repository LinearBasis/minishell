#include "parser.h"

static char		*envp__get_value(char **envp[2], char *key);
static void		replace_keys(char *str, char *dest, char **envp[2]);
static size_t	get_new_len(char *str, char **envp[2]);

int	parser__envp_replace(char **str, t_envp *envp)
{
	size_t	size;
	char	*out;

	size = get_new_len(*str, envp->envp_key_value);
	out = malloc(sizeof(char) * (size + 1));
	if (!out)
		return (-1);
	out[size + 1] = '\0';
	replace_keys(*str, out, envp->envp_key_value);
	free(*str);
	*str = out;
	return (0);
}

static size_t	get_new_len(char *str, char **envp[2])
{
	size_t	size;
	
	size = 0;
	while (str)
	{
		if (str == '$')
			size += ft_strlen(envp__get_value(envp, str + 1));
		else
			++size;
	}
	return (size);
}

static void		replace_keys(char *str, char *dest, char **envp[2])
{
	char	*value;
	
	while (*str)
	{
		if (*str == '$')
		{
			value = envp__get_value(envp, str + 1);
			while (*value)
			{
				*dest = *value;
				dest++;
				value++;
			}
		}
		else
		{
			*dest = *str;
			dest++;
			str++;
		}
	}
}

static char		*envp__get_value(char **envp[2], char *key)
{
	size_t	len;
	size_t	index;

	len = 0;
	while (key[len] && !ft_isspace(key[len])
		&& parser__is_oper(key) == OP_NONE && *key != '$')
		++len;
	index = 0;
	while (envp[KEY][index])
	{
		if (ft_strncmp(envp[KEY][index], key, len) == 0)
			return (envp[VALUE][index]);
		index++;
	}
	return (NULL);
}
