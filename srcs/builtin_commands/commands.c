#include "builtin_commands.h"
#include <string.h>

int	handle_command(char **command, t_envp *exp)
{
	if (!command || !command[0])
		return (1);
	if (!strcmp(command[0], "echo"))	// TODO
		return (builtin_echo(command));
	if (!strcmp(command[0], "cd"))
		builtin_cd(command, exp);
	if (!strcmp(command[0], "pwd"))
		builtin_pwd(command);
	// if (!strcmp(command[0], "export"))
	// 	builtin_export(command, exp);
	// if (!strcmp(command[0], "unset"))
	// 	builtin_unset(command, exp);
	// if (!strcmp(command[0], "env"))
	// 	builtin_env(command, exp);
	// if (!strcmp(command[0], "exit"))
	// 	builtin_exit(command);
	return (0);
}
