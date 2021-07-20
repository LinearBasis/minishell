#include "commands.h"
#include "minishell.h"

int		builtin_heredoc(char *command)
{
	char	*input;
	int		fd_heredoc;

	input = NULL;
	fd_heredoc = open(".heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (!fd_heredoc)
		return (perror__errno("heredoc", 1));
	while (1)
	{
		input = readline("> ");
		if (!input)
			return (0);
		write(fd_heredoc, input, ft_strlen(input));
		write(fd_heredoc, "\n", 1);
	}
	
}