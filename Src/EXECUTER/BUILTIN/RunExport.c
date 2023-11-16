/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunExport.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:42:46 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:42:46 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

void	run_export(t_cmdlist *cmd_node)
{
	int		array_len;
	char	**temp_path;

	array_len = get_array_len(cmd_node->path);
	if (array_len > 1)
	{
		temp_path = cmd_node->path;
		while (*(++temp_path))
			double_export_arg(*temp_path);
	}
	else
		single_export_arg(cmd_node);
}

void	single_export_arg(t_cmdlist *cmd_node)
{
	t_env	*env;

	env = g_core.env_table;
	while (env)
	{
		write(cmd_node->outfile, "declare -x ", 11);
		write(cmd_node->outfile, env->env_name, ft_strlen(env->env_name));
		if (!env->content)
		{
			write(cmd_node->outfile, "\n", 1);
			env = env->next;
			continue ;
		}
		write(cmd_node->outfile, "=\"", 2);
		write(cmd_node->outfile, env->content, ft_strlen(env->content));
		write(cmd_node->outfile, "\"\n", 2);
		env = env->next;
	}
}

void	double_export_arg(char *env_cmd)
{
	char	*arg;
	int		is_equal;
	t_env	*env;
	char	*temp_envname;

	if (!env_arg_control(env_cmd))
		return ;
	temp_envname = get_env_name(env_cmd);
	arg = env_cmd + ft_strlen(temp_envname);
	is_equal = 0;
	if (*arg == '=')
		is_equal |= 1;
	if (change_env(temp_envname, ++arg, is_equal))
	{
		free(temp_envname);
		return ;
	}
	env = g_core.env_table;
	add_newenv(&env, env_cmd);
	if (!is_equal)
		update_env(env_cmd, NULL);
	free(temp_envname);
}

int	change_env(char *envname, char *arg, int is_equal)
{
	t_env	*env;

	env = g_core.env_table;
	while (env)
	{
		if (str_compare(envname, env->env_name))
		{
			if (is_equal)
				update_env(envname, arg);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
