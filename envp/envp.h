#ifndef ENVP_H
# define ENVP_H
typedef struct s_export
{
	char	**envp_cpy;
	char	**envp_key_value[2];
}				t_export;

t_export	*create_export(char **envp);
void		sort_env(t_export *);
void		print_env(t_export *);
int			get_env(t_export *, char *name);
int			add_to_env(t_export *, char *name, char *value);
int			remove_from_env(t_export *, char *name);

#endif