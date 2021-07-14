#ifndef COMMANDS_H
# define COMMANDS_H

# include "data_structs/commlist.h"
# include "envp.h"
# include "utils.h"
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <sys/stat.h>

int		command_processing(t_commlist *commands, t_envp *envp);
int		handle_command(char **command, t_envp *envp);

// builtin commands
int		builtin_echo(char ** command);
int		builtin_cd(char ** command, t_envp *envp);
int		builtin_pwd(char ** command);
int		builtin_export(char ** command, t_envp *envp);
int		builtin_unset(char ** command, t_envp *envp);
int		builtin_env(char ** command, t_envp *envp);
int		builtin_exit(char ** command);

// exec commands
int		exec_command(char **argv, t_envp *envp);

#endif