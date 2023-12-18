

#include "libft.h"
#include <stdlib.h>

static int	checker(const char *a, char b)
{
	int	i;

	i = 0;
	while (a[i] != '\0')
	{
		if (a[i] == b)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *s2)
{
	int		i;
	int		end;
	int		start;
	char	*str;

	if (!s1)
		return (NULL);
	end = ft_strlen(s1);
	start = 0;
	while (s1[start] != '\0' && checker(s2, s1[start]))
		start++;
	while (start < end && checker(s2, s1[end - 1]))
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (0);
	i = 0;
	while (start < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
