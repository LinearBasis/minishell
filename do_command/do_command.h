#ifndef DO_COMMAND_H
# define DO_COMMAND_H
# include "../envp/envp.h"

int		check_what_to_do_with_string(char ** command, t_export *);
int		do_echo(char ** command);
int		do_cd(char ** command);
int		do_pwd(char ** command);
int		do_export(char ** command, t_export *);
int		do_unset(char ** command, t_export *);
int		do_env(char ** command, t_export *);
int		do_exit(char ** command);

#endif