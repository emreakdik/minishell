/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:24:35 by yakdik            #+#    #+#             */
/*   Updated: 2023/12/05 00:06:44 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	is_count_odd(char *before, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (before[i])
	{
		if (before[i] == c)
			count++;
		i++;
	}
	if (count % 2 == 1)
		return (1);
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

void	remove_quotes(t_list *lex)
{
	char	*str;
	int		i;
	int		j;
	char	quote_char;
	int		in_quotes;

	str = lex->content;
	i = 0, j = 0, in_quotes = 0;
	quote_char = '\0';
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && (!in_quotes
				|| quote_char == str[i]))
		{
			in_quotes = !in_quotes;
			if (in_quotes)
				quote_char = str[i];
			else
				quote_char = '\0';
		}
		else
		{
			str[j] = str[i];
			j++;
		}
		i++;
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
