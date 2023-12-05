/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:24:15 by bakilli           #+#    #+#             */
/*   Updated: 2023/12/05 14:50:01 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Bu fonksiyon, verilen lex listesini kullanarak bir parse ağacı oluşturur.
 *
 * @param lex Lex listesi
 * @param m_shell Shell yapısı
 * @param a Dizi
 */
void	mini_parse(t_list *lex, t_shell *m_shell, int a[3])
{
	char	*str;
	t_parse	*parse;

	/* Yeni bir parse bagli listesi olusturuluyor */
	parse = parse_init((size_t)ft_lstsize(lex));
	m_shell->parse = parse;
	while (lex != NULL)
	{
		str = lex->content;
		/**
			* Syntax kontrollerinden gecen komut'un ilk kelimesi ise komut olarak alinir.
			* a[0] artirilarak artik komutun ilk kelimesinde olmadigimiz bilinir.
			*/
		if (a[0]++ == 0 && ft_strcmp(str, "<<")) // << kontrolü
			parse->cmd = ft_strdup(str);
		/* parse yapisinin tipini ayarlamak icin metakarakter kontrolu yapiyoruz */
		else if (str[0] == '|' || str[0] == '>' || str[0] == '<')
		{
			/* eger pipe ise sonraki komut olacagi icin a[0] sifirlanmistir ve pipe tiplenmistir. */
			if (tokenize_type_m(&parse, str), str[0] == '|')
				a[0] = 0;
			parse->next = parse_init((size_t)ft_lstsize(lex));
			a[1] = 0;
			parse = parse->next;
		}
		/**
			*  metakarakter ve komut degilse text olarak alinir
			* a[1] text dizisinin indeksini tutar ki text'e arka arkaya ekleme yapabilelim
			* a[2] ise text dizisine ekleme yapildigini belirtir
			*/
		else if (ft_strcmp(str, ""))
			parse_text_m(parse, str, &a[1], &a[2]);
		lex = lex->next;
	}
	/**
		*  eger text dizisine ekleme yapilmamissa flag_ fonksiyonu cagirilir
		*  cunku text dizisi bos olmalidir
		*/
	if (a[2] == 0)
		flag_(parse);
}

/**
 * Bu fonksiyon,
	verilen t_shell yapısı üzerinde bir parser işlemi gerçekleştirir.
 * Parser işlemi,
	m_shell yapısının lex_listesindeki lex tokenlerini analiz eder ve gerekli işlemleri yapar.
 * İşlem sonucunda oluşan dosyaları oluşturur ve döndürür.
 *
 * @param m_shell t_shell yapısı
 * @return oluşturulan dosyaların durumunu döndürür
 */
int	ft_parser(t_shell *m_shell)
{
	int	a[3];

	a[0] = 0; // pipe sonrasinda miyiz kontrolu
	a[1] = 0; // text'in indeksini tutacak
	a[2] = 0; // text eklendi mi flag'i
	mini_parse(m_shell->lex_list->lex, m_shell, a);
	/* lexer'da olusturulan liste free'lendi cunku artik parser listesine sahibiz*/
	free_node(m_shell->lex_list->lex);
	return (create_files_m(m_shell));
}
