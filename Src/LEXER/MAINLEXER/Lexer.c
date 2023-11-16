/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:02:11 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 14:17:29 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	Lexer 4 asamali projenin ilk asamasidir. Burada amac
	girilen karisik komutlari sozcuk yapilarina ayirmaktir.
	orn komut: <a.txt cat| ls| wc -l | echo "ahmet $HOME''"selam
	lexer calistiktan sonra bagil liste deki
	contentlerin ciktisi soyle olmalidir:
	<, a.txt, cat, |, ls, |, wc, -l, |, echo, "ahmet $HOME''"selam'$PATH'
*/
void	lexer(void)
{
	g_core.lex_table = NULL;
	create_lexlist(g_core.cmd, &(g_core.lex_table)); // tokenlerimizi isleyecegimiz bagli liste olusturulur
	classify(g_core.lex_table); // tokenlerin tip numaralari atanir.
	syntax_check(); // syntax kontrolu
}
