#ifndef ENVP_H
# define ENVP_H

# include <stddef.h>
# include <stdlib.h>
# include "utils.h"

typedef struct s_envp
{
	char	**envp_key_value[2];
}	t_envp;

# define KEY	0
# define VALUE	1

int			_fill_one_export(t_envp *ans, char *env, int i);

void		clear_export(t_envp *exp);
t_envp	*create_export(char **envp);
void		sort_env(t_envp *);
void		print_env(t_envp *);
char		*get_env(t_envp *, char *key);
int			add_to_env(t_envp *, char *key);
int			remove_from_env(t_envp *, char *key);
int			_copy_envp(t_envp *ans, char **envp, int i);

#endif