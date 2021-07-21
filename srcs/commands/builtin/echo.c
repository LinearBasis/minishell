#include "commands.h"
#include "utils.h"

int	builtin_echo(char **command)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (command[i])
	{
		while (!ft_strcmp(command[i], "-n"))
		{
			++i;
			++flag;
		}
	}
	while (command[i])
	{
		printf("%s", command[i]);
		if (command[i + 1])
			printf(" ");
		++i;
	}
	if (!flag)
		printf("\n");
	return (0);
}
