#include "utils.h"

//before <= after, str1 != null, str1 will be freed
void	*ft_realloc(void *str1, size_t before, size_t after)
{
	char	*ans;
	char	*cpy;
	size_t	i;

	cpy = str1;
	if (!str1 || before > after)
		return (NULL);
	ans = malloc(after);
	if (!ans)
		return (NULL);
	i = 0;
	while (i < before)
	{
		ans[i] = cpy[i];
		i++;
	}
	free(cpy);
	return (ans);
}

//podarok [2,4) = da
char	*ft_substr_from_to(char *str, int begin, int end)
{
	char	*ans;
	int		begin_cpy;

	if (end <= begin || begin > ft_strlen(str) || end > ft_strlen(str))
		return (NULL);
	ans = malloc(end - begin + 1);
	if (!ans)
		return (NULL);
	begin_cpy = begin;
	while (begin < end)
	{
		ans[begin - begin_cpy] = str[begin];
		begin++;
	}
	ans[begin - begin_cpy] = 0;
	return (ans);
}
