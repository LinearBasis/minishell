#include "commands.h"

static int	exec_process(t_commlist *commands, t_envp *envp);

int	command_processing(t_commlist **commands, t_envp *envp)
{
	int		status;

	//commlist_print(*commands);
	if (commands__pipe_parser(*commands) != 0)
		return (-1);
	//commlist_print(*commands);
	if (commands__redir_parser(commands) != 0)
		return (-2);
	//commlist_print(*commands);
	if (exec_process(*commands, envp) != 0)
		return (-3);
	wait(&status);
	if (status == -1)
		return (perror__errno("sys/wait", -4));
	return (0);
}

static int	exec_process(t_commlist *commands, t_envp *envp)
{
	int		pid;

	while (commands)
	{
		pid = fork();
		if (pid < 0)
			return (perror__errno("sys/fork", -1));
		else if (pid == 0)
		{
			if (commands->fd_in != STDIN_FILENO)
				dup2(commands->fd_in, STDIN_FILENO);
			if (commands->fd_out != STDIN_FILENO)
				dup2(commands->fd_out, STDOUT_FILENO);
			handle_command(commands->argv, envp);
		}
		if (commands->fd_in != STDIN_FILENO)
			close(commands->fd_in);
		if (commands->fd_out != STDOUT_FILENO)
			close(commands->fd_out);
		commands = commands->next;
	}
	return (0);
}