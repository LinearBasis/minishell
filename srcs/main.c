#include "minishell.h"

int	g_flag;

int	minishell(t_envp *envp, int last_exit_code)
{
	t_commlist	*commands;
	char		*input;

	while (1)
	{
		signal(SIGINT, handler_sigint);
		signal(SIGQUIT, handler_sigquit);
		printf("\e[s");
		input = readline(SHELL_NAME);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (input == NULL)
		{
			printf("\e[u%sexit\n", SHELL_NAME);
			return (g_flag);
		}

		if (*input && !g_flag)
			add_history(input);
		g_flag = 0;
		if (parse_input(&input, &commands, envp, last_exit_code) == 0)
			last_exit_code = command_processing(&commands, envp);
		commlist_clear(commands);
		free(input);
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_envp		*envp_copy;
	int			ret_status;

	(void)argc;
	(void)argv;
	if (!envp)
		return (0);
	rl_catch_signals = 0;
	envp_copy = envp_create(envp);
	ret_status = minishell(envp_copy, 0);
	envp_clear(envp_copy);
	rl_clear_history();
	return (ret_status);
}

//readline,
//rl_on_new_line,
//rl_replace_line,
//rl_redisplay,
//add_history
