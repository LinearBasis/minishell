#include "header.h"
#include "signals/signals.h"

int	g_flag;

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**commands;

	if (!envp)
		return (0);
	signal(SIGINT, handler_sigint);
	rl_catch_signals = 0;

	while(21)
	{
		input = readline(SHELL_NAME);
		g_flag = 0;
		if (input == NULL)
		{
			printf("\e[A%sexit\n", SHELL_NAME);
			break;
		}
		if (input[0] && !g_flag)
		{
			add_history(input);
		}
		// input = parse();
		//проверка
		check_what_to_do_with_string(input);
		free(input);
	}
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	printf("%s\n", envp[0]);
// 	char	*asd[] = {"cat", "main.c", NULL};
// 	printf("%d\n", execve("/bin/cat", asd, envp));
// }






//readline,
//rl_on_new_line,
//rl_replace_line,
//rl_redisplay,
//add_history