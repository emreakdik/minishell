/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaniber <akaniber@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 23:31:41 by aaybaz            #+#    #+#             */
/*   Updated: 2023/10/15 13:37:44 by akaniber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

int	ft_ultimatestrcmp(char *key, char *tmp, int i)
{
	int	j;

	j = 0;
	if (tmp[i] != key[0])
		return (0);
	while (tmp[i])
	{
		j = 0;
		while (tmp[i] == key[j])
		{
			i++;
			j++;
			if (!key[j])
			{
				if (!ft_isalnum(tmp[i]))
					return (1);
				return (0);
			}
		}
		i++;
	}
	return (0);
}

void	_ft_exit_status(t_list *data, char *str1)
{
	data->content = str1;
}

void	free_tmps(char *str, char *str2, char *str_tmp)
{
	if (str)
		free(str);
	if (str_tmp)
		free(str_tmp);
	if (str2)
		free(str2);
}

void	free_str1(char *str1, int flag)
{
	if (flag == 0 && str1)
		free(str1);
}
