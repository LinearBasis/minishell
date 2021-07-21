#include "commands.h"
#include "signals.h"

static int		exec_processes_prepare(t_commlist *commands, t_envp *envp);
static int		exec_processes(t_commlist *commands, t_envp *envp, int *pids);
static int		exec_single_builtin(t_commlist *commands, t_envp *envp,
					int *status);
static size_t	count_procesess(t_commlist *commands);

int	command_processing(t_commlist **commands, t_envp *envp)
{
	//commlist_print(*commands);
	if (commands__pipe_parser(*commands) != 0)
		return (-1);
	// commlist_print(*commands);
	if (redir_left_double(commands) != 0)
		return (-2);
	if (redir_left_uno(commands) != 0)
		return (-3);
	if (redir_right_all(commands) != 0)
		return (-4);
	commlist_print(*commands);
	return (exec_processes_prepare(*commands, envp));
}

static int	exec_processes_prepare(t_commlist *commands, t_envp *envp)
{
	int		status;
	int		*pids;
	size_t	size;
	size_t	index;

	size = count_procesess(commands);
	if (size == 0)
		return (0);
	if (size == 1 && is_builtin_command(commands->argv))
		return (exec_single_builtin(commands, envp, &status));
	pids = malloc(sizeof(int) * size);
	if (!pids)
		return (perror__errno("sys/malloc", -4));
	if (exec_processes(commands, envp, pids) != 0)
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

static int	exec_processes(t_commlist *commands, t_envp *envp, int *pids)
{
	ssize_t	index;

	index = -1;
	while (commands)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		pids[++index] = fork();
		if (pids[index] < 0)
			return (perror__errno("sys/fork", -1));
		else if (pids[index] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			dup2(commands->fd_in, STDIN_FILENO);
			dup2(commands->fd_out, STDOUT_FILENO);
			exit(handle_command(commands->argv, envp));
		}
		if (commands->fd_in != STDIN_FILENO)
			close(commands->fd_in);
		if (commands->fd_out != STDOUT_FILENO)
			close(commands->fd_out);
		commands = commands->next;
	}
	return (0);
}

static int	exec_single_builtin(t_commlist *commands, t_envp *envp,
					int *status)
{
	int	stdout_fd;
	int	stdin_fd;

	if (commands->fd_in)
	{
		stdin_fd = dup (STDIN_FILENO);
		dup2(commands->fd_in, STDIN_FILENO);
	}
	if (commands->fd_out)
	{
		stdout_fd = dup(STDOUT_FILENO);
		dup2(commands->fd_out, STDOUT_FILENO);
	}
	*status = handle_command(commands->argv, envp);
	if (commands->fd_in)
	{
		close(commands->fd_in);
		dup2(stdin_fd, STDIN_FILENO);
	}
	if (commands->fd_out)
	{
		close(commands->fd_out);
		dup2(stdout_fd, STDOUT_FILENO);
	}
	return (*status);
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
