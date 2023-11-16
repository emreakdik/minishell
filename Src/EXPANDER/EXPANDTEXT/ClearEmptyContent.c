/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClearEmptyContent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 02:47:46 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 02:47:46 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/**
 * Fonksiyon adı: clear_void_contents
 * -------------------------------------
 * 
 * Bu fonksiyon, g_core.lex_table içindeki boş content'lere sahip olan t_lexlist
 * düğümlerini listeden çıkarır ve belleklerini serbest bırakır. Fonksiyon, listedeki
 * tüm düğümleri dolaşarak boş content'lere sahip olanları tespit eder ve listeden çıkarır.
 * 
 * Girdiler:
 *  - Yok
 * 
 * Çıktılar:
 *  - Yok
 */

void	clear_void_contents(void)
{
	t_lexlist	*lex_list;
	t_lexlist	*temp_lex_list;

	lex_list = g_core.lex_table;
	temp_lex_list = g_core.lex_table;
	while (lex_list)
	{
		if (!lex_list->content)
		{
			if (lex_list == g_core.lex_table)
			{
				g_core.lex_table = g_core.lex_table->next;
				temp_lex_list = temp_lex_list->next;
			}
			else
				temp_lex_list->next = lex_list->next;
			free(lex_list);
			lex_list = temp_lex_list;
		}
		temp_lex_list = lex_list;
		if (lex_list)
			lex_list = lex_list->next;
	}
}
