/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PipeErrorCheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:25:24 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 14:25:24 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/**
 * Bu fonksiyon, verilen lex_list yapısının pipe hatası içerip içermediğini kontrol eder.
 * Eğer pipe hatası içeriyorsa, print_lex_error fonksiyonunu çağırarak hata mesajı yazdırır.
 * Eğer pipe hatası içermiyorsa, run_miss_arg fonksiyonunu çağırarak eksik argüman hatası kontrolü yapar.
 * 
 * @param lex_list pipe hatası kontrolü yapılacak olan lex_list yapısı.
 * @return pipe hatası yoksa 1, varsa -1 veya print_lex_error fonksiyonunun dönüş değeri.
 */
int	pipe_error_check(t_lexlist *lex_list)
{
	if (lex_list->next && lex_list->next->type == SIGN_PIPE) // pipe sonrasinda da pipe varsa 
		return (print_lex_error(lex_list));					// yan yana iki tane pipe olmaz
	else if (!lex_list->next)
		return (run_miss_arg(lex_list));
	/**
	 * pipe sonrasinda bir girdi yoksa terminal bu girdiyi tamamlamak icin kullanicidan bir standart girdi ister
	 * bu eksik girdigi run_miss_arg fonksiyonu ile sagliyoruz.
	 * uygulamali olarak bu durumu "ls |" komutunu girerek gorebiliriz.
	*/
	return (1);
}

/**
 * Bu fonksiyon, verilen lex_list yapısının eksik argüman hatası içerip içermediğini kontrol eder.
 * Eğer eksik argüman hatası içeriyorsa, get_missing_arg fonksiyonunu çağırarak eksik argümanı alır ve
 * create_lexlist fonksiyonunu çağırarak yeni bir lex_list yapısı oluşturur.
 * 
 * @param lex_list Eksik argüman hatası kontrolü yapılacak olan lex_list yapısı.
 * @return Eksik argüman hatası yoksa 1, varsa get_missing_arg fonksiyonunun dönüş değeri.
 */
int	run_miss_arg(t_lexlist *lex_list)
{
	char	*ptr;

	ptr = get_missing_arg(); // standart girdi ile eksik argumani alir
	if (!ptr)
		return (1);
	create_lexlist(ptr, &lex_list);
	classify(lex_list);
	str_addchar(&g_core.cmd, ' ');
	own_strjoin(&g_core.cmd, ptr);
	free(ptr);
	if (str_compare(lex_list->next->content, PIPE))
		return (-1);
	return (1);
}
