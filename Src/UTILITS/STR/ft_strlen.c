/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:25:24 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:25:24 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	Karakter dizisinin boyutunu alir.
*/

size_t	ft_strlen(char *ptr)
{
	size_t	count;

	count = 0;
	while (ptr && *(ptr++))
		count++;
	return (count);
}
