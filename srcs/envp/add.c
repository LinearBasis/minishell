#include "envp.h"

static int	_add_key_value_to_env(t_envp *env, char *key, char *value)
{
	char	**new_key_value[2];
	int		size;
	int		i;

	size = -1;
	while (env->envp_key_value[0][++size])
	{
		if (!ft_strcmp(key, env->envp_key_value[0][size]))
		{
			free(key);
			free(env->envp_key_value[1][size]);
			env->envp_key_value[1][size] = value;
			return (0);
		}
	}
	new_key_value[0] = ft_realloc(env->envp_key_value[0], sizeof(char *) * (size), sizeof(char *) * (size + 2));
	if (!new_key_value[0])
		return (-1);
	new_key_value[1] = ft_realloc(env->envp_key_value[1], sizeof(char *) * (size), sizeof(char *) * (size + 2));
	if (!new_key_value[1])
	{
		free(new_key_value[0]);
		return (-1);
	}
	new_key_value[0][size] = key;
	new_key_value[1][size] = value;
	new_key_value[0][size + 1] = NULL;
	new_key_value[1][size + 1] = NULL;
	env->envp_key_value[0] = new_key_value[0];
	env->envp_key_value[1] = new_key_value[1];
	return (0);
}

int			add_to_env(t_envp *env, char *str)
{
	int		i;
	char	*key;
	char	*value;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	value = NULL;
	while (str[i] != '=' && str[i])
		++i;
	if (i <= len - 1)
	{
		if (i == len - 1)
			value = ft_strdup("");
		else
			value = ft_substr_from_to(str, i + 1, len);
		if (!value)
			return (-1);
	}
	key = ft_substr_from_to(str, 0, i);
	if (!key)
	{
		free(value);
		return (-1);
	}
	return (_add_key_value_to_env(env, key, value));
}