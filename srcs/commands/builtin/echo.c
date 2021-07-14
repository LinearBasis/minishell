#include "commands.h"
#include "utils.h"

int	builtin_echo(char **command)
{
	int i = 1;
	int	flag = 0;

	if (command[i])
		while (!ft_strcmp(command[i], "-n"))
		{
			++i;
			++flag;
		}
	i = 1;
	if (command[i])
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