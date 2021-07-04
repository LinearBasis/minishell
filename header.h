#ifndef HEADER_H
# define HEADER_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "a_readline.h"
#define SHELL_NAME "\x1b[1;32mMem4AgainShell:\x1b[0m "

extern int	g_flag;

void rl_replace_line(const char *text, int clear_undo);







#endif