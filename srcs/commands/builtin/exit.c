#include "commands.h"

int		ft_is_digit(char *c, int *put_here)
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

int		builtin_exit(char **command)
{
	int	exit_status;

	exit_status = 0;
	if (command[1] != NULL && command[2] != NULL)
		return (perror__builtin((const char **)command, -1,  TOO_MANY_ARGS));
	printf("imhere\n");
	if (!ft_is_digit(command[2], &exit_status))
		perror__builtin((const char **)command, -1, NUMERIC_ARG_REQUIRED);
	exit(exit_status);
}