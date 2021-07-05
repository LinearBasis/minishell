#ifndef ENVP_H
# define ENVP_H

# include <stddef.h>
# include <stdlib.h>
# include "../utils/utils.h"

typedef struct s_export
{
	t_li
}				t_export;


int			_fill_one_export(t_export *ans, char *env, int i);

void		clear_export(t_export *exp);
t_export	*create_export(char **envp);
void		sort_env(t_export *);
void		print_env(t_export *);
int			get_env(t_export *, char *name);
int			add_to_env(t_export *, char *str);
int			remove_from_env(t_export *, char *name);

#endif