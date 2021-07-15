#include "data_structs/commlist.h"
#include <stdio.h>

static void	printf_oper(t_operation op)
{
	if (op == OP_NONE)
		printf("(null)");
	else if (op == OP_PIPE)
		printf("|");
	else if (op == OP_REDIRL)
		printf("<");
	else if (op == OP_REDIRR)
		printf(">");
	else if (op == OP_REDIR2L)
		printf("<<");
	else if (op == OP_REDIR2R)
		printf(">>");
}

void	commlist_print(t_commlist *lst)
{
	char	**copy;

	while (lst)
	{
		printf("\n----------------------------------------\n");
		printf_oper(lst->op_prev);
		copy = lst->data;
		printf("\t[");
		while (*(copy + 1))
		{
			printf("%s|", *copy);
			copy++;
		}
		printf("%s]\t", *copy);
		printf_oper(lst->op_next);
		printf("\n");
		lst = lst->next;
	}
	printf("\n----------------------------------------\n");
}