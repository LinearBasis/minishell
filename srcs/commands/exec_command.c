#include "commands.h"

static int		is_colon(char c);
static void		free_path(char **path_dirs);
static int		check_binary(char *binary, int status, char **argv);

int	exec_command(char **argv, t_envp *envp)
{
	char	**path_dirs;
	char	*binary;
	int		status;

	status = EX_OK;
	path_dirs = ft_smart_split(envp_get_value(envp, "PATH"), &is_colon, "/");
	if (!path_dirs)
		return (perror__errno("sys", EX_OSERR));
	binary = exec_command__bruteforce_binary(argv[0], path_dirs, &status);
	status = check_binary(binary, status, argv);
	if (status != EX_OK)
		return (status);
	if (execve(binary, argv, envp->envp_cpy) < 0)
	{
		free_path(path_dirs);
		return (perror__errno(binary, EX_CMD_NOTEXEC));
	}
	return (EX_OK);
}

static int	check_binary(char *binary, int status, char **argv)
{
	struct stat	buff;

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
	if (stat(binary, &buff) != 0)
		return (perror__errno(argv[0], errno));
	if (buff.st_mode & S_IFDIR)
	{
		errno = EISDIR;
		return (perror__errno(argv[0], EX_CMD_NOTEXEC));
	}
	return (EX_OK);
}

static int	is_colon(char c)
{
	return (c == ':');
}

static void	free_path(char **path_dirs)
{
	size_t	index;

	index = 0;
	while (path_dirs[index++])
		free(path_dirs[index - 1]);
	free(path_dirs);
}
