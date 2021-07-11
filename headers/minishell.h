#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include "a_readline.h"
# include "signals.h"
# include "envp.h"
# include "do_command.h"
# include "utils.h"

# define SHELL_NAME "\x1b[1;32mMem4AgainShell:\x1b[0m "


void rl_replace_line(const char *text, int clear_undo);

#endif