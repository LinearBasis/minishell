#include "do_command.h"

	// printf("declare -x %s", exp->envp_key_value[0][i]);
		// if (exp->envp_key_value[1][i])
		// 	printf("=\"%s\"", exp->envp_key_value[1][i]);
		// printf("\n");

static void	_swap(int *a1, int *a2)
{
	int	a3;

	a3 = *a1;
	*a1 = *a2;
	*a2 = a3;
}

static int	*get_sort_indexes(char **export, size_t size)
{
	int		*ans;
	size_t	i;
	size_t	j;

	ans = malloc(sizeof(int) * size);
	if (!ans)
		return (NULL);
	i = 0;
	j = 0;
	while (j < size)
	{
		ans[j] = j;
		j++;
	}
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (ft_strcmp(export[ans[i]], export[ans[j]]) < 0)
				_swap(&ans[j], &ans[i]);
			j++;
		}
		i++;
	}
	return (ans);
}

static int	print_export(t_export *exp)
{
	int		*indexes;
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	size = 0;
	while (exp->envp_key_value[0][size])
		size++;
	indexes = get_sort_indexes(exp->envp_key_value[0], size);
	if (!indexes)
		return (-1);
	i = 0;
	while (i < size)
	{
		printf("indexes[%d] - %d,    ", i, indexes[i]);
		printf("declare -x %s", exp->envp_key_value[0][indexes[i]]);
		if (exp->envp_key_value[1][indexes[i]])
			printf("=\"%s\"", exp->envp_key_value[1][indexes[i]]);
		printf("\n");
		i++;
	}
	free(indexes);
	return (0);
}

int		builtin_export(char **command, t_export *exp)
{
	size_t	size;

	size = 0;
	while (command[size])
		size++;
	if (size == 1)
	{
		return (print_export(exp));
	}
}