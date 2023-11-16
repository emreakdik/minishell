/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TrimSpace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:28:06 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:28:06 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	Gelen komutu bosluk gordukce adres uzerinde arttirir
	boylece geldigi fonksiyonda da artmis olur.
*/
size_t	trim_spaces(char **cmd_line)
{
	size_t	count;

	count = 0;
	if (!*cmd_line)
		return (count);
	while (**cmd_line == 32)
	{
		count++;
		(*cmd_line)++;
	}
	return (count);
}
