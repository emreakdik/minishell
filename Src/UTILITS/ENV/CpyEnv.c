/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CpyEnv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:32:04 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:32:04 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

int	get_env_len(void)
{
	t_env	*env_list;
	int		count;

	env_list = g_core.env_table;
	count = 0;
	while (env_list)
	{
		if (env_list->content)
			count++;
		env_list = env_list->next;
	}
	return (count);
}

char	**get_env_cpy(void)
{
	int		env_len;
	char	**envlist;
	char	*temp_env;
	t_env	*temp_envlist;

	env_len = get_env_len();
	envlist = (char **)malloc(sizeof(char *) * (env_len + 1));
	envlist[env_len] = NULL;
	temp_envlist = g_core.env_table;
	while (temp_envlist)
	{
		if (temp_envlist->content)
		{
			temp_env = NULL;
			own_strjoin(&temp_env, temp_envlist->env_name);
			str_addchar(&temp_env, '=');
			own_strjoin(&temp_env, temp_envlist->content);
			envlist[--env_len] = temp_env;
		}
		temp_envlist = temp_envlist->next;
	}
	return (envlist);
}

void	free_env_cpy(char **envlist)
{
	char	**temp_envlist;

	temp_envlist = envlist;
	while (*temp_envlist)
		free(*(temp_envlist++));
	free(envlist);
}
