#include "commands.h"

static char	*bruteforce_binary__preprocessing(char *command, char **path_dirs,
				int *status)
{
	struct stat	buff;
	char		*tmp;

	if (!*path_dirs)
	{
		if (stat(command, &buff) != 0)
			*status = ENOENT;
		return (command);
	}
	tmp = command;
	while (*tmp)
	{
		if (*(tmp++) == '/')
		{
			if (stat(command, &buff) != 0)
				*status = ENOENT;
			return (command);
		}
	}
	if (stat(command, &buff) == 0 && (buff.st_mode & S_IXUSR))
		return (command);
	return (NULL);
}

char	*bruteforce_binary__check_pathdir(char *command, char *path_dir,
			int *status)
{
	struct stat	buff;
	char		*tmp;

	tmp = ft_strjoin(path_dir, command);
	if (!tmp)
	{
		*status = perror__errno("sys", EX_OSERR);
		return (NULL);
	}
	if (stat(tmp, &buff) == 0 && (buff.st_mode & S_IXUSR))
		return (tmp);
	free(tmp);
	return (NULL);
}

char	*exec_command__bruteforce_binary(char *command, char **path_dirs,
			int *status)
{
	char		*tmp;

	*status = EX_OK;
	tmp = command;
	while (*command && ft_isspace(*command))
		command++;
	if (!*command)
		return (NULL);
	tmp = bruteforce_binary__preprocessing(command, path_dirs, status);
	if (tmp)
		return (command);
	while (*path_dirs)
	{
		tmp = bruteforce_binary__check_pathdir(command, *path_dirs, status);
		if (tmp)
			return (tmp);
		path_dirs++;
	}
	return (NULL);
}
