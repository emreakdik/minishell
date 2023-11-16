/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunUnset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:41:07 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:41:07 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

void	run_unset(t_cmdlist *cmd_node)
{
	char	**temp_name;
	int		array_len;

	array_len = get_array_len(cmd_node->path);
	if (array_len > 1)
	{
		temp_name = cmd_node->path;
		while (*(++temp_name))
		{
			if (!env_arg_control(*temp_name))
			{
				print_error("-bash: unset: `", *temp_name,
					"': not a valid identifier\n");
				g_core.exec_output = 1;
				continue ;
			}
			else
				delete_env(*temp_name);
		}
	}
}

void	delete_env(char *name)
{
	t_env	*env;
	t_env	*temp_env;

	env = g_core.env_table;
	while (env)
	{
		if (str_compare(env->env_name, name))
		{
			if (env->content)
				free(env->content);
			free(env->env_name);
			if (g_core.env_table == env)
				g_core.env_table = g_core.env_table->next;
			else
				temp_env->next = env->next;
			free(env);
			break ;
		}
		temp_env = env;
		env = env->next;
	}
}
