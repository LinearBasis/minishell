#include "parser.h"

static char		*envp__get_value(char **envp[2], char *key, size_t *key_len);
static void		replace_keys(char *str, char *dest, char **envp[2],
					char *exit_code);
static size_t	get_new_len(char *str, char **envp[2], char *exit_code);

int	parser__envp_replace(char **str, t_envp *envp, int last_exit_code)
{
	size_t	size;
	char	*out;
	char	*exit_code;

	exit_code = ft_itoa(last_exit_code);
	size = get_new_len(*str, envp->envp_key_value, exit_code);
	out = malloc(sizeof(char) * (size + 1));
	if (!out)
	{
		free(exit_code);
		return (-1);
	}
	out[size] = '\0';
	replace_keys(*str, out, envp->envp_key_value, exit_code);
	free(exit_code);
	free(*str);
	*str = out;
	return (0);
}

static size_t	get_new_len(char *str, char **envp[2], char *exit_code)
{
	size_t	size;
	size_t	key_len;
	int		squotes_flag;

	squotes_flag = 0;
	size = 0;
	while (*str)
	{
		key_len = 0;
		if (*str == '\'')
			squotes_flag = !squotes_flag;
		if (*str == '$' && !squotes_flag && *(str + 1))
		{
			if (*(str + 1) == '?')
				size += ft_strlen(exit_code);	
			else if (*(str + 1))
				size += ft_strlen(envp__get_value(envp, str + 1, &key_len));
		}
		else
			++size;
		str += key_len + 1;
	}
	return (size);
}

static void		replace_keys(char *str, char *dest, char **envp[2],
					char *exit_code)
{
	char	*value;
	size_t	key_len;
	int		squotes_flag;

	squotes_flag = 0;
	while (*str)
	{
		if (*str == '\'')
			squotes_flag = !squotes_flag;
		if (*str == '$' && !squotes_flag && *(str + 1))
		{
			value = NULL;
			key_len = 0;
			if (*(str + 1) == '?')
			{
				value = exit_code;
				key_len = 1;
			}
			else if (*(str + 1))
				value = envp__get_value(envp, str + 1, &key_len);
			if (value)
				while (*value)
				{
					*dest = *value;
					dest++;
					value++;
				}
			str += key_len + 1;
		}
		else
		{
			*dest = *str;
			++dest;
			++str;
		}
	}
}

static char		*envp__get_value(char **envp[2], char *key, size_t *key_len)
{
	size_t	index;

	*key_len = 0;
	while (key[*key_len] && !ft_isspace(key[*key_len])
		&& parser__is_oper(key) == OP_NONE
		&& key[*key_len] != '\"' && key[*key_len] != '$')
		++(*key_len);
	index = 0;
	while (envp[KEY][index])
	{
		if (ft_strncmp(envp[KEY][index], key, *key_len) == 0)
			return (envp[VALUE][index]);
		index++;
	}
	return (NULL);
}
