#include "commands.h"

static void		close_fds_n_switch(t_commlist **commands);
static void		close_next_fds(t_commlist *commands);

int	exec_all_processes(t_commlist *commands, t_envp *envp, int *pids)
{
	ssize_t	index;
	int		st;

	st = EX_OK;
	index = -1;
	while (commands)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		pids[++index] = fork();
		if (pids[index] < 0)
			return (perror__errno("sys", EX_OSERR));
		else if (pids[index] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			err_assign2(dup2(commands->fd_in, STDIN_FILENO), EX_OSERR, &st);
			err_assign2(dup2(commands->fd_out, STDOUT_FILENO), EX_OSERR, &st);
			close_next_fds(commands);
			if (st == EX_OK)
				st = handle_command(commands->argv, envp);
			exit(st);
		}
		close_fds_n_switch(&commands);
	}
	return (st);
}

static void	close_fds_n_switch(t_commlist **commands)
{
	if ((*commands)->fd_in != STDIN_FILENO)
		close((*commands)->fd_in);
	if ((*commands)->fd_out != STDOUT_FILENO)
		close((*commands)->fd_out);
	*commands = (*commands)->next;
}

static void	close_next_fds(t_commlist *commands)
{
	while (commands)
		close_fds_n_switch(&commands);
}
