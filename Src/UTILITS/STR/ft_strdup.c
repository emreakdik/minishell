/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:24:33 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:24:33 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	gönderilen karakter dizisi icin heap bellekte 
	yer ayrilir ve ardindan return edilir.
*/

char	*ft_strdup(char *ptr)
{
	char	*new_ptr;
	char	*return_new_ptr;

	if (!ptr)
		return (NULL);
	new_ptr = (char *)malloc(sizeof(char) * (ft_strlen(ptr) + 1));
	return_new_ptr = new_ptr;
	while (*ptr)
		*(new_ptr++) = *(ptr++);
	*new_ptr = 0;
	return (return_new_ptr);
}
