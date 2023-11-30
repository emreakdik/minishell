/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:24:35 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/30 20:05:35 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	count_of_quotes(char *before)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (before[i])
	{
		if (before[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

int	quote_index(char *str, int is_from_last)
{
	int	len;

	len = 0;
	if (is_from_last)
		len = ft_strlen(str) - 1;
	while (str[len])
	{
		if (str[len] == '\'')
			return (len);
		if (is_from_last)
			len--;
		else
			len++;
	}
	return (0);
}

char	*get_env(t_list *env, char *key)
{
	t_env	*tmp;
	char	*ret;
	int		flag;

	flag = 0;
	ret = NULL;
	while (env)
	{
		tmp = env->content;
		if (ft_ultimatestrcmp(tmp->key, key, 0, &flag))
		{
			if (flag == 1)
				ret = ft_strdup(key + ft_ultimatestrcmp(tmp->key, key, 0,
							&flag));
			else
				ret = ft_strjoin(tmp->value, key + ft_ultimatestrcmp(tmp->key,
							key, 0, &flag));
			return (ret);
		}
		env = env->next;
	}
	return (ret);
}

void remove_quotes(t_list *lex)
{
	char *str = lex->content;
	int len = strlen(str);
	int i = 0;
	int j = 0;

	while (i < len)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			continue;
		}
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
}

int	ft_ultimatestrcmp(char *key, char *tmp, int i, int *flag)
{
	int	j;

	j = 0;
	while (tmp[i])
	{
		j = 0;
		while (tmp[i++] == key[j++])
		{
			if (!key[j])
			{
				if (!ft_isalnum(tmp[i]))
					return (i);
				while (ft_isalnum(tmp[i]))
					i++;
				if (tmp[i])
				{
					*flag = 1;
					return (i);
				}
				return (0);
			}
		}
		i++;
	}
	return (0);
}
