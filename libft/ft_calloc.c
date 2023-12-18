

#include "libft.h"
#include <stdlib.h>


void	*ft_calloc(size_t count, size_t size)
{
	void *result;

	result = malloc(count * size);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, count * size);
	return (result);
}
