/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunCd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:39:25 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:39:25 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

void	run_cd(t_cmdlist *cmd_node)
{
	int		array_len;

	array_len = get_array_len(cmd_node->path);
	if (array_len > 2)
	{
		g_core.exec_output = 1;
		print_error("-bash: cd: too many arguments\n", NULL, NULL);
	}
	else if (array_len == 2)
		cd_double_arg(cmd_node);
	else
		cd_single_arg();
}

void	cd_single_arg(void)
{
	t_env	*temp_env;
	char	*content;

	temp_env = g_core.env_table;
	while (temp_env)
	{
		if (str_compare("HOME", temp_env->env_name))
		{
			content = temp_env->content;
			if (!content)
				return ;
			change_dir(content);
			return ;
		}
		temp_env = temp_env->next;
	}
	print_error("-bash: cd: HOME not set\n", NULL, NULL);
	g_core.exec_output |= 1;
}

void	cd_double_arg(t_cmdlist *cmd_node)
{
	if (!change_dir(cmd_node->path[1]))
	{
		print_error("--bash: cd: ", cmd_node->path[1],
			": No such file or directory\n");
		g_core.exec_output = 1;
		return ;
	}
}

int	change_dir(char *path)
{
	char	pwd[256];
	int		is_pwdaccess;
	char	*oldpwd;
	int		error;

	oldpwd = ft_strdup(getcwd(pwd, 256));
	error = chdir(path);
	if (error == -1)
	{
		if (oldpwd)
			free(oldpwd);
		return (0);
	}
	is_pwdaccess = update_pwd_from_export("PWD", getcwd(pwd, 256));
	if (is_pwdaccess)
		update_pwd_from_export("OLDPWD", oldpwd);
	else
		delete_env("OLDPWD");
	if (oldpwd)
		free(oldpwd);
	change_title();
	return (1);
}

int	update_pwd_from_export(char *pwd_name, char *pwd_content)
{
	t_env	*temp_env;
	char	*temp_pwd;

	if (!update_env(pwd_name, pwd_content))
	{
		temp_env = g_core.env_table;
		temp_pwd = NULL;
		own_strjoin(&temp_pwd, pwd_name);
		str_addchar(&temp_pwd, '=');
		own_strjoin(&temp_pwd, pwd_content);
		add_newenv(&temp_env, temp_pwd);
		free(temp_pwd);
		return (0);
	}
	return (1);
}
