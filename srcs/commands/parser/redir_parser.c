#include "commands.h"

static int	redir_left_uno(t_commlist **commands);
static int	redir_left_uno2(t_commlist *iter, t_commlist **redir_target,
				int *last_fd);
static int	redir_right_all(t_commlist **commands);
static int	redir_right_all2(t_commlist *iter, t_commlist **redir_target,
				int *last_fd);

int	commands__redir_parser(t_commlist **commands)
{
	if (redir_left_double(commands) != 0)
		return (-1);
	if (redir_left_uno(commands) != 0)
		return (-2);
	if (redir_right_all(commands) != 0)
		return (-3);
	return (0);
}

static int	redir_left_uno(t_commlist **commands)
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
			if (redir_left_uno2(iter, &redir_target, &last_fd) != 0)
				return (-1);
			tmp = iter;
			iter = iter->next;
			commlist_remove_elem(commands, tmp);
			if (iter && iter->op_prev == OP_NONE && iter->prev)
			{
				iter = iter->prev;
				commlist_merge_two(commands, iter);
			}
		}
		else
		{
			if (iter->op_prev == OP_NONE)
				redir_target = iter;
			iter = iter->next;
		}
	}
	return (0);
}

static int	redir_left_uno2(t_commlist *iter, t_commlist **redir_target,
				int *last_fd)
{
	if (*last_fd)
		close(*last_fd);
	*last_fd = open(iter->argv[0], O_RDONLY);
	if (*last_fd < 0)
		return (perror__errno(iter->argv[0], -1));
	if (iter->op_next != OP_REDIRL)
	{
		if (*redir_target)
		{
			if ((*redir_target)->fd_in != STDOUT_FILENO)
				close ((*redir_target)->fd_out);
			(*redir_target)->fd_in = *last_fd;
		}
		else if (iter->op_next == OP_NONE && iter->next)
			iter->next->fd_in = *last_fd;
		*last_fd = 0;
		*redir_target = NULL;
	}
	return (0);
}

static int	redir_right_all(t_commlist **commands)
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
			if (redir_right_all2(iter, &redir_target, &last_fd) != 0)
				return (-1);
			tmp = iter;
			iter = iter->next;
			commlist_remove_elem(commands, tmp);
			if (iter && iter->op_prev == OP_NONE && iter->prev)
			{
				iter = iter->prev;
				commlist_merge_two(commands, iter);
			}
		}
		else
		{
			if (iter->op_next == OP_REDIRR || iter->op_next == OP_REDIR2R)
				redir_target = iter;
			iter = iter->next;
		}
	}
	return (0);
}

static int	redir_right_all2( t_commlist *iter, t_commlist **redir_target,
				int *last_fd)
{
	if (*last_fd)
		close(*last_fd);
	if (iter->op_prev == OP_REDIRR)
		*last_fd = open(iter->argv[0], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		*last_fd = open(iter->argv[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (*last_fd < 0)
		return (perror__errno(iter->argv[0], -1));
	if (iter->op_next != OP_REDIRR && iter->op_next != OP_REDIR2R)
	{
		if (*redir_target)
		{
			if ((*redir_target)->fd_out != STDOUT_FILENO)
				close ((*redir_target)->fd_out);
			(*redir_target)->fd_out = *last_fd;
		}
		else  if (iter->op_next == OP_NONE && iter->next)
			iter->next->fd_out = *last_fd;
		*last_fd = 0;
		*redir_target = NULL;
	}
	return (0);
}
