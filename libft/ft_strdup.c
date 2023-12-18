

#include "libft.h"
#include <stdlib.h>


char	*ft_strdup(const char *str)
{
	char *s;
	size_t len;
	int i;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (0);
	while (str[i] != '\0')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
