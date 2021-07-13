#include "data_structs/list.h"
#include <stdio.h>

void	list_print(t_list *begin, char *(*get_str)(void *))
	 //функция печатает строки, получаемые из данных в списке
{
	int	i;

	i = 0;
	printf("___\n");
	if (!begin)
	{
		printf("null_lst\n");
	}
	while (begin)
	{
		printf("%d - {%s}\n", i, get_str(begin->data));
		i++;
		begin = begin->next;
	}
	printf("__\n");
}