#include "commands.h"

static int		is_colon(char c);
static int		replace_home_dir(char **command, t_envp *envp);
static char		*bruteforce_binary(char *command, char **path_dirs, int *status);
static void		free_path(char **path_dirs);

int	exec_command(char **argv, t_envp *envp)
{
	char	**path_dirs;
	char	*binary;
	int		status;

	status = EX_OK;
	path_dirs = ft_smart_split(envp_get_value(envp, "PATH"), &is_colon, "/");
	if (!path_dirs)
		return (perror__errno("sys", EX_OSERR));
	if (err_assign(replace_home_dir(argv, envp), &status) != EX_OK)
		return (status);
	binary = bruteforce_binary(argv[0], path_dirs, &status);
	if (status == ENOENT)
		return (perror__errno(argv[0], EX_CMD_NOTFOUND));
	if (status != EX_OK)
		return (status);
	if (!binary)
		return (perror__exec(argv[0], EX_CMD_NOTFOUND));
	if (binary != argv[0])
	{
		free(argv[0]);
		argv[0] = binary;
	}
	if (execve(binary, argv, envp->envp_cpy) < 0)
	{
		free_path(path_dirs);
		return (perror__errno(binary, EX_CMD_NOTEXEC));
	}
	return (EX_OK);
}

static int	is_colon(char c)
{
	return (c == ':');
}

static int	replace_home_dir(char **command, t_envp *envp)
{
	char	*tmp;

	if (!ft_strncmp(*command, "~/", 2))
	{
		tmp = ft_strjoin(envp_get_value(envp, "HOME"), *command + 1);
		if (!tmp)
			return (perror__errno("sys", EX_OSERR));
		free(*command);
		*command = tmp;
	}
	return (0);
}

static char	*bruteforce_binary(char *command, char **path_dirs, int *status)
{
	struct stat	buff;
	char		*tmp;

	tmp = command;
	while (*tmp)
		if (*(tmp++) == '/')
		{
			if (stat(command, &buff) != 0)
				*status = ENOENT;
			return (command);
		}
	if (stat(command, &buff) == 0 && (buff.st_mode & S_IXUSR))
		return (command);
	while (*path_dirs)
	{
		tmp = ft_strjoin(*path_dirs, command);
		if (!tmp)
		{
			*status = perror__errno("sys", EX_OSERR);
			return (NULL);
		}
		if (stat(tmp, &buff) == 0 && (buff.st_mode & S_IXUSR))
			return (tmp);
		free(tmp);
		path_dirs++;
	}
	return (NULL);
}

static void	free_path(char **path_dirs)
{
	size_t	index;

	index = 0;
	while (path_dirs[index++])
		free(path_dirs[index - 1]);
	free(path_dirs);
}
