#include "minishell.h"

int		cmd_exit(int argc, char **argv)
{
	printf("EXIT CMD [ %d | %p ]\n", argc, argv);
	return (0);
}
