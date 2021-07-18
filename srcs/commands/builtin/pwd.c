#include "commands.h"
#include <unistd.h>

int		builtin_pwd(char **command)
{
	char	buf[25565];

	(void)command;
	if (getcwd(buf, 25565) == NULL)
	{
		write(2, "i dont know where are you\n", 26);
		return (1);
	}
	printf("%s\n", buf);
	return (GOOD_RETURN);
}