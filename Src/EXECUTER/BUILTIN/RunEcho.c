/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunEcho.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:41:52 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:41:52 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

void	run_echo(t_cmdlist *cmd_node)
{
	char	**path;
	int		is_n;

	is_n = 0;
	path = &cmd_node->path[1];
	if (*path && str_compare(*path, "-n"))
	{
		is_n = 1;
		path++;
	}
	while (*path)
	{
		if (*path)
			write(cmd_node->outfile, *path, ft_strlen(*path));
		if (*(++path))
			write(cmd_node->outfile, " ", 1);
	}
	if (!is_n)
		write(cmd_node->outfile, "\n", 1);
}
