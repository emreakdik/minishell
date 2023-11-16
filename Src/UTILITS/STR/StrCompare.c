/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrCompare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:27:41 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:27:41 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

int	str_compare(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (0);
	while (*str1)
	{
		if (*str1 != *str2)
			break ;
		str1++;
		str2++;
	}
	if (*str1 != 0 || *str2 != 0)
		return (0);
	return (1);
}
