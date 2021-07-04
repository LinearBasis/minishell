#include "do_command.h"

int	do_echo(char **commmand)
{
	int i = 1;
	int	flag = 0;

	while (!strcmp(commmand[i], "-n"))
	{
		++i;
		++flag;
	}
	while (commmand[i])
	{
		write(1, );
	}
}