/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrintParser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 03:00:06 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 03:00:06 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

void	print_files(t_filelist *temp_filelist)
{
	while (temp_filelist)
	{
		printf("{fd: %d, ridrect : %s, filename : %s} ", temp_filelist->fd,
			temp_filelist->metachar, temp_filelist->filename);
		temp_filelist = temp_filelist->next;
	}
	printf("\n\n");
}

void	print_parser(void)
{
	int			node_count;
	int			index;
	t_cmdlist	*temp_cmdlist;

	node_count = 1;
	temp_cmdlist = g_core.cmd_table;
	while (temp_cmdlist)
	{
		index = 0;
		printf("------------NODE %d------------\n", node_count++);
		printf("PATH: ");
		while (temp_cmdlist->path && temp_cmdlist->path[index])
			printf("%s; ", (temp_cmdlist->path[index++]));
		printf("\nCMD: %s\n", temp_cmdlist->cmd);
		printf("infile: %d\n", temp_cmdlist->infile);
		printf("outfile: %d\n", temp_cmdlist->outfile);
		if (temp_cmdlist->heradoc_values)
			printf("heradoc values: %s\n", temp_cmdlist->heradoc_values);
		printf("pid: %d\n", temp_cmdlist->pid);
		printf("~files~\n");
		print_files(temp_cmdlist->files);
		temp_cmdlist = temp_cmdlist->next;
	}
}
