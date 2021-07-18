#include "commands.h"

static void	redir_left_uno(t_commlist **commands);
static void	redir_left_uno2(t_commlist *iter, t_commlist **redir_target,
				int *last_fd);
static void	redir_right_all(t_commlist **commands);
static void	redir_right_all2(t_commlist *iter, t_commlist **redir_target,
				int *last_fd);

int	commands__redir_parser(t_commlist **commands)
{
	redir_left_uno(commands);
	redir_right_all(commands);
	return (0);
}

static void	redir_left_uno(t_commlist **commands)
{
	t_commlist	*iter;
	t_commlist	*tmp;
	t_commlist	*redir_target;
	int			last_fd;

	last_fd = 0;
	redir_target = NULL;
	iter = *commands;
	while (iter)
	{
		if (iter->op_prev == OP_REDIRL)
		{
			redir_left_uno2(iter, &redir_target, &last_fd);
			tmp = iter;
			iter = iter->next;
			commlist_remove_elem(commands, tmp);
		}
		else
		{
			if (iter->op_prev == OP_NONE)
				redir_target = iter;
			iter = iter->next;
		}
	}
}

static void	redir_left_uno2(t_commlist *iter, t_commlist **redir_target,
				int *last_fd)
{
	if (*last_fd)
		close(*last_fd);
	*last_fd = open(iter->argv[0], O_RDONLY);
	if (*last_fd < 0)
		perror("Can't open file");
	if (iter->op_next != OP_REDIRL)
	{
		if (*redir_target)
			(*redir_target)->fd_in = *last_fd;
		else
			iter->next->fd_in = *last_fd;
		*last_fd = 0;
		*redir_target = NULL;
	}
}

static void	redir_right_all(t_commlist **commands)
{
	t_commlist	*iter;
	t_commlist	*tmp;
	t_commlist	*redir_target;
	int			last_fd;

	last_fd = 0;
	redir_target = NULL;
	iter = *commands;
	while (iter)
	{
		if (iter->op_prev == OP_REDIRR || iter->op_prev == OP_REDIR2R)
		{
			redir_right_all2(iter, &redir_target, &last_fd);
			tmp = iter;
			iter = iter->next;
			commlist_remove_elem(commands, tmp);
			continue ;
		}
		else if (iter->op_next == OP_REDIRR || iter->op_next == OP_REDIR2R)
			redir_target = iter;
		iter = iter->next;
	}
}

static void	redir_right_all2( t_commlist *iter, t_commlist **redir_target,
				int *last_fd)
{
	if (*last_fd)
		close(*last_fd);
	if (iter->op_prev == OP_REDIRR)
		*last_fd = open(iter->argv[0], O_WRONLY | O_CREAT);
	else
		*last_fd = open(iter->argv[0], O_WRONLY | O_APPEND | O_CREAT);
	if (*last_fd < 0)
		perror("Can't open file");
	if (iter->op_next != OP_REDIRR && iter->op_next != OP_REDIR2R)
	{
		if (*redir_target)
			(*redir_target)->fd_out = *last_fd;
		else
			iter->next->fd_out = *last_fd;
		*last_fd = 0;
		*redir_target = NULL;
	}
}
