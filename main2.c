#include "header.h"
#include "signals/signals.h"
#include "envp/envp.h"
#include "do_command/do_command.h"
#include "utils/utils.h"

int	g_flag;

// int	main(int argc, char **argv, char **envp)
// {
// 	char		*input;
// 	char		**commands;
// 	t_export	*exp;

// 	if (!envp)
// 		return (0);
// 	signal(SIGINT, handler_sigint);
// 	rl_catch_signals = 0;
// 	exp = create_export(envp);
// 	while(21)
// 	{
// 		input = readline(SHELL_NAME);
// 		g_flag = 0;
// 		if (input == NULL)
// 		{
// 			printf("\e[A%sexit\n", SHELL_NAME);
// 			break;
// 		}
// 		if (input[0] && !g_flag)
// 		{
// 			add_history(input);
// 		}
// 		// input = parse();
// 		// проверка
// 		check_what_to_do_with_command(&input, exp);
// 		free(input);
// 	}
// }


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
// 	t_export	*exp;

// 	if (!envp)
// 		return (0);
// 	signal(SIGINT, handler_sigint);
// 	rl_catch_signals = 0;
// 	exp = create_export(envp);
// 	for (int i = 0; i < 9; i++)
// 	{
// 		check_what_to_do_with_command(arr[i], exp);
// 	}
// }



int	main(int argc, char *argv[], char *envp[])
{
	if (!envp)
		return (1);
	t_export	*exp;
	char	*arr1[] = {"cd", NULL};
	char	*arr2[] = {"pwd", "-n", "-n", "1", "2", "3", "-n", "4", NULL};

	exp = create_export(envp);
	// add_to_env(exp, "a");
	// add_to_env(exp, "b=");
	print_env(exp);
	
	// // do_env(NULL, exp);
	// for (int i = 0; i < 10; i++)
	// {
	// 	printf("_\n");
	// }
	// do_export(arr1, exp);
	check_what_to_do_with_command(arr1, exp);
	check_what_to_do_with_command(arr2, exp);

	// printf("%s - a\n", get_env(exp, "a"));
	// printf("%s - z\n", get_env(exp, "z"));
}






//readline,
//rl_on_new_line,
//rl_replace_line,
//rl_redisplay,
//add_history
