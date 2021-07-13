#ifndef COMMLIST_H
# define COMMLIST_H

# include <stdlib.h>

typedef struct s_commlist
{
	struct s_list	*prev;
	struct s_list	*next;
	void			*data;
}				t_commlist;

t_commlist	*list_create(void *data);
t_commlist	*list_find(t_commlist *list, void *data, int (*cmp)(void *, void *));
void	list_push_back(t_commlist **list, t_commlist *added);
void	list_push_front(t_commlist **list, t_commlist *added);

void	list_remove_elem(t_commlist **list_begin, t_commlist *deleted, void (*del)(void *));

void	list_clear(t_commlist **list, void (*del)(void*));

#endif