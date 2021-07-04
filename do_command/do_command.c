#include "do_command.h"

void	check_what_to_do_with_command(char **command, t_export *exp)
{
	if (!command || !command[0])
		return ;
	if (!strcmp(command[0], "echo"))	// TODO
		do_echo(command);
	if (!strcmp(command[0], "cd"))
		do_cd(command);
	if (!strcmp(command[0], "pwd"))
		do_pwd(command);
	if (!strcmp(command[0], "export"))
		do_export(command, exp);
	if (!strcmp(command[0], "unset"))
		do_unset(command, exp);
	if (!strcmp(command[0], "env"))
		do_env(command, exp);
	if (!strcmp(command[0], "exit"))
		do_exit(command);
}
