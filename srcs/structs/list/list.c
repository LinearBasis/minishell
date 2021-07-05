#include "list.h"

t_list	*list_create(void *data)
{
	t_list	*ans;

	ans = malloc(sizeof(t_list));
	if (!ans)
	{
		return (ans);
	}
	ans->prev = NULL;
	ans->next = NULL;
	ans->data = data;
	return (ans);
}

void	list_push_back(t_list **list, t_list *added)
{
	t_list	*cpy;

	if (!list || !*list || !added)
		return ;
	cpy = *list;
	while (cpy->next)
		cpy = cpy->next;
	cpy->next = added;
	added->prev = cpy;
}

void	list_push_front(t_list **list, t_list *added)
{
	t_list	*cpy;

	if (!list || !*list || !added)
		return ;
	cpy = *list;
	while (cpy->prev)
		cpy = cpy->prev;
	cpy->prev = added;
	added->next = cpy;
	*list = added;
}

void	list_remove_elem(t_list **list_begin,
							t_list *deleted, void (*del)(void *))
{
	t_list	*prev;
	t_list	*next;

	if (!list_begin || !*list_begin || !deleted || !del)
		return ;
	if (deleted->prev == NULL && deleted->next == NULL)
	{
		del(deleted->data);
		free(deleted);
		*list_begin = NULL;
	}
	else if (deleted->prev == NULL)
	{
		(*list_begin)->next->prev = NULL;
		*list_begin = (*list_begin)->next;
	}
	else if (deleted->next == NULL)
		deleted->prev->next = NULL;
	else
	{
		deleted->next->prev = deleted->prev;
		deleted->prev->next = deleted->next;
	}
	del(deleted->data);
	free(deleted);
}

t_list	*list_find(t_list *list, void *data, int (*cmp)(void *, void *))
{
	while (list)
	{
		if (!cmp(list->data, data))
			return (list);
		list = list->next;
	}
	return (NULL);
}



void	list_clear(t_list **list, void (*del)(void*))
{
	t_list	*cpy;

	if (!list || !*list || !del)
		return ;
	while (cpy)
	{
		cpy = (*list)->next;
		del((*list)->data);
		free((*list));
		*list = cpy;
	}
	*list = cpy;
}
