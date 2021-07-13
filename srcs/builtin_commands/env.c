#include "do_command.h"

int		builtin_env(char ** command, t_export *exp)
{
	int	i;

	i = 0;
	while (exp->envp_key_value[0][i])
	{
		if (exp->envp_key_value[1][i])
			printf("%s=%s\n", exp->envp_key_value[0][i], exp->envp_key_value[1][i]);
		i++;
	}
	return (0);
}
