#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include "../header.h"

void	handler_sigint(int status);
void	handler_sigquit(int status);

#endif