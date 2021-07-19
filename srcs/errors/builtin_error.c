#include "error.h"

char	*get_const_error_str(int code)
{
	if (code == MALLOC_ERROR)
		return ("malloc error");
	if (code == NOT_A_VALID_IDENTIFIER)
		return ("not a valid identifier");
	if (code == HOME_NOT_SET)
		return ("HOME not set");
}

int		get_error_code_from_my_error_code(int code)
{
	return (1);
}

int	perror__builtin(const char **commands, int id_of_error_arg, int error_code)
{
	printf("minishell: ");
	printf("%s: ", commands[0]);
	if (id_of_error_arg > 0)
		printf("\'%s\': ");
	printf("%s\n", get_const_error_str(error_code));	
	return (get_error_code_from_my_error_code(error_code));
}
