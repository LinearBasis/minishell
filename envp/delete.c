#include "envp.h"

int			remove_from_env(t_export *exp, char *key)
{
	size_t	i;
	int		id;
	char	**new_key_value[2];
	size_t	size;

	i = 0;
	size = 0;
	id = -1;
	while (exp->envp_key_value[0][size])
	{
		if (!ft_strcmp(exp->envp_key_value[0][size], key))
			id = (int)size;
		size++;
	}
	if (id == -1)
		return (0);
	new_key_value[0] = malloc(sizeof(char *) * (size));
	if (!new_key_value[0])
		return (-1);
	new_key_value[1] = malloc(sizeof(char *) * (size));
	if (!new_key_value[1])
	{
		free(new_key_value[0]);
		return (-1);
	}
	while (i < (size_t)id)
	{
		new_key_value[0][i] = exp->envp_key_value[0][i];
		new_key_value[1][i] = exp->envp_key_value[1][i];
		i++;
	}
	// printf("%s %s\n", exp->envp_key_value[0][i], exp->envp_key_value[1][i]);
	while (i + 1 < (size_t)size)
	{
		new_key_value[0][i] = exp->envp_key_value[0][i + 1];
		new_key_value[1][i] = exp->envp_key_value[1][i + 1];
		i++;
	}
	new_key_value[0][i] = NULL;
	new_key_value[1][i] = NULL;

	free(exp->envp_key_value[0]);
	free(exp->envp_key_value[1]);
	exp->envp_key_value[0] = new_key_value[0];
	exp->envp_key_value[1] = new_key_value[1];

	return (1);
}