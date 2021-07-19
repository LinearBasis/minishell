#include "commands.h"

static int		exec_process(t_commlist *commands, t_envp *envp, int *pids);
static size_t	count_procesess(t_commlist *commands);

int	command_processing(t_commlist **commands, t_envp *envp)
{
	int		status;
	int		*pids;
	size_t	size;
	size_t	index;

	//commlist_print(*commands);
	if (commands__pipe_parser(*commands) != 0)
		return (-1);
	//commlist_print(*commands);
	if (commands__redir_parser(commands) != 0)
		return (-2);
	//commlist_print(*commands);
	size = count_procesess(*commands);
	pids = malloc(sizeof(int) * size);
	if (!pids)
		return (perror__errno("sys/malloc", -4));
	if (exec_process(*commands, envp, pids) != 0)
	{
		free(pids);
		return (-3);
	}
	index = 0;
	while (index++ < size)
		if (waitpid(pids[index - 1], &status, 0) == -1)
			return (perror__errno("sys/wait", -5));
	free(pids);
	return (WEXITSTATUS(status));
}

static int	exec_process(t_commlist *commands, t_envp *envp, int *pids)
{
	size_t	index;

	index = 0;
	while (commands)
	{
		pids[index] = fork();
		if (pids[index] < 0)
			return (perror__errno("sys/fork", -1));
		else if (pids[index] == 0)
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
		index++;
	}
	
	return (0);
}

static size_t	count_procesess(t_commlist *commands)
{
	size_t	count;

	count = 0;
	while (commands)
	{
		count++;
		commands = commands->next;
	}
	return (count);
}
