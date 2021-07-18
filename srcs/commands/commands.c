#include "commands.h"

static int	pipe_parse(t_commlist *commands);
static int	redir_parse(t_commlist *commands);
static int	exec_process(t_commlist *commands, t_envp *envp);

int	command_processing(t_commlist *commands, t_envp *envp)
{
	int		status;

	//commlist_print(commands);
	if (pipe_parse(commands) != 0)
		return (-1);
	if (redir_parse(commands) != 0)
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
	return (0);
}

static int	redir_parse(t_commlist *commands)
{
	return (0);
}

static int	exec_process(t_commlist *commands, t_envp *envp)
{
	return (0);
}