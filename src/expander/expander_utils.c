/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaybaz <aaybaz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:25:39 by aaybaz            #+#    #+#             */
/*   Updated: 2023/07/20 00:59:49 by aaybaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void	_erase_after(t_list *data, char *str, char *tmp, int i)
{
	if (data->content)
		free(data->content);
	data->content = ft_substr(tmp, i, (ft_strlen(tmp) - i));
	if (str)
		free(str);
}

void	erase_after(char *tmp, t_list *data, int i)
{
	char	*before;
	char	*str;

	str = NULL;
	before = before_dollar(tmp);
	while (1)
	{
		if (!ft_isalnum(tmp[i]) || !tmp[i])
		{
			if (before)
			{
				if (data->content)
					free(data->content);
				str = ft_substr(tmp, i, (ft_strlen(tmp) - i));
				data->content = ft_strjoin(before, str);
				free(before);
				free(str);
			}
			else
				_erase_after(data, str, tmp, i);
			return ;
		}
		i++;
	}
	data->content = before;
}

void	_does_dollar_make_sense(t_env *y, char *before,
	char *after, t_list *data)
{
	char	*str;
	char	*new_content;

	new_content = NULL;
	str = NULL;
	if (after && before)
	{
		str = ft_strjoin(before, y->value);
		new_content = ft_strjoin(str, after);
		free(str);
	}
	else if (after)
		new_content = ft_strjoin(y->value, after);
	else if (before)
		new_content = ft_strjoin(before, y->value);
	else
		new_content = ft_strdup(y->value);
	if (data->content)
		free(data->content);
	data->content = new_content;
}

char	*after_dark2(char *key, char *tmp)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (tmp[i] != key[j])
		i++;
	while (tmp[i] && tmp[i] == key[j])
	{
		i++;
		j++;
		if (!key[j] && (tmp[i] > 0))
		{
			if (tmp[i] == 0)
				return (NULL);
			str = ft_substr(tmp, i, ft_strlen(tmp));
			return (str);
		}
	}
	return (NULL);
}

void	does_dollar_make_sense(char *tmp, t_list *data,
	t_list *shell_data, int i)
{
	t_env	*y;
	char	*after;
	char	*before;

	y = shell_data->content;
	if (ft_ultimatestrcmp(y->key, tmp, i))
	{
		before = before_dollar(tmp);
		after = after_dark2(y->key, tmp);
		_does_dollar_make_sense(y, before, after, data);
		if (before)
			free(before);
		if (after)
			free(after);
	}
}
