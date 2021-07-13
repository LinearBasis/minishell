#include "commands.h"

int		is_colon(char c);
char	*bruteforce_binary(char *command, char **path_dirs);

int		exec_command(char **argv, t_envp *envp)
{
	char	**path_dirs;
	char	*binary;

	path_dirs = ft_smart_split(get_env(envp, "PATH"), &is_colon, "/");
	if (!path_dirs)
		return (-1);
	binary = bruteforce_binary(argv[0], path_dirs);
	if (binary != argv[0])
	{
		free(argv[0]);
		argv[0] = binary;
	}
	if (execve(binary, argv, envp->envp_key_value) < 0)
		return (-2);
	return (0);
}

int		is_colon(char c)
{
	return (c == ':');
}

char	*bruteforce_binary(char *command, char **path_dirs)
{
	struct stat	buff;
	char	*tmp;

	while (*path_dirs)
	{
		tmp = ft_strjoin(*path_dirs, command);
		if (stat(tmp, &buff) != 0)
			return (NULL);
		if (buff.st_mode & S_IXUSR)
			return (tmp);
		free(tmp);
		path_dirs++;
	}
	return (command);
}