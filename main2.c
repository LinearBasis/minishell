#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#define SHELL_NAME "\x1b[35mMem4AgainShell:\x1b[0m"

int	g_flag = 0;
void rl_replace_line(const char *text, int clear_undo);

// int		echo(char *argv[])
// {
// 	int i = 1;

// 	while (argv[i])
// 	{
// 		printf("%s", argv[i]);
// 		if (argv[i + 1])
// 			printf(" ");
// 	} 
// }

void handler (int status)
{
	// printf("status - %d\n", status);
	// rl_redisplay();
	// printf("\n___%s___\n", rl_prompt);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	// printf("\n");
	// printf("a %s\n", rl_line_buffer);
	// printf("^C caught\n");
	while (1)
	{
		write(1, "\b", 1);
	}
	g_flag = 1;

}

int	main()
{
	char*	input;
	// signal(SIGTERM, handler);
	signal(SIGINT, handler);
	// rl_catch_signals = 0;

	while(21)
	{
		g_flag = 0;
		input = readline(SHELL_NAME);
		printf("in - %s\n", input);
		if (input == NULL)
			break;
		// input = parse();
		if (input[0] && !g_flag)
		{
			add_history(input);
		}
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