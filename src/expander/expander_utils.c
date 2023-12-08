/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:24:35 by yakdik            #+#    #+#             */
/*   Updated: 2023/12/08 16:42:37 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	there_is_no_env(t_shell *shell, t_list *lex, char **key)
{
	int		i;
	int		j;
	char	*temp;

	if (!*key)
		return (0);
	i = 0;
	j = 0;
	if (*key && !ft_isalnum((*key)[1]))
	{
		if (ft_strchr(*key + 1, '$'))
		{
			*key = ft_strchr(*key + 1, '$');
			expand_dollar_variable(shell, lex, *key);
		}
	}
	else
	{
		while ((*key)[i] && ft_isalnum((*key)[i]) && (*key)[i] != '$')
			i++;
		j = i;
		while ((*key)[j] && (*key)[j] != '$')
			j++;
		temp = ft_substr(*key, i, j - i);
		*key = temp;
	}
	return (1);
}

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

char	*get_env(t_shell *shell, t_list *env, t_list *lex, char *key)
{
	t_env	*tmp;
	char	*ret;
	int		flag;

	flag = 0;
	ret = NULL;
	if (!key)
		return (NULL);
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
	if (there_is_no_env(shell, lex, &key))
		ret = ft_strdup(key);
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
	return (0);
}
