#include "commands.h"
#include <string.h>

/*
	builtin_cd function

	Если не против, я тут немного поменял структуру файла,
	чтобы было видна основная структура "функция - статические подфункции"

	Можешь прописать комментарии сюда
*/
static int	do_cd_to_user(char **command, t_envp *exp);
static int	do_cd_to_path(char **command, t_envp *exp);

int	set_pwd(t_envp *exp)
{
	char	*newpwd;
	char	*newpwd_keyvalue;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (perror__errno("sys", errno));
	newpwd_keyvalue = ft_strjoin("PWD=", newpwd);
	free(newpwd);
	if (!newpwd_keyvalue)
		return (perror__errno("sys", errno));
	if (envp_add(exp, newpwd_keyvalue) != GOOD_RETURN)
	{
		free(newpwd_keyvalue);
		return (MALLOC_ERROR);
	}
	free(newpwd_keyvalue);
	return (0);
}

int	builtin_cd(char **command, t_envp *exp)
{
	char	*oldpwd;
	char	*oldpwd_keyvalue;

	oldpwd = envp_get_value(exp, "PWD");
	if (!oldpwd)
		oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror__errno("sys", errno));
	oldpwd_keyvalue = ft_strjoin("OLDPWD=", oldpwd);
	free(oldpwd);
	if (!oldpwd_keyvalue)
		return (perror__errno("sys", errno));
	if (envp_add(exp, oldpwd_keyvalue) != GOOD_RETURN)
	{
		free(oldpwd_keyvalue);
		return (MALLOC_ERROR);
	}
	free(oldpwd_keyvalue);
	if (command[1] == NULL)
		return (do_cd_to_user(command, exp));
	return (do_cd_to_path(command, exp));
}

static int	do_cd_to_user(char **command, t_envp *exp)
{
	char	*path;

	path = envp_get_value(exp, "HOME");
	if (!path)
		return (perror__builtin((const char **)command, 0, HOME_NOT_SET));
	if (chdir(path) == -1)
	{
		free(path);
		return (perror__errno("cd", CD_CHDIR_ERROR));
	}
	free(path);
	return (set_pwd(exp));
}

static int	do_cd_to_path(char **command, t_envp *exp)
{
	char	buf[1234];

	if (chdir(command[1]) == -1)
	{
		return (perror__builtin((const char **)command, 1, errno));
	}
	if (getcwd(buf, 1234) == NULL)
	{
		write(2, "cd: error retrieving current directory: getcwd: cannot", 54);
		write(2, " access parent directories: No such file or directory\n", 54);
	}
	else
		return (set_pwd(exp));
	return (GOOD_RETURN);
}
