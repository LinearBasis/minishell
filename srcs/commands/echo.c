#include "do_command.h"

#include <string.h>

int	builtin_echo(char **commmand)
{
	int i = 1;
	int	flag = 0;

	while (!strcmp(commmand[i], "-n"))		//TODO
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