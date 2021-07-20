#ifndef ERROR_H
# define ERROR_H

# include <unistd.h>
# include <string.h>
# include <errno.h>
# include "utils.h"

# define MALLOC_ERROR 11
//	for unset and export
# define NOT_A_VALID_IDENTIFIER 12
# define HOME_NOT_SET 13
# define CD_CHDIR_ERROR 14
# define NO_SUCH_FILE 15









int	perror__syntax(const char *error_token, int error_code);
int	perror__errno(const char *error_token, int error_code);
int perror__exec(const char *error_token, int error_code);

int	perror__builtin(const char **commands, int id_of_error_arg, int error_code);

#endif