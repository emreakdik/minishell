/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Classify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:17:16 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 14:17:16 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"
/*
	olusturulmus lexer bagli listesinde ki her nodeda bulunan 
	sozcuklerin tipi belirlenir.
	bu olusturulan tiplerin karsiliklari "lexer.h"'da define edilmistir
	oradan karsiliklari gorulebilir ve kontrol islemleri
	orda define edilmis degiskenler uzerinden yapilabilir.
*/

void	classify(t_lexlist *lex_table)
{
	char	*metachars;

	if (!lex_table)
		return ;
	while (lex_table)
	{
		metachars = compare_metachars(lex_table->content); // meta karakter mi kontrolu
		if (metachars)
			lex_table->type = (*metachars - 1) * ft_strlen(metachars); // meta karakterse (ascii deger -1 x uzunluk) uzerinden tip atamasi yapiliyor.
		else
			lex_table->type = 0;
		lex_table = lex_table->next;
	}
}
