#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include <stdlib.h>

char	*ft_substr_from_to(char *str, int begin, int end);		//	[begin, end)
size_t	ft_strlen(const char *str);

char	**ft_split_smart(const char *s, int (*cmp)(char), const char *tail);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(char *str);

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

int		ft_strncmp(const char *str1, const char *str2, size_t len);
int		ft_strcmp(const char *str1, const char *str2);

#endif