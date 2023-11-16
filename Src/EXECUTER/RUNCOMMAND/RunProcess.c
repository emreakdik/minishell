/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunProcess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:45:34 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:45:34 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

void	run_process(t_cmdlist *cmd_list, int *fd, int fd_index)
{
	if (cmd_list->infile != SSTDERR && cmd_list->outfile != SSTDERR)
		exec_command(cmd_list, fd, fd_index);
	else
		clear_pipe(fd);
	free_for_loop();
	free_core();
	exit(g_core.exec_output);
}

void	wait_all(void)
{
	t_cmdlist	*cmd_list;

	cmd_list = g_core.cmd_table;
	while (cmd_list)
	{
		if (!cmd_list->next)
			waitpid(cmd_list->pid, &g_core.exec_output, 0);
		else
			waitpid(cmd_list->pid, 0, 0);
		cmd_list = cmd_list->next;
	}
	g_core.exec_output = WEXITSTATUS(g_core.exec_output);
}
