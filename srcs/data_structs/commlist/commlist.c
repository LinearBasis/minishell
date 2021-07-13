#include "data_structs/commlist.h"

t_commlist	*commlist_create(char *data)
{
	t_commlist	*out;

	out = malloc(sizeof(t_commlist));
	if (!out)
		return (out);
	out->prev = NULL;
	out->next = NULL;
	out->op_prev = OP_NONE;
	out->op_next = OP_NONE;
	out->data = data;
	return (out);
}

void	commlist_push_back(t_commlist **list, t_commlist *to_add)
{
	t_commlist	*iter;

	if (!list || !to_add)
		return ;
	if (!*list)
	{
		*list = to_add;
		return;
	}

	iter = *list;
	while (iter->next)
		iter = iter->next;
	iter->next = to_add;
	to_add->prev = iter;
}

void	commlist_push_front(t_commlist **list, t_commlist *to_add)
{
	t_commlist	*iter;

	if (!list || !to_add)
		return ;
	to_add->next = *list;
	*list = to_add;
}

void	commlist_clear(t_commlist *list)
{
	t_commlist	*tmp;

	if (!list)
		return ;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->data);
		free(tmp);
	}
}
