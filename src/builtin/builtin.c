/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:20:37 by ealbayra          #+#    #+#             */
/*   Updated: 2023/12/03 16:58:19 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin_command(t_parse *parse, t_shell *m_shell)
{
	t_parse	*new_parse;

	new_parse = parse;
	if ((ft_strcmp(new_parse->cmd, "echo") == 0)
		|| (ft_strcmp(new_parse->cmd, "ECHO") == 0))
		exec_echo(new_parse, m_shell);
	if (ft_strcmp(new_parse->cmd, "cd") == 0)
		exec_cd(new_parse, m_shell);
	if ((ft_strcmp(new_parse->cmd, "pwd") == 0)
		|| (ft_strcmp(new_parse->cmd, "PWD") == 0))
		exec_pwd(new_parse, m_shell);
	if (ft_strcmp(new_parse->cmd, "export") == 0)
		exec_export(new_parse, m_shell);
	if (ft_strcmp(new_parse->cmd, "unset") == 0)
		exec_unset(new_parse, m_shell, 0, 0);
	if (((ft_strcmp(new_parse->cmd, "env") == 0)
			|| (ft_strcmp(new_parse->cmd, "ENV") == 0)))
		exec_env(m_shell);
}

int	is_builtin(t_parse *data)
{
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
