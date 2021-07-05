#include "envp.h"
#include <stdio.h>


//		ТРЕБУЕТСЯ ПРОВЕРКА НА ЛИКИ, ВРОДЕ ВСЕ НАКОСТЫЛЕНО ХОРОШО, НО КТО ЗНАЕТ

int			add_to_env(t_export *env, char *str)
{
	int i = 0;
}

int		_fill_one_export(t_export *ans, char *env, int i)
{
	int		len;
	char	*a1;
	char	*a2;
	char	*a3;

	len = 0;
	while (env[len] != '=')
		len++;
	a1 = ft_strdup(env);										//	TODO
	a2 = ft_substr_from_to(env, 0, len);
	a3 = ft_substr_from_to(env, len + 1, (int)ft_strlen(env));
	ans->envp_cpy[i] = NULL;
	ans->envp_key_value[0][i] = NULL;
	ans->envp_key_value[1][i] = NULL;
	if (!a1 || !a2 || !a3)
	{
		free(a1);
		free(a2);
		free(a3);
		return (-1);
	}
	ans->envp_cpy[i] = a1;
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
	ans->envp_cpy[i] = 0;
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
	ans->envp_cpy = (char **)malloc(sizeof(char *) * (i + 1));
	ans->envp_key_value[0] = (char **)malloc(sizeof(char *) * (i + 1));
	ans->envp_key_value[1] = (char **)malloc(sizeof(char *) * (i + 1));

	if (!ans->envp_key_value[0] || !ans->envp_key_value[1] || !ans->envp_cpy)
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
	clear_nullptred_array(exp->envp_cpy);
	clear_nullptred_array(exp->envp_key_value[0]);
	clear_nullptred_array(exp->envp_key_value[1]);
	free(exp);
}

void		print_env(t_export *exp)
{
	int	i;

	i = 0;
	while (exp->envp_cpy[i])
	{
		printf("%s\n", exp->envp_cpy[i]);
		printf("%s = %s\n\n", exp->envp_key_value[0][i], exp->envp_key_value[1][i]);
		i++;
	}

}