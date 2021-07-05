#include "utils.h"
	
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
