/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpandLexList.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:43:22 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 14:43:22 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/**
 * expand_values_from_lexlist fonksiyonu, g_core.lex_table'daki t_lexlist yapısındaki
 * tüm öğeleri dolaşarak, TEXT tipindeki öğeleri expand_text fonksiyonuna gönderir.
 * SIGN_PIPE tipindeki öğeleri atlar. SIGN_DOUBLE_LESS tipindeki öğelerin bir sonraki
 * öğe ile expand_text fonksiyonuna gönderilmesini sağlar.
 * 
 * @param void
 * @return void
 */

void	expand_values_from_lexlist(void)
{
	t_lexlist	*lex_table;

	lex_table = g_core.lex_table;
	while (lex_table)
	{
		if (lex_table->type == TEXT) 
			expand_text(lex_table, 0);
		else if (lex_table->next && lex_table->type != SIGN_PIPE)
		{
			if (lex_table->type != SIGN_DOUBLE_LESS)
				expand_text(lex_table->next, 1);
			lex_table = lex_table->next;
		}
		lex_table = lex_table->next;
	}
}

/**
 * expand_text fonksiyonu, verilen t_lexlist yapısındaki content değerini expand eder.
 * Fonksiyon, content içindeki $ ve ~ karakterlerini tespit ederek, expand_order fonksiyonunu
 * çağırır. Fonksiyon, content içindeki ' ve " karakterlerini de dikkate alarak, expand işlemini
 * gerçekleştirir.
 * 
 * @param lex_table expand edilecek t_lexlist yapısı
 * @param is_after_meta meta karakterlerinden sonra gelen bir öğe mi?
 * @return void
 */

void	expand_text(t_lexlist *lex_table, int is_after_meta)
{
	char	*cmd;
	int		flag;
	char	*ptr;

	cmd = lex_table->content;
	ptr = NULL;
	flag = 0;
	while (*cmd)
	{
		/**
		 * bu noktada flag tek tirnak mi yoksa cift tirnak icerisinde mi oldugumuzu tutmakta.
		 * flag'in 1 olmasi tek tirnak icerisinde oldugumuzu soyler o yuzden icerideki hicbir sey genisletilmez
		 * flag 2 ise cift tirnak icerisinde oldugumuzu soyler bu yuzden dolar ve tilda isaretleri genisletilir
		 * 
		 * flag ^ 1 kullanimi flag 1 ise flag'i 0 yapar, eger flag 0 ise flag'i 1 yapar
		 * bu durum su sekilde aciklanabilir: 
		 * flag eger sifir ise content'i okumaya yeni basladik demektir /
		 * contentte eger tek tirnak ile karsilasilirsa flag 1 yapilir ve 
		 * tekrar tek tirnak ile karsilasilana kadar hicbir sey genisletilmez
		 * tekrar tek tirnak ile karsilasildiginda ise flag ^ 1 islemi ile 1 olan flag 0 yapilir
		 * 
		 * flag ^ 2 kullanimi flag eger 2 ise flag'i sifir yapar, flag eger 0 ise flag'i 2 yapar.
		 * 
		 * Fonksiyonun sonundaki yorum satirinda uygulamali aciklama var
		*/
		if (*cmd == '\'' && (!flag || flag == 1)) 
			flag = flag ^ 1;
		else if (*cmd == '\"' && (!flag || flag == 2))
			flag = flag ^ 2;
		else if ((!flag || flag == 2) && (*cmd == *DOLLAR || *cmd == *TILDA))
			expand_order(&ptr, &cmd);
		else
			str_addchar(&ptr, *cmd);
		cmd++;
	}
	if (is_after_meta && !ptr)
		return ;
	free(lex_table->content);
	lex_table->content = ptr;
}

/**
#include <stdio.h>

int main(){

    int flag = 0;

    // burada flag'in sifir oldugu durumdayiz yani tirnak icerisinde degiliz
    flag = flag ^ 2;
    printf("first: %d\n", flag);

    // burada ise flag'in sifir olmadigi yani tirnak icerisindeyken 
    // tekrar tirnak'a yani bitise denk gelisimizdeyiz
    flag = flag ^ 2;
    printf("second: %d\n", flag);
}
*/