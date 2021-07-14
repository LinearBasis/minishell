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
	envp_copy = create_export(envp);
	while(1)
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
		if (parse_input(input, &commands, envp_copy) == 0)
			if (command_processing(commands, envp_copy) != 0)
				perror("Error ");
		free(input);
	}
	return (0);
}


	//TEST COMMANDS MAIN
// int	main(int argc, char **argv, char **envp)
// {
// 	char	**arr[10];
// 	char	*arr1[] = {"pwd", "-n", "-n", "1", "2", "3", "-n", "4", NULL};
// 	char	*arr2[] = {"cd", "..", NULL};
// 	char	*arr3[] = {"cd", "..", NULL};
// 	char	*arr4[] = {"cd", "..", NULL};
// 	char	*arr5[] = {"cd", "..", NULL};
// 	char	*arr6[] = {"cd", "..", NULL};
// 	char	*arr7[] = {"cd", "..", NULL};
// 	char	*arr8[] = {"cd", "..", NULL};
// 	char	*arr9[] = {"pwd", NULL};


// 	arr[0] = (char **)arr1;
// 	arr[1] = (char **)arr2;
// 	arr[2] = (char **)arr3;
// 	arr[3] = (char **)arr4;
// 	arr[4] = (char **)arr5;
// 	arr[5] = (char **)arr6;
// 	arr[6] = (char **)arr7;
// 	arr[7] = (char **)arr8;
// 	arr[8] = (char **)arr9;

// 	char		*input;
// 	char		**commands;
// 	t_envp	*exp;

// 	if (!envp)
// 		return (0);
// 	signal(SIGINT, handler_sigint);
// 	rl_catch_signals = 0;
// 	exp = create_export(envp);
// 	for (int i = 0; i < 9; i++)
// 	{
// 		handle_command(arr[i], exp);
// 	}
// }



// int	main(int argc, char *argv[], char *envp[])
// {
// 	if (!envp)
// 		return (1);
// 	t_envp	*exp;

// 	exp = create_export(envp);
// 	// add_to_env(exp, "a=b");
// 	// add_to_env(exp, "TERM=prikol");
// 	// add_to_env(exp, "_=HERE");
// 	// add_to_env(exp, "a");
// 	// add_to_env(exp, "c");
// 	// add_to_env(exp, "a=d");
// 	add_to_env(exp, "b=");
// 	print_env(exp);

// 	clear_export(exp);

// 	// printf("%s - a\n", get_env(exp, "a"));
// 	// printf("%s - z\n", get_env(exp, "z"));
// 	sleep(10);
// }

// int		main(int argc, char *argv[])
// {
// 	t_commlist	*lst;

// 	if (argc < 2)
// 		return (-1);
// 	if (parse_input(argv[1], &lst, NULL) == 0)
// 		commlist_print(lst);
// 	return (0);
// }


//readline,
//rl_on_new_line,
//rl_replace_line,
//rl_redisplay,
//add_history
