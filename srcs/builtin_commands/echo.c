#include "builtin_commands.h"
#include "utils.h"

int	builtin_echo(char **commmand)
{
	int i = 1;
	int	flag = 0;

	while (!ft_strcmp(commmand[i], "-n"))
	{
		++i;
		++flag;
	}
	while (commmand[i])
	{
		printf("%s", commmand[i]);
		if (commmand[i + 1])
			printf(" ");
		++i;
	}
	if (!flag)
		printf("\n");
	return (0);
}