/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaniber <akaniber@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:38:42 by aaybaz            #+#    #+#             */
/*   Updated: 2023/10/16 14:31:48 by akaniber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>

void	exec_pwd(t_shell *shell, t_parse *data)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(data->outfile, &cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		shell->exec_status = 0;
	}
	else
	{
		perror("getcwd");
		shell->exec_status = 1;
	}
}

char	*get_home(t_shell *shell)
{
	t_list	*tmp;
	t_env	*env;

	tmp = shell->env;
	while (tmp)
	{
		env = tmp->content;
		if (!ft_strcmp(env->key, "HOME"))
			return (env->value);
		tmp = tmp->next;
	}
	return (NULL);
}
