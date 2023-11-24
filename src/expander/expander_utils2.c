/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 23:24:14 by aaybaz            #+#    #+#             */
/*   Updated: 2023/11/22 13:45:05 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void	free_tmp_tmp2(char *tmp, char *tmp1)
{
	free(tmp);
	free(tmp1);
}

void	ft_tilde_build1(t_list *data, char *key, char *tmp)
{
	if (data->content)
		free(data->content);
	data->content = ft_strjoin(key, tmp);
}

void	ft_tilde_build2(t_list *data, char *str)
{
	if (data->content)
		free(data->content);
	data->content = ft_strdup(str);
}

char	*before_dollar(char *tmp)
{
	char	*str;
	int		i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '$')
		{
			str = ft_substr(tmp, 0, i);
			if (i != 0)
				return (str);
			else
			{
				free(str);
				break ;
			}
		}
		i++;
	}
	return (NULL);
}

void	get_after_num(char *tmp, t_list *data, int i)
{
	char	*before;
	char	*str;

	str = NULL;
	before = before_dollar(tmp);
	if (before)
	{
		if (data->content)
			free(data->content);
		str = ft_substr(tmp, i, ft_strlen(tmp) - i);
		data->content = ft_strjoin(before, str);
	}
	else
	{
		if (data->content)
			free(data->content);
		data->content = ft_substr(tmp, i, ft_strlen(tmp) - i);
	}
	if (before)
		free(before);
	if (str)
		free(str);
}
