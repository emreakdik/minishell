/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunCommand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:44:30 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:44:30 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

void	run_multiple_command(t_cmdlist *cmd_list)
{
	int			*fd;

	fd = create_pipe();
	while (cmd_list)
	{
		switch_pipe(&fd);
		pipe(&fd[2]);
		cmd_list->pid = fork();
		if (cmd_list->pid <= 0)
			run_process(cmd_list, fd, 2);
		cmd_list = cmd_list->next;
		if (fd[4] && fd[5])
		{
			close(fd[4]);
			close(fd[5]);
			fd[4] = 0;
			fd[5] = 0;
		}
	}
	clear_pipe(fd);
	wait_all();
}

void	run_single_command(t_cmdlist *cmd_list, int *fd)
{
	if (cmd_list->infile != SSTDERR && cmd_list->outfile != SSTDERR)
		exec_command(cmd_list, fd, -1);
}
