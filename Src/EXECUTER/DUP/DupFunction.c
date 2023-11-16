/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DupFunction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:43:13 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:43:13 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

void	create_dup(t_cmdlist *cmd_list, int *fd, int fd_index)
{
	int	new_fd[2];

	if (cmd_list->infile == HERADOC)
	{
		pipe(new_fd);
		write(new_fd[1], cmd_list->heradoc_values,
			ft_strlen(cmd_list->heradoc_values));
		dup2(new_fd[0], STDIN_FILENO);
		close (new_fd[1]);
		close(new_fd[0]);
	}
	else if (cmd_list->infile > SSTDERR)
		dup2(cmd_list->infile, STDIN_FILENO);
	else if (fd && cmd_list != g_core.cmd_table)
		dup2(fd[fd_index - 2], STDIN_FILENO);
	if (cmd_list->outfile > SSTDERR)
		dup2(cmd_list->outfile, STDOUT_FILENO);
	else if (fd && cmd_list->next)
		dup2(fd[fd_index + 1], STDOUT_FILENO);
	if (fd_index >= 0)
		clear_pipe(fd);
}
