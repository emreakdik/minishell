/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaniber <akaniber@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:56:23 by akaniber          #+#    #+#             */
/*   Updated: 2022/10/10 17:33:57 by akaniber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*buffer;

	buffer = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*buffer == (unsigned char)c)
			return (buffer);
		buffer++;
		i++;
	}
	return (NULL);
}
