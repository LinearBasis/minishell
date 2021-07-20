#include "signals.h"

//	ctrl-c
void	handler_sigint(int status)
{
	(void)status;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	g_flag = 1;
}

//	ctrl-backslash
void	handler_sigquit(int status)
{
	(void)status;
}