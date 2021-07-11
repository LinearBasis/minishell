#ifndef ENVP_H
# define ENVP_H

# include <stddef.h>
# include <stdlib.h>
# include "../utils/utils.h"

typedef struct s_export
{
	char	**envp_key_value[2];
}				t_export;


int			_fill_one_export(t_export *ans, char *env, int i);

void		clear_export(t_export *exp);
t_export	*create_export(char **envp);
void		sort_env(t_export *);
void		print_env(t_export *);
char		*get_env(t_export *, char *key);
int			add_to_env(t_export *, char *key);
int			remove_from_env(t_export *, char *key);
int			_copy_envp(t_export *ans, char **envp, int i);

#endif