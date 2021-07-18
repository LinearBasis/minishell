#ifndef ERROR_H
# define ERROR_H

# include <unistd.h>
# include <string.h>
# include <errno.h>
# include "utils.h"

int	perror__syntax(const char *error_token, int error_code);
int	perror__errno(const char *error_token, int error_code);
int perror__exec(const char *error_token, int error_code);

#endif