/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileErrorCheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 02:33:15 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 02:33:15 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

int	file_error_check(t_lexlist *lex_list)
{
	if (!lex_list->next || (lex_list->next && lex_list->next->type != TEXT))
	{
		if (lex_list->next)
		{
			print_error("-bash: syntax error near unexpected token '",
				lex_list->next->content, "'\n");
			g_core.exec_output = 2;
			free_lexer_without_heradoc(lex_list);
			return (0);
		}
		else
		{
			print_error("-bash: syntax error near unexpected token '",
				"newline", "'\n");
			g_core.exec_output = 2;
			free_lexer_without_heradoc(lex_list);
			return (0);
		}
	}
	return (1);
}
