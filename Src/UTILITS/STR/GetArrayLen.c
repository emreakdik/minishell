/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetArrayLen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:25:40 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:25:40 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

int	get_array_len(char **array)
{
	int	count;

	count = 0;
	while (array && *(array++))
		count++;
	return (count);
}
