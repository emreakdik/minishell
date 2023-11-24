/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaybaz <aaybaz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:35:47 by aaybaz            #+#    #+#             */
/*   Updated: 2023/07/20 01:05:00 by aaybaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	change_old(t_shell *shell, char *str)
{
	t_list	*tmp;
	t_env	*env;

	tmp = shell->env;
	while (tmp)
	{
		env = tmp->content;
		if (!ft_strcmp(env->key, "OLDPWD"))
		{
			if (env->value)
				free(env->value);
			env->value = str;
		}
		tmp = tmp->next;
	}
}

void	_change_pwd(t_env **env)
{
	char	cwd[1024];

	if (!ft_strcmp((*env)->key, "PWD"))
	{
		if ((*env)->value)
			free((*env)->value);
		(*env)->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
	}
}

void	change_pwd(t_shell *shell, t_parse	*data)
{
	t_list	*tmp;
	t_env	*env;
	char	cwd[1024];

	tmp = shell->env;
	while (tmp)
	{
		env = tmp->content;
		if (!ft_strcmp(env->key, "PWD")
			&& data->text && !ft_strcmp(data->text[0], "~"))
		{
			if (env->value)
				free(env->value);
			env->value = get_home(shell);
		}
		else if (!ft_strcmp(env->key, "PWD")
			&& data->text && !ft_strcmp(data->text[0], ".."))
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
		}
		_change_pwd(&env);
		tmp = tmp->next;
	}
}

void	exec_cd1(t_shell *shell, char *str, t_parse *data)
{
	change_old(shell, str);
	chdir(get_home(shell));
	change_pwd(shell, data);
	shell->exec_status = 0;
}

void	exec_cd(t_shell *shell, t_parse *data)
{
	char	cwd[1024];
	char	*str;

	str = ft_strdup(getcwd(cwd, sizeof(cwd)));
	if (data->text && data->text[0])
	{
		if (chdir(data->text[0]) == 0)
		{
			change_old(shell, str);
			change_pwd(shell, data);
			shell->exec_status = 1;
		}
		else
		{
			if (str)
				free(str);
			shell->exec_status = 1;
			perror("cd");
		}
	}
	else
		exec_cd1(shell, str, data);
}
