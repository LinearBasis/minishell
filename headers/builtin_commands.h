#ifndef BUILTIN_COMMANDS_H
# define BUILTIN_COMMANDS_H

# include "envp.h"
# include <unistd.h>
# include <errno.h>
# include <stdio.h>

int		handle_command(char **command, t_envp *exp);
int		builtin_echo(char ** command);
int		builtin_cd(char ** command, t_envp *exp);
int		builtin_pwd(char ** command);
int		builtin_export(char ** command, t_envp *);
int		builtin_unset(char ** command, t_envp *);
int		builtin_env(char ** command, t_envp *);
int		builtin_exit(char ** command);

#endif