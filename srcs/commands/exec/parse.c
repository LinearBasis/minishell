#include "commands.h"

int		is_colon(char c);
char	*bruteforce_binary(char *command, char **path_dirs);

int		exec_command(char **argv, t_envp *envp)
{
	char	**path_dirs;
	char	*binary;
	size_t	index;

	path_dirs = ft_smart_split(get_env(envp, "PATH"), &is_colon, "/");
	if (!path_dirs)
		return (perror__errno("sys", EXECERR__PATHDIRS));
	binary = bruteforce_binary(argv[0], path_dirs);
	if (!binary)
		return (perror__exec(argv[0], EXECERR__NOT_FOUNT));
	if (binary != argv[0])
	{
		free(argv[0]);
		argv[0] = binary;
	}
	if (execve(binary, argv, NULL) < 0)
	{
		index = 0;
		while (path_dirs[index++])
			free(path_dirs[index - 1]);
		free(path_dirs);
		return (perror__errno("sys", EXECERR__EXECVE));
	}
	return (EXECERR__SUCCESS);
}

int		is_colon(char c)
{
	return (c == ':');
}

char	*bruteforce_binary(char *command, char **path_dirs)
{
	struct stat	buff;
	char		*tmp;

	while (*path_dirs)
	{
		tmp = ft_strjoin(*path_dirs, command);
		if (stat(tmp, &buff) == 0 && (buff.st_mode & S_IXUSR))
			return (tmp);
		free(tmp);
		path_dirs++;
	}
	return (command);
}