#include "commands.h"

static int		is_colon(char c);
static int		replace_home_dir(char **command, t_envp *envp);
static char		*bruteforce_binary(char *command, char **path_dirs);

int	exec_command(char **argv, t_envp *envp)
{
	char	**path_dirs;
	char	*binary;
	size_t	index;

	path_dirs = ft_smart_split(envp_get_value(envp, "PATH"), &is_colon, "/");
	if (!path_dirs)
		return (perror__errno("path_dirs: sys", EXECERR__PATHDIRS));
	if (replace_home_dir(argv, envp) != EXECERR__SUCCESS)
		return (EXECERR__HOMEDIR);
	binary = bruteforce_binary(argv[0], path_dirs);
	if (!binary)
		return (perror__exec(argv[0], EXECERR__NOT_FOUNT));
	if (binary != argv[0])
	{
		free(argv[0]);
		argv[0] = binary;
	}
	if (execve(binary, argv, envp->envp_cpy) < 0)
	{
		index = 0;
		while (path_dirs[index++])
			free(path_dirs[index - 1]);
		free(path_dirs);
		return (perror__errno(binary, EXECERR__EXECVE));
	}
	return (EXECERR__SUCCESS);
}

static int	is_colon(char c)
{
	return (c == ':');
}

static int		replace_home_dir(char **command, t_envp *envp)
{
	char	*tmp;

	if (ft_strncmp(*command, "~/", 2) == 0)
	{
		tmp = ft_strjoin(envp_get_value(envp, "HOME"), *command + 1);
		if (!tmp)
			return (perror__errno("home_dir: sys", EXECERR__HOMEDIR));
		free(*command);
		*command = tmp;
	}
	return (0);
}

static char	*bruteforce_binary(char *command, char **path_dirs)
{
	struct stat	buff;
	char		*tmp;

	if (
		(
			ft_strncmp(command, "/", 1) == 0
			|| ft_strncmp(command, "./", 2) == 0
			|| ft_strncmp(command, "../", 2) == 0
		)
		&& stat(command, &buff) == 0 && (buff.st_mode & S_IXUSR))
		return (command);
	while (*path_dirs)
	{
		tmp = ft_strjoin(*path_dirs, command);
		if (stat(tmp, &buff) == 0 && (buff.st_mode & S_IXUSR))
			return (tmp);
		free(tmp);
		path_dirs++;
	}
	return (NULL);
}
