#include "utils.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while ((i + 1 < dstsize) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	if (dst_len > dstsize)
		return (dstsize + ft_strlen(src));
	ft_strlcpy(dst + dst_len, src, dstsize - dst_len);
	return (dst_len + ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	out = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!out)
		return (NULL);
	ft_strlcpy(out, s1, (len1 + 1));
	ft_strlcat(out, s2, (len1 + len2 + 1));
	return (out);
}

char	*ft_strdup(char *str)
{
	char	*ans;
	size_t	i;

	i = ft_strlen(str);
	ans = malloc(i + 1);
	ft_strlcpy(ans, str, i + 1);
	return (ans);
}

int		ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i] && str2[i])
		i++;
	return (str1[i] - str2[i]);
}