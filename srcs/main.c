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

	for (int i = 0; envp_copy->envp_key_value[0][0]; i++)
			{
				envp_remove(envp_copy, envp_copy->envp_key_value[0][0]);
			}
	envp_add(envp_copy, "asd=bef");
	envp_add(envp_copy, "asd=");
	envp_add(envp_copy, "bef");
	envp_print(envp_copy);
	sleep(100);
	return (0);



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
		if (parse_input(&input, &commands, envp_copy) == 0)
			if (command_processing(commands, envp_copy) != 0)
				perror("Error ");
		commlist_clear(commands);
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
// 	exp = envp_create(envp);
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

// 	exp = envp_create(envp);
// 	// envp_add(exp, "a=b");
// 	// envp_add(exp, "TERM=prikol");
// 	// envp_add(exp, "_=HERE");
// 	// envp_add(exp, "a");
// 	// envp_add(exp, "c");
// 	// envp_add(exp, "a=d");
// 	envp_add(exp, "b=");
// 	envp_print(exp);

// 	envp_clear(exp);

// 	// printf("%s - a\n", envp_get_value(exp, "a"));
// 	// printf("%s - z\n", envp_get_value(exp, "z"));
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
