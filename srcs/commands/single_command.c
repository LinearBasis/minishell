#include "commands.h"

int	handle_command(char **command, t_envp *envp)
{
	int		status;
	size_t	index;

	if (!command || !command[0])
		status = 1;
	else if (!ft_strcmp(command[0], "echo"))	// TODO
		status = builtin_echo(command);
	else if (!ft_strcmp(command[0], "cd"))
		status = builtin_cd(command, envp);
	else if (!ft_strcmp(command[0], "pwd"))
		status = builtin_pwd(command);
	// else if (!ft_strcmp(command[0], "export"))
	// 	builtin_export(command, envp);
	// else if (!ft_strcmp(command[0], "unset"))
	// 	builtin_unset(command, envp);
	// else if (!ft_strcmp(command[0], "env"))
	// 	builtin_env(command, envp);
	// else if (!ft_strcmp(command[0], "exit"))
	// 	builtin_exit(command);
	else
		status = exec_command(command, envp);
	index = 0;
	while (command[index++])
		free(command[index - 1]);
	free(command);
	exit(status);
}
