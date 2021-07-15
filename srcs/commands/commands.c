#include "commands.h"

static int	open_file(int *fd, const char *filename);

int	command_processing(t_commlist *commands, t_envp *envp)
{
	int		pipe_fds[2];
	int		prev_fd;
	int		status;
	int		pid;

	//commlist_print(commands);
	prev_fd = -1;
	while (commands)
	{
		if (commands->op_next == OP_PIPE && pipe(pipe_fds) == -1)
		{
			perror("Can't create pipe ");
			return (-1);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("Can't fork ");
			return (-2);
		}
		else if (pid == 0)
		{
			if (prev_fd >= 0)
				dup2(prev_fd, STDIN_FILENO);
			if (commands->op_next == OP_PIPE)
				dup2(pipe_fds[1], STDOUT_FILENO);
			handle_command(commands->data, envp);
		}
		if (prev_fd >= 0)
			close(prev_fd);
		if (commands->op_next == OP_PIPE)
		{
			close(pipe_fds[1]);
			prev_fd = pipe_fds[0];
		}
		else
			prev_fd = -1; 
		commands = commands->next;
	}
	wait(&status);
	if (status == -1)
	{
		perror("Wait error ");
		return (-3);
	}
	printf("\n");
	return (0);
}

static int	open_file(int *fd, const char *filename)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, ": No such file or directory\n", 28);
		return (-1);
	}
	return (0);
}

