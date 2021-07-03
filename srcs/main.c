// #include "list/list.h"

// char	*get_string(void *str)
// {
// 	return (str);
// }

// int	cmp(void *v1, void *v2)
// {
// 	return (strcmp(v1, v2));
// }
// int		main()
// {
// 	t_list	*lst = list_create(strdup("12345"));
// 	list_push_front(&lst, list_create(strdup("444444")));
// 	list_push_front(&lst, list_create(strdup("255255")));
// 	list_push_back(&lst, list_create(strdup("zzzzzz")));
// 	list_push_back(&lst, list_create(strdup("abcdef")));
// 	// list_remove_elem(&lst, list_find(lst, "12345", cmp), free);
// 	list_remove_elem(&lst, list_find(lst, "255255", cmp), free);
// 	list_remove_elem(&lst, list_find(lst, "abcdef", cmp), free);
// 	// list_clear(&lst, free);
// 	list_print(lst, get_string);
// 	sleep(10);
// }