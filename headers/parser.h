#ifndef PARSER_H
# define PARSER_H

# include "utils.h"
# include <unistd.h>
# include "commlist.h"
# include "envp.h"
# include "error.h"

# define CHECK_FAILED_QUOTES	-1
# define CHECK_FAILED_OPERS		-2
# define CHECK_SUCCESS			0

// parser.c
int			parse_input(char **str, t_commlist **out_commlist,
				t_envp *envp, int last_exit_code);

// syntax_analys.c
t_operation	parser__is_oper(const char *str);
int			parser__syntax_analys(const char *str, t_operation *error_token);
void		parser__print_syntax_error(t_operation error_token);

// envp_replace
int			parser__envp_replace(char **str, t_envp *envp, int last_exit_code);
char		*replace_keys__get_value(char **envp[2], char *key, size_t *key_len);
size_t		replace_keys__get_new_len(char *str, char **envp[2],
					char *exit_code);
// parser_argv.c
char		**parser__get_argv(char **str);
char		*parser__get_word(char **str);

#endif
