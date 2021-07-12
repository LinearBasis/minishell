#ifndef A_READLINE_H
# define A_READLINE_H

//#include "../readlinelib/include/readline/readline.h"
//#include "../readlinelib/include/readline/history.h"

# include <readline/readline.h>
# include <readline/history.h>

void	rl_replace_line(const char *text, int clear_undo);

#endif
