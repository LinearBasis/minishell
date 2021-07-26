#include "commands.h"
#include <unistd.h>

int	builtin_pwd(char **command, t_envp *exp)
{
	char	buf[25565];
	char	*pwd_var;

	(void)command;
	ft_bzero(buf, 255);
	pwd_var = envp_get_value(exp, "PWD");
	if (!pwd_var)
	{
		if (getcwd(buf, 25565) == NULL)
		{
			write(2, "i dont know where are you\n", 26);
			return (1);
		}
		write(1, buf, ft_strlen(buf));
	}
	else
		write(1, pwd_var, ft_strlen(pwd_var));
	write(1, "\n", 1);
	free(pwd_var);
	return (EX_OK);
}
