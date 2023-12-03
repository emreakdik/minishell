/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:24:35 by yakdik            #+#    #+#             */
/*   Updated: 2023/12/02 17:23:32 by yakdik           ###   ########.fr       */
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

/**
 * this function will remove quotes that paired just itselfs with each other
 * and not replace them remove them in given node
*/
void	remove_quotes(t_list *node)
{
	char *temp = node->content;
	int i = 0;
	int j = 0;

	while(temp[i]){
		if (temp[i] == '\''){
			j = i;
			while(temp[++i] != '\'');
			if (!temp[i]){
				i = ++j;
			}
			else{
				temp[i] = '\0';
				temp = ft_strjoin(temp + j, temp + i + 1);
				node->content = temp;
				i = j;
			}
		}
		else if (temp[i] == '\"'){
			j = i;
			while(temp[++i] != '\"');
			if (!temp[i]){
				i = ++j;
			}
			else{
				temp[i] = '\0';
				temp = ft_strjoin(temp + j, temp + i);
				node->content = temp;
				i = j;
			}
		}
		i++;
	}
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
