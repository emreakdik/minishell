/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FillCmdTable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 02:55:57 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 02:55:57 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
** fill_cmdtable - Komut tablosunu doldurur.
**
** Girdiler:
** 		- Yok
**
** Çıktılar:
** 		- Yok
**
** Açıklama:
** 		Komut tablosunu doldurmak için kullanılır. Komut tablosu, komutların
** 		tutulduğu bir veri yapısıdır. Bu fonksiyon, komut tablosundaki her bir
** 		komut için fill_cmdnode fonksiyonunu çağırır.
*/

void	fill_cmdtable(void)
{
	t_cmdlist	*temp_cmdtable;
	t_lexlist	*temp_lexlist;

	if (!g_core.cmd_table)
		return ;
	temp_cmdtable = g_core.cmd_table;
	temp_lexlist = g_core.lex_table;
	while (temp_cmdtable)
	{
		fill_cmdnode(temp_cmdtable, &temp_lexlist);
		if (temp_lexlist && *temp_lexlist->content == *PIPE)
			temp_lexlist = temp_lexlist->next;
		temp_cmdtable = temp_cmdtable->next;
	}
}

/*
** fill_cmdnode - Komut düğümünü doldurur.
**
** Girdiler:
** 		- node: Komut düğümü
** 		- lex_list: Lex listesi
**
** Çıktılar:
** 		- Yok
**
** Açıklama:
** 		Komut düğümünü doldurmak için kullanılır. Komut düğümü, bir komutun
** 		tutulduğu bir veri yapısıdır. Bu fonksiyon, komut düğümünün path ve cmd
** 		alanlarını doldurur.
*/

void	fill_cmdnode(t_cmdlist *node, t_lexlist **lex_list)
{
	char	**path_holder;
	int		is_begin;

	node->path = create_path(*lex_list);
	path_holder = node->path;
	is_begin = 0;
	while (*lex_list && (*lex_list)->type != SIGN_PIPE)
	{
		if (create_new_filelist(node, lex_list))
			continue ;
		if (!(is_begin++) && (*lex_list)->content)
			expand_cmd(&((*lex_list)->content));
		if ((*lex_list)->content)
			*(path_holder++) = (*lex_list)->content;
		*lex_list = (*lex_list)->next;
	}
	if (node->path)
		node->cmd = node->path[0];
}
