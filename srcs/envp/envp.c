#include "envp.h"
#include <stdio.h>

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
	_copy_envp(ans, envp, i);
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
		printf("%s = >>> %s <<<\n\n", exp->envp_key_value[0][i], exp->envp_key_value[1][i]);
		i++;
	}
}



