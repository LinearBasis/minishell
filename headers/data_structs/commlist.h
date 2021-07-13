#ifndef COMMLIST_H
# define COMMLIST_H

# include <stdlib.h>

typedef unsigned char t_operation;

typedef struct s_commlist
{
	struct s_list	*prev;
	struct s_list	*next;
	t_operation		op_prev;
	t_operation		op_next;
	char			*data;
}				t_commlist;

# define OP_NONE		0
# define OP_PIPE		1
# define OP_REDIRL		2
# define OP_REDIRR		3
# define OP_REDIR2L 	4
# define OP_REDIR2R 	4

t_commlist	*commlist_create(char *data);

void		commlist_push_back(t_commlist **list, t_commlist *to_add);
void		commlist_push_front(t_commlist **list, t_commlist *to_add);

void		commlist_clear(t_commlist *list);

#endif