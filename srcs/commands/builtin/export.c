#include "commands.h"

	// printf("declare -x %s", exp->envp_key_value[0][i]);
		// if (exp->envp_key_value[1][i])
		// 	printf("=\"%s\"", exp->envp_key_value[1][i]);
		// printf("\n");

/*
	builtin_export function

	Если не против, я тут немного поменял структуру файла,
	чтобы было видна основная структура "функция - статические подфункции"

	Можешь прописать комментарии сюда
*/
static void	_swap(int *a1, int *a2);
static int	*get_sort_indexes(char **export, size_t size);
static int	print_envp(t_envp *exp);

int	builtin_export(char **command, t_envp *exp)
{
	size_t	size;
	int		returned_value;
	int		out;

	size = 0;
	out = GOOD_RETURN;
	while (command[size])
		size++;
	if (size == 1)
		return (print_envp(exp));
	size = 1;
	while (command[size])
	{
		returned_value = envp_add(exp, command[size]);
		if (returned_value != GOOD_RETURN)
			out = perror__builtin((const char **)command,
					(int)size, returned_value);
		size++;
	}
	return (out);
}

static void	_swap(int *a1, int *a2)
{
	int	a3;

	a3 = *a1;
	*a1 = *a2;
	*a2 = a3;
}

static int	*get_sort_indexes(char **export, size_t size)
{
	int		*out;
	size_t	i;
	size_t	j;

	out = malloc(sizeof(int) * size);
	if (!out)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < size)
		out[j] = j;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (ft_strcmp(export[out[i]], export[out[j]]) < 0)
				_swap(&out[j], &out[i]);
			j++;
		}
		i++;
	}
	return (out);
}

static int	print_envp(t_envp *exp)
{
	int		*indexes;
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (exp->envp_key_value[0][size])
		size++;
	indexes = get_sort_indexes(exp->envp_key_value[0], size);
	if (!indexes)
		return (perror__errno("sys", EX_OSERR));
	i = 0;
	while (i < size)
	{
		printf("declare -x %s", exp->envp_key_value[0][indexes[i]]);
		if (exp->envp_key_value[1][indexes[i]])
			printf("=\"%s\"", exp->envp_key_value[1][indexes[i]]);
		printf("\n");
		i++;
	}
	free(indexes);
	return (0);
}
