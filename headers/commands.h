#ifndef COMMANDS_H
# define COMMANDS_H

# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

# include "commlist.h"
# include "envp.h"
# include "utils.h"
# include "error.h"

# define EXECERR__SUCCESS	0
# define EXECERR__PATHDIRS	1
# define EXECERR__HOMEDIR	2
# define EXECERR__EXECVE	126
# define EXECERR__NOT_FOUNT 127

int		command_processing(t_commlist **commands, t_envp *envp);
int		commands__pipe_parser(t_commlist *commands);

int		commands__redir_parser(t_commlist **commands);
int		redir_left_double(t_commlist **commands);
int		redir_left_uno(t_commlist **commands);
int		redir_right_all(t_commlist **commands);

int		is_builtin_command(char **command);
int		handle_command(char **command, t_envp *envp);

// builtin commands
int		builtin_echo(char **command);
int		builtin_cd(char **command, t_envp *envp);
int		builtin_pwd(char **command);
int		builtin_export(char **command, t_envp *envp);
int		builtin_unset(char **command, t_envp *envp);
int		builtin_env(char **command, t_envp *envp);
int		builtin_exit(char **command);
// exec commands
int		exec_command(char **argv, t_envp *envp);

#endif