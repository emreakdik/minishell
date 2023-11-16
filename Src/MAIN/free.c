/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:43:42 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 14:43:42 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	free_core(void)
{
	free_metachars();
	free_envtable();
	free_title();
	clear_history();
}

void	free_for_loop(void)
{
	if (g_core.cmd)
	{
		free(g_core.cmd);
		g_core.cmd = NULL;
	}
	if (g_core.lex_table)
		free_lexer();
	if (g_core.cmd_table)
		free_parser();
	close_heradoc_file();
}
