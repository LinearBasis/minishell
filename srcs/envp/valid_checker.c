#include "envp.h"

int	is_valid_key(char *key)
{
	// int	i;

	// i = 1;
	// if (!ft_isalpha(key[0]) && key[0] != '_')
	// 	return (INVALID_VAR);
	// while (key[i])
	// {
	// 	if (!ft_isalpha(key[i]) && key[i] != '_' && !ft_isdigit(key[i]))
	// 		return (INVALID_VAR);
	// 	i++;
	// }
	// return (VALID_VAR);
}

int	is_valid_envp_str(char *str)
{
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (INVALID_VAR);
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalpha(key[i]) && key[i] != '_' && !ft_isdigit(key[i]))
			return (INVALID_VAR);
		i++;
	}
	return (VALID_VAR);
}