/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SynaxCheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:25:10 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 14:25:10 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
** syntax_check fonksiyonu, g_core.lex_table'daki tüm token'ları dolaşarak
** syntax_error_check fonksiyonunu çağırır ve hatalı bir syntax bulunursa
** işlemi sonlandırır. Eğer bir syntax hatası yoksa işlemi devam ettirir.
*/
void	syntax_check(void)
{
	t_lexlist	*lex_list;
	int			syntax_error;

	lex_list = g_core.lex_table;
	while (lex_list)
	{
		syntax_error = syntax_error_check(lex_list);
		if (syntax_error == -1)
			break ;
		else if (!syntax_error)
			continue ;
		if (g_core.lex_table)
			lex_list = lex_list->next;
		else
			lex_list = NULL;
	}
}

/*
** syntax_error_check fonksiyonu, aldığı t_lexlist struct'ının tipine göre
** ilgili syntax hatasını kontrol eder. Eğer bir syntax hatası yoksa 1 değerini
** döndürür. Eğer bir syntax hatası varsa -1 veya 0 değerini döndürür. -1
** değeri, hatanın kritik olduğunu ve işlemin sonlandırılması gerektiğini
** belirtir. 0 değeri ise hatanın kritik olmadığını ve işlemin devam
** ettirilebileceğini belirtir.
*/
int	syntax_error_check(t_lexlist *lex_list)
{
	int	pipe_error;

	if (lex_list == g_core.lex_table && lex_list->type == SIGN_PIPE) // ilk node ise ve tip'i pipe ise hata
	{																// cunku komutun baslangicinda pipe olamaz
		print_lex_error(lex_list);
		return (-1);
	}
	else if (lex_list->type != TEXT && lex_list->type != SIGN_PIPE) // meta karakter ise 
	{
		if (!file_error_check(lex_list))							// sonrasinda text var mi kontrolu
			return (-1);
	}
	else if (lex_list->type == SIGN_PIPE) // pipe ise
	{
		pipe_error = pipe_error_check(lex_list); // bu fonksiyonun notlari iceride
		if (pipe_error < 0)
			return (0);
		else if (!pipe_error)
			return (-1);
	}
	return (1);
}
