/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateCmdTable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 02:53:58 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 02:53:58 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

void	create_cmdtable(t_lexlist *lex_table)
{
	int		count;

	if (!lex_table)
		return ;
	count = 1;
	while (lex_table)
	{
		if (lex_table->type == SIGN_PIPE)
			count++;
		else if (lex_table->type != TEXT)
		{
			lex_table = lex_table->next;
			if (lex_table && lex_table->type == SIGN_PIPE)
				lex_table = lex_table->next;
			continue ;
		}
		lex_table = lex_table->next;
	}
	create_cmdtable_nodes(count);
}

void	fill_cmdtable_node(t_cmdlist *node)
{
	node->pid = -1;
	node->infile = SSTDIN;
	node->outfile = SSTDOUT;
	node->cmd = NULL;
	node->path = NULL;
	node->next = NULL;
	node->files = NULL;
	node->heradoc_values = NULL;
}

void	create_cmdtable_nodes(int count)
{
	t_cmdlist	*temp_cmdtable;

	if (!count)
		return ;
	g_core.cmd_table = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	fill_cmdtable_node(g_core.cmd_table);
	temp_cmdtable = g_core.cmd_table;
	while ((--count))
	{
		temp_cmdtable->next = (t_cmdlist *)malloc(sizeof(t_cmdlist));
		fill_cmdtable_node(temp_cmdtable->next);
		temp_cmdtable = temp_cmdtable->next;
	}
}
