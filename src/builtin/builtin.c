/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:52:18 by aaybaz            #+#    #+#             */
/*   Updated: 2023/11/21 18:20:51 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_builtin_command(t_shell *shell, t_list *tmp, t_fd_params fd)
{
	t_parse	*data;

	data = tmp->content;
	if (fd.fd)
		create_dup(shell, tmp, fd);
	if ((ft_strcmp(data->cmd, "echo") == 0)
		|| (ft_strcmp(data->cmd, "ECHO") == 0))
		exec_echo(shell, data);
	if (ft_strcmp(data->cmd, "cd") == 0)
		exec_cd(shell, data);
	if ((ft_strcmp(data->cmd, "pwd") == 0)
		|| (ft_strcmp(data->cmd, "PWD") == 0))
		exec_pwd(shell, data);
	if (ft_strcmp(data->cmd, "export") == 0)
		exec_export(shell, data);
	if (ft_strcmp(data->cmd, "unset") == 0)
		exec_unset(shell, data);
	if (((ft_strcmp(data->cmd, "env") == 0)
			|| (ft_strcmp(data->cmd, "ENV") == 0)))
		exec_env(shell);
}

int	is_builtin(t_list *tmp)
{
	t_parse	*data;

	data = tmp->content;
	if ((ft_strcmp(data->cmd, "echo") == 0)
		|| (ft_strcmp(data->cmd, "ECHO") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "pwd") == 0)
		|| (ft_strcmp(data->cmd, "PWD") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "env") == 0)
		|| (ft_strcmp(data->cmd, "ENV") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "cd") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "export") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "unset") == 0))
		return (1);
	return (0);
}

void	ft_newlstiter(t_list *lst, void (*f)(t_shell *, void *), t_shell *shell)
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(shell, lst->content);
		lst = lst->next;
	}
}
