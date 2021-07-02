#ifndef LIST_H
# define LIST_H

# include <string.h>
# include <stdlib.h>

typedef struct s_list
{
	struct s_list	*prev;
	struct s_list	*next;
	void			*data;
}				t_list;

t_list	*list_create(void *data);
t_list	*list_find(t_list *list, void *data, int (*cmp)(void *, void *));
void	list_push_back(t_list **list, t_list *added);
void	list_push_front(t_list **list, t_list *added);

void	list_remove_elem(t_list **list_begin, t_list *deleted, void (*del)(void *));

void	list_clear(t_list **list, void (*del)(void*));

#endif