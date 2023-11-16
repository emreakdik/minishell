/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrintError.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:31:23 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:31:23 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

int	print_lex_error(t_lexlist *lex_list)
{
	print_error("-bash: syntax error near unexpected token '",
		lex_list->content, "'\n");
	g_core.exec_output = 2;
	free_lexer_without_heradoc(lex_list);
	return (0);
}

void	print_error(char *ptr1, char *ptr2, char *ptr3)
{
	if (ptr1)
		write(2, ptr1, ft_strlen(ptr1));
	if (ptr2)
		write(2, ptr2, ft_strlen(ptr2));
	if (ptr3)
		write(2, ptr3, ft_strlen(ptr3));
}
