#include "commands.h"

int	ft_is_digit(char *c, int *put_here)
{
	int		i;

	i = 0;
	if (c[i] == '-' || c[i] == '+')
		i++;
	while (c[i])
	{
		if (!ft_isdigit(c[i]))
			return (0);
		i++;
	}
	*put_here = ft_atoi(c);
	return (1);
}

int	builtin_exit(char **command, t_commlist *cl_root)
{
	int	exit_status;

	exit_status = g_last_exit_code;
	printf("exit\n");
	if (!command[1])
		exit((exit_status % 256 + 256) % 256);
	if (command[1] && !ft_is_digit(command[1], &exit_status))
	{
		perror__builtin((const char **)command, -1, NUMERIC_ARG_REQUIRED);
		exit_status = 255;
	}
	else if (command[1] != NULL && command[2] != NULL)
		return (perror__builtin((const char **)command, 1, TOO_MANY_ARGS));
	exit_status %= 256;
	if (exit_status < 0)
		exit_status += 256;
	commlist_clear(cl_root);
	exit(exit_status);
}
