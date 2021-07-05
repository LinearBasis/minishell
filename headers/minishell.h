#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>

/*
 * built-in commands
 */
int		cmd_echo(int argc, char **argv);
int		cmd_cd(int argc, char **argv);
int		cmd_pwd(int argc, char **argv);
int		cmd_export(int argc, char **argv);
int		cmd_unset(int argc, char **argv);
int		cmd_env(int argc, char **argv);
int		cmd_exit(int argc, char **argv);

#endif
