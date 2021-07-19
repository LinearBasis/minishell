#include "commands.h"
#include <string.h>

/*
	builtin_cd function

	Если не против, я тут немного поменял структуру файла,
	чтобы было видна основная структура "функция - статические подфункции"

	Можешь прописать комментарии сюда
*/
static int	do_cd_to_user(char **command, t_envp *exp);
static int	do_cd_to_path(char **command);

int	builtin_cd(char **command, t_envp *exp)
{
	char	buf[25565];

	getcwd(buf, 25565);
	if (command[1] == NULL)
	{
		return (do_cd_to_user(command, exp));
	}
	
	return(do_cd_to_path(command));
}

static int	do_cd_to_user(char **command, t_envp *exp)
{
	char	*path;
	
	path = envp_get_value(exp, "HOME");
	printf("asd\n");
	printf("path - %s\n", path);
	if (!path)							//		ОБЯЗАТЕЛЬНО ОБРАБОТАТЬ ОШИБКУ
		return (perror__builtin(command, 0, HOME_NOT_SET));
	if (chdir(path) == -1)
	{
		free(path);
		return (perror__errno("cd", CD_CHDIR_ERROR));
	}
	free(path);
	return (0);
}

static int	do_cd_to_path(char **command)
{
	if (chdir(command[1]) == -1)
		return (perror__errno("cd", CD_CHDIR_ERROR));
}