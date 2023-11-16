/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateLexTable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:10:44 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 14:10:44 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	Count degiskenine komutun ne kadar genislikte olmasi gerektigi get_cmdlen 
	fonksiyonu ile atanir.
	count buyuklugu kadar bellekte alan acilir ve bu alana count
	degiskeninde ki miktar kadar atanir.
	komutun adresi cmd_line degiskeninde tutuldugundan dolayi adres 
	uzerinden arttirilma islemleri yapilir.
	Boylece fonksiyonun cagirildigi yerde de adres arttirilmis olur.
*/
void	parse_cmd(char **cmd_line, t_lexlist *last_node)
{
	size_t	count;
	char	*holder_content;

	count = get_cmdlen(*cmd_line); // ayristirilacak kelimenin uzunlugu alinir
	holder_content = (char *)malloc(sizeof(char) * (count) + 1);
	last_node->content = holder_content;
	holder_content[count] = 0;
	while (count--) // alinan uzunluk kadar kopyalama islemi gerceklestirilir.
		*(holder_content++) = *((*cmd_line)++);
}

/*
	Gelen komutta oncelikle bosluklar gecilir ardindan komutta sona gelinip
 	gelinmedigi kontrol edilir, geldi ise fonksiyon sonlandirilir.
	Eger sona gelinmedi ise yeni lexer listesinde yeni bir node olusturulur
	 ve olusturulan yeni node komut ayiriciya gonderilir.
	Ardindan recurisive ile komut sona gelene kadar fonksiyon tekrardan cagirilir.
*/
void	create_lexlist(char *cmdline, t_lexlist **lex_table)
{
	t_lexlist	*last_node;

	trim_spaces(&cmdline); // bosluklar gecilir 
	if (!cmdline || !*cmdline)
		return ;
	last_node = add_new_lex_node(lex_table); // yeni ve bos node eklenir
	parse_cmd(&cmdline, last_node); // olusturulan bos node'a ayristirilan kelime/token eklenir
	create_lexlist(cmdline, lex_table); // recursive ile dongu saglanir
}
