#ifndef PARSER_H
# define PARSER_H

# include "utils.h"
# include "data_structs/commlist.h"

# define CHECK_FAILED_QUOTES	-1
# define CHECK_FAILED_OPERS		-2
# define CHECK_SUCCESS			0

t_operation	parser__is_operation(const char *str);
int			parser__syntax_analys(const char *str, t_operation *error_token);

#endif