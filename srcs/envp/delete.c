#include "envp.h"


static int	remove_by_index(t_envp *exp, int index)
{
	free(exp->envp_cpy[index]);
	free(exp->envp_key_value[0][index]);
	free(exp->envp_key_value[1][index]);

	while (exp->envp_cpy[index])
	{
		exp->envp_cpy[index] = exp->envp_cpy[index + 1];
		exp->envp_key_value[0][index] = exp->envp_key_value[0][index + 1];
		exp->envp_key_value[1][index] = exp->envp_key_value[1][index + 1];
		index++;
	}
	return (GOOD_RETURN);
}

int			envp_remove(t_envp *exp, char *key)
{
	int	delete_index;

	delete_index = envp_find_key_index(exp, key);
	if (delete_index < 0)
	{
		// printf("%s not found\n", key);
		return (GOOD_RETURN);
	}
	// printf("removed %s\n", exp->envp_key_value[0][delete_index]);
	return (remove_by_index(exp, delete_index));
}