#include "minishell.h"

int	g_flag;

int	main(int argc, char **argv, char **envp)
{
	t_commlist	*commands;
	t_envp		*envp_copy;
	char		*input;

	(void)argc;
	(void)argv;
	if (!envp)
		return (0);
	signal(SIGINT, handler_sigint);
	rl_catch_signals = 0;
	envp_copy = envp_create(envp);

	while (1)
	{
		input = readline(SHELL_NAME);
		g_flag = 0;
		if (input == NULL)
		{
			printf("\e[A%sexit\n", SHELL_NAME);
			break;
		}
		if (*input && !g_flag)
		{
			add_history(input);
		}
		if (parse_input(&input, &commands, envp_copy) == 0)
			command_processing(&commands, envp_copy);
		commlist_clear(commands);
		free(input);
	}
	return (0);
}

//readline,
//rl_on_new_line,
//rl_replace_line,
//rl_redisplay,
//add_history
