#include "commands.h"
#include "signals.h"
#include "minishell.h"

static int		builtin_heredoc(char *command);
static int		builtin_heredoc_exec(char *command);
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

static int	builtin_heredoc(char *command)
{
	int	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (perror__errno("sys/fork", -1));
	else if (pid == 0)
	{
		builtin_heredoc_exec(command);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (open(HEREDOC_FILE, O_RDONLY));
}

static void	handler_in_heredoc(int status)
{
	if (status == 2)
	{
		write(1, "\n", 1);
		readline(NULL);
		exit(0);
	}
}

static int	builtin_heredoc_exec(char *command)
{
	char	*input;
	int		fd_heredoc;

	input = NULL;
	g_flag = 0;
	fd_heredoc = open(HEREDOC_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (!fd_heredoc)
		return (perror__errno("heredoc", 1));
	signal(SIGINT, handler_in_heredoc);
	signal(SIGQUIT, handler_in_heredoc);
	while (1)
	{
		printf("\e[s");
		input = readline("> ");
		if (!input || !ft_strcmp(input, command) || g_flag == 1)
		{
			if (!input)
				printf("\e[u> ");
			break ;
		}
		write(fd_heredoc, input, ft_strlen(input));
		write(fd_heredoc, "\n", 1);
		free(input);
	}
	close(fd_heredoc);
	return (GOOD_RETURN);
}
