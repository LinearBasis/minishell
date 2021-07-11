#include "do_command.h"
#include <string.h>


static int	do_cd_to_user(t_export *exp)
{
	char	*path;
	

	path = get_env(exp, "HOME");
	printf("asd\n");
	printf("path - %s\n", path);
	if (!path)							//		ОБЯЗАТЕЛЬНО ОБРАБОТАТЬ ОШИБКУ
	{
		write(2, "HOME not set\n", 13);
		return (1);
	}
	if (chdir(path) == -1)
	{
		free(path);
		return (-1);
	}
	free(path);
	return (0);
}

static int	do_cd_to_back(char buf[25565])
{
	char	*rchr;

	rchr = strrchr(buf, '/');
	if (rchr == &buf[0])
	{
		return (chdir("/"));
	}
	else
	{
		*rchr = 0;
		return (chdir(buf));
	}
}

static int	do_cd_to_path(char b)
{
	return (-1);
}

int	do_cd(char **command, t_export *exp)
{
	char	buf[25565];

	getcwd(buf, 25565);
	if (command[1] == NULL)
	{
		return (do_cd_to_user(exp));
	}
	// else if (!strcmp(command[1], ".."))	//TODO
	// {
	// 	do_cd_to_back(buf);
	// }
	// else if (!strcmp(command[1], "."))
	// {
	// 	return (0);
	// }
	// else
	// {
	// 	do_cd_to_path();
	// }
	return(0);
}