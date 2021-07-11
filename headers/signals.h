#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern int	g_flag;

void	handler_sigint(int status);
void	handler_sigquit(int status);

#endif