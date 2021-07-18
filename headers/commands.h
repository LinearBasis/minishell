#ifndef COMMANDS_H
# define COMMANDS_H

# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

# include "data_structs/commlist.h"
# include "envp.h"
# include "utils.h"
# include "error.h"

int		command_processing(t_commlist **commands, t_envp *envp);
int		commands__pipe_parser(t_commlist *commands);
int		commands__redir_parser(t_commlist **commands);
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