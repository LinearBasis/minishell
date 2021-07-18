#include "commands.h"

static int	pipe_parse(t_commlist *commands);
static int	redir_parse(t_commlist **commands);
static int	exec_process(t_commlist *commands, t_envp *envp);

int	command_processing(t_commlist *commands, t_envp *envp)
{
	int		status;

	commlist_print(commands);
	if (pipe_parse(commands) != 0)
		return (-1);
	commlist_print(commands);
	if (redir_parse(&commands) != 0)
		return (-2);
	if (exec_process(commands, envp) != 0)
		return (-3);
	wait(&status);
	if (status == -1)
	{
		perror("Wait error");
		return (-4);
	}
	return (0);
}

static int	pipe_parse(t_commlist *commands)
{
	int			pipe_fds[2];
	t_commlist	*iter;

	iter = commands;
	while (iter)
	{
		if (iter->op_next == OP_PIPE)
		{
			if (pipe(pipe_fds) != 0)
			{
				perror("Can't create pipe");
				return (-1);
			}
			iter->fd_out = pipe_fds[1];
			iter->next->fd_in = pipe_fds[0];
		}
		iter = iter->next;
	}
	return (0);
}

static int	redir_parse(t_commlist **commands)
{
	
	return (0);
}

static int	exec_process(t_commlist *commands, t_envp *envp)
{
	(void)commands;
	(void)envp;
	return (0);
}