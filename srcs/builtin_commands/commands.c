#include "do_command.h"
#include <string.h>

int	handle_command(char **command, t_envp *exp)
{
	if (!command || !command[0])
		return (1);
	if (!strcmp(command[0], "echo"))	// TODO
		return (do_echo(command));
	if (!strcmp(command[0], "cd"))
		do_cd(command, exp);
	if (!strcmp(command[0], "pwd"))
		do_pwd(command);
	// if (!strcmp(command[0], "export"))
	// 	do_export(command, exp);
	// if (!strcmp(command[0], "unset"))
	// 	do_unset(command, exp);
	// if (!strcmp(command[0], "env"))
	// 	do_env(command, exp);
	// if (!strcmp(command[0], "exit"))
	// 	do_exit(command);
	return (0);
}
