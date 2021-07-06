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
