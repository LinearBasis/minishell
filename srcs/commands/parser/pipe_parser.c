#include "commands.h"

int	commands__pipe_parser(t_commlist *commands)
{
	int			pipe_fds[2];
	t_commlist	*iter;

	iter = commands;
	while (iter)
	{
		if (iter->op_next == OP_PIPE)
		{
			if (pipe(pipe_fds) != 0)
				return (perror__errno("sys/pipe", -1));
			iter->fd_out = pipe_fds[1];
			iter->next->fd_in = pipe_fds[0];
		}
		iter = iter->next;
	}
	return (0);
}
