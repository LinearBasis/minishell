#ifndef PARSER_H
# define PARSER_H

# include "utils.h"
# include "unistd.h"
# include "data_structs/commlist.h"

# define CHECK_FAILED_QUOTES	-1
# define CHECK_FAILED_OPERS		-2
# define CHECK_SUCCESS			0

// parser.c
int			parse_input(char *str, t_commlist **out_commlist);

// parser_argv.c
char		**parser__get_argv(char **str);

// syntax_analys.c
t_operation	parser__is_oper(const char *str);
int			parser__syntax_analys(const char *str, t_operation *error_token);
void		parser__print_syntax_error(t_operation error_token);

#endif