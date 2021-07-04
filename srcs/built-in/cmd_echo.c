#include "minishell.h"

int		cmd_echo(int argc, char **argv)
{
	printf("ECHO CMD [ %d | %p ]\n", argc, argv);
	return (0);
}
