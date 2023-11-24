/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaybaz <aaybaz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:48:18 by aaybaz            #+#    #+#             */
/*   Updated: 2023/07/20 17:25:00 by aaybaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*search_command(char *cmd, char **value)
{
	char	*data;
	int		i;
	char	*tmp;
	char	*substring;

	tmp = *value;
	i = 0;
	(void)cmd;
	while (*tmp && *tmp != ':')
	{
		i++;
		tmp++;
	}
	if (!i)
		return (NULL);
	substring = ft_substr(*value, 0, i);
	data = ft_strjoin(substring, "/");
	free(substring);
	substring = ft_strjoin(data, cmd);
	free(data);
	*value = *value + i + 1;
	return (substring);
}

char	*_search_path(t_shell *shell)
{
	t_env	*env;
	t_list	*tmp;
	char	*value;

	value = NULL;
	tmp = shell->env;
	while (tmp)
	{
		env = tmp->content;
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			value = env->value;
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	search_path(t_shell *shell, t_parse *data, int i)
{
	char	*value;
	char	*str;
	int		x;

	x = -1;
	str = NULL;
	value = _search_path(shell);
	while (x != 0 && value && ++i < 10)
	{
		if (str)
			free(str);
		str = search_command(data->cmd, &value);
		x = access(str, F_OK);
	}
	if (x == 0)
	{
		if (data->cmd)
			free(data->cmd);
		data->cmd = ft_strdup(str);
	}
	if (str)
		free(str);
}

void	run_execve(t_shell *shell, t_list *data1, char **env, t_fd_params fd)
{
	char	**str;
	t_parse	*data;

	data = data1->content;
	search_path(shell, data, -1);
	data->pid = fork();
	str = NULL;
	if (!data->pid)
	{
		str = get_args(data, data1);
		create_dup(shell, data1, fd);
		if ((execve(data->cmd, str, env) == -1))
		{
			if (data->cmd && ft_strcmp(data->cmd, "<<"))
				printf("minishell: %s: command not found\n", data->cmd);
			execve_child_free(shell, str);
			exit(127);
		}
	}
	if (fd.fd && data->pid)
		clear_pipe(fd.fd);
	waitpid(data->pid, &shell->exec_status, 0);
	shell->exec_status = WEXITSTATUS(shell->exec_status);
}

void	exec_others(t_shell *shell, t_list *data, char **env, t_fd_params fd)
{
	run_execve(shell, data, env, fd);
}
