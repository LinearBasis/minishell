#include "utils.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buf;

	buf = malloc(count * size);
	if (buf)
		ft_bzero(buf, count * size);
	return (buf);
}

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*((unsigned char *)s++) = 0;
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\t' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i++])
		;
	return (i - 1);
}

int	ft_strncmp(const char *str1, const char *str2, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len - 1 && str1[i] == str2[i] && str1[i])
		i++;
	return (str1[i] - str2[i]);
}