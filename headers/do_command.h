#ifndef DO_COMMAND_H
# define DO_COMMAND_H

# include "envp.h"
# include <unistd.h>
# include <errno.h>
# include <stdio.h>

int		check_what_to_do_with_command(char **command, t_export *exp);
int		builtin_echo(char ** command);
int		builtin_cd(char ** command, t_export *exp);
int		builtin_pwd(char ** command);
int		builtin_export(char ** command, t_export *);
int		builtin_unset(char ** command, t_export *);
int		builtin_env(char ** command, t_export *);
int		builtin_exit(char ** command);

#endif