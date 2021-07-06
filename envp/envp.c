#include "envp.h"
#include <stdio.h>


//		ТРЕБУЕТСЯ ПРОВЕРКА НА ЛИКИ, ВРОДЕ ВСЕ НАКОСТЫЛЕНО ХОРОШО, НО КТО ЗНАЕТ

static int	_add_key_value_to_env(t_export *env, char *key, char *value)
{
	char	**new_key_value[2];
	int		size;
	int		i;

	size = 0;
	while (env->envp_key_value[0][size])
	{

		if (!ft_strcmp(key, env->envp_key_value[0][size]))
		{
			free(env->envp_key_value[1][size]);
			env->envp_key_value[1][size] = value;
			return (0);
		}
		++size;
	}
	printf("asd\n");
	new_key_value[0] = malloc(sizeof(char *) * (size + 2));
	if (!new_key_value[0])
		return (-1);
	new_key_value[1] = malloc(sizeof(char *) * (size + 2));
	if (!new_key_value[1])
	{
		free(new_key_value[0]);
		return (-1);
	}
	i = 0;
	while (i < size)
	{
		new_key_value[0][i] = env->envp_key_value[0][i];
		new_key_value[1][i] = env->envp_key_value[1][i];
		++i;
	}
	new_key_value[0][i] = key;
	new_key_value[1][i] = value;
	new_key_value[0][i + 1] = NULL;
	new_key_value[1][i + 1] = NULL;

	free(env->envp_key_value[0]);
	free(env->envp_key_value[1]);
	env->envp_key_value[0] = new_key_value[0];
	env->envp_key_value[1] = new_key_value[1];
	return (0);
}

int			add_to_env(t_export *env, char *str)
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
		{
			value = ft_substr_from_to(str, i, len);
		}
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

int		_fill_one_export(t_export *ans, char *env, int i)
{
	int		len;
	char	*a2;
	char	*a3;

	len = 0;
	while (env[len] != '=')
		len++;									//	TODO
	a2 = ft_substr_from_to(env, 0, len);
	a3 = ft_substr_from_to(env, len + 1, (int)ft_strlen(env));
	ans->envp_key_value[0][i] = NULL;
	ans->envp_key_value[1][i] = NULL;
	if (!a2 || !a3)
	{
		free(a2);
		free(a3);
		return (-1);
	}
	ans->envp_key_value[0][i] = a2;
	ans->envp_key_value[1][i] = a3;
	return (0);
}

static int	copy_envp(t_export *ans, char **envp, int i)
{
	int		j;
	int		len;
	char	**tmp;

	j = 0;
	while (j < i)
	{
		if (_fill_one_export(ans, envp[j], j) != 0)
		{
			clear_export(ans);
			return (-1);
		}
		j++;
	}
	ans->envp_key_value[0][i] = 0;
	ans->envp_key_value[1][i] = 0;
	return (0);
}

t_export	*create_export(char **envp)
{
	int			i;
	t_export	*ans;

	i = 0;
	while (envp[i])
		i++;
	ans = calloc(1, sizeof(t_export));		//TODO
	if (!ans)
		return ans;
	ans->envp_key_value[0] = (char **)malloc(sizeof(char *) * (i + 1));
	ans->envp_key_value[1] = (char **)malloc(sizeof(char *) * (i + 1));

	if (!ans->envp_key_value[0] || !ans->envp_key_value[1])
	{
		clear_export(ans);
		return (NULL);
	}
	copy_envp(ans, envp, i);
	return (ans);
}

static void	clear_nullptred_array(char **arr)
{
	int i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i]);
		free(arr);
	}
}

void		clear_export(t_export *exp)
{
	int i;

	if (!exp)
		return ;
	clear_nullptred_array(exp->envp_key_value[0]);
	clear_nullptred_array(exp->envp_key_value[1]);
	free(exp);
}

void		print_env(t_export *exp)
{
	int	i;

	i = 0;
	while (exp->envp_key_value[0][i])
	{
		printf("%s = %s\n\n", exp->envp_key_value[0][i], exp->envp_key_value[1][i]);
		i++;
	}
}