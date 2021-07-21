#include "commands.h"
#include "signals.h"

static int		builtin_heredoc(char *command);
static void		builtin_heredoc_exec(char *command, int fd_out);
static int		redir_left_double__fd_proc(t_commlist *iter,
					t_commlist **redir_target, int *last_fd);
static void		redir_left_double__delete_n_merge(t_commlist **commands,
					t_commlist **iter);

int	redir_left_double(t_commlist **commands)
{
	t_commlist	*iter;
	t_commlist	*redir_target;
	int			last_fd;

	last_fd = 0;
	redir_target = NULL;
	iter = *commands;
	while (iter)
	{
		if (iter->op_prev == OP_REDIR2L)
		{
			if (redir_left_double__fd_proc(iter, &redir_target, &last_fd) != 0)
				return (-1);
			redir_left_double__delete_n_merge(commands, &iter);
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

static int	redir_left_double__fd_proc(t_commlist *iter,
				t_commlist **redir_target, int *last_fd)
{
	if (*last_fd)
		close(*last_fd);
	*last_fd = builtin_heredoc(iter->argv[0]);
	if (*last_fd < 0)
		return (perror__errno(iter->argv[0], -1));
	if (iter->op_next != OP_REDIRL)
	{
		if (*redir_target)
		{
			if ((*redir_target)->fd_in != STDIN_FILENO)
				close ((*redir_target)->fd_in);
			(*redir_target)->fd_in = *last_fd;
			if (iter->fd_out != STDOUT_FILENO)
				(*redir_target)->fd_out = iter->fd_out;
		}
		else if (iter->op_next == OP_NONE && iter->next)
			iter->next->fd_in = *last_fd;
		*last_fd = 0;
		*redir_target = NULL;
	}
	return (0);
}

static void	redir_left_double__delete_n_merge(t_commlist **commands,
				t_commlist **iter)
{
	t_commlist	*tmp;

	tmp = *iter;
	*iter = (*iter)->next;
	commlist_remove_elem(commands, tmp);
	if ((*iter) && (*iter)->op_prev == OP_NONE && (*iter)->prev)
	{
		*iter = (*iter)->prev;
		commlist_merge_two(commands, *iter);
	}
}

static void	handler_in_heredoc(int status)
{
	if (status == 2)
	{
		printf("\n");
		exit(1);
	}
}

static int	builtin_heredoc(char *command)
{
	int	pipe_fds[2];
	int	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(pipe_fds) < 0)
		return (perror__errno("sys/pipe", -1));
	pid = fork();
	if (pid < 0)
		return (perror__errno("sys/fork", -1));
	else if (pid == 0)
	{
		close(pipe_fds[0]);
		builtin_heredoc_exec(command, pipe_fds[1]);
		exit(0);
	}
	close(pipe_fds[1]);
	waitpid(pid, NULL, 0);
	return (pipe_fds[0]);
}

static void	builtin_heredoc_exec(char *command, int fd_out)
{
	char	*input;

	input = NULL;
	signal(SIGINT, handler_in_heredoc);
	signal(SIGQUIT, handler_in_heredoc);
	while (1)
	{
		input = readline("> ");
		if (!input || !ft_strcmp(input, command))
		{
			printf("\033[A> ");
			break ;
		}
		write(fd_out, input, ft_strlen(input));
		write(fd_out, "\n", 1);
	}
	close(fd_out);
}
