#include "envp.h"

char		*get_env(t_export *exp, char *key)
{
	int	i;

	i = 0;
	while (exp->envp_key_value[0][i])
	{
		if (!ft_strcmp(key, exp->envp_key_value[0][i]))
			return (ft_strdup(exp->envp_key_value[1][i]));
		++i;
	}
	return (NULL);
}