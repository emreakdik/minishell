/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FreeParser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 02:56:24 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 02:56:24 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

void	free_parser(void)
{
	t_cmdlist	*parser;
	t_cmdlist	*temp_parser;

	parser = g_core.cmd_table;
	while (parser)
	{
		temp_parser = parser;
		parser = parser->next;
		free_filelist(temp_parser->files);
		if (temp_parser->path)
			free(temp_parser->path);
		if (temp_parser->heradoc_values)
			free(temp_parser->heradoc_values);
		free(temp_parser);
	}
	g_core.cmd_table = NULL;
}

void	free_filelist(t_filelist *files)
{
	t_filelist	*temp_files;

	while (files)
	{
		temp_files = files;
		files = files->next;
		if (temp_files->fd > SSTDERR)
			close(temp_files->fd);
		free(temp_files);
	}
}
