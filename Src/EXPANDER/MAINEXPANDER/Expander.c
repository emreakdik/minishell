/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:43:16 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 14:43:16 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
** Bu fonksiyon, lex listesindeki değerleri genişletir ve ardından boş içerikleri temizler.
*/
void	expander(void)
{
	if (g_core.exec_output == 2)
		return ;
	expand_values_from_lexlist();
	clear_void_contents();
}
