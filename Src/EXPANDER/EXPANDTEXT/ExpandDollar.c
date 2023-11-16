/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpandDollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:49:31 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 16:49:31 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/**
 * Buradaki genisletmelerden once notlarimdaki $$ ya da $? vb. kullanimlarin ne olduguna bakmak mantikli olacaktir.
*/

/**
 * @brief Dolar işaretiyle başlayan değişkenleri genişletir.
 * 
 * @param dst Değişkenin genişletilmiş hali burada saklanır.
 * @param src Genişletilecek değişkenin adresi.
 */

void	expand_dollar(char **dst, char **src)
{
	char	*ptr;

	ptr = (*src) + 1;
	if (*ptr == *DOLLAR)
		double_dollar(dst, src); // Dolar isaretinden sonra tekrar dolar isareti gelirse
	else if (*ptr == *QUSTION_MARK) 
		question_mark(dst, src); // Dolar isaretinden sonra ? gelirse
	else if (*ptr == ' ' || !*ptr || *ptr == *DOUBLE_QUOTE
		|| *ptr == *SINGLE_QUOTE)
		single_dollar(dst); // Dolar isaretinden sonra tirnak kullanimi // burada fix gerekebilir
	else
		expand_dollar_value(dst, src); // normal kullanim yani $USER gibi
}

/**
 * @brief Tek dolar işareti genişletmesi yapar.
 * 
 * @param dst Değişkenin genişletilmiş hali burada saklanır.
 */

void	single_dollar(char **dst)
{
	str_addchar(dst, *DOLLAR);
}

/**
 * @brief Çift dolar işareti genişletmesi yapar.
 * 
 * @param dst Değişkenin genişletilmiş hali burada saklanır.
 * @param src Genişletilecek değişkenin adresi.
 */

void	double_dollar(char **dst, char **src)
{
	char	*line;

	line = ft_itoa(g_core.main_pid); 
	own_strjoin(dst, line);
	free(line);
	(*src)++;
}

/**
 * @brief Soru işareti genişletmesi yapar.
 * 
 * @param dst Değişkenin genişletilmiş hali burada saklanır.
 * @param src Genişletilecek değişkenin adresi.
 */

void	question_mark(char **dst, char **src)
{
	char	*line;

	line = ft_itoa(g_core.old_exec_output);
	own_strjoin(dst, line);
	free(line);
	(*src)++;
}

/**
 * @brief Dolar işaretiyle başlayan değişkenin değerini genişletir.
 * 
 * @param dst Değişkenin genişletilmiş hali burada saklanır.
 * @param src Genişletilecek değişkenin adresi.
 */

void	expand_dollar_value(char **dst, char **src)
{
	int		count;
	char	*ptr;

	count = 0;
	ptr = (*src) + 1;
	while (*ptr != ' ' && *(ptr) && *ptr != *DOUBLE_QUOTE
		&& *ptr != *SINGLE_QUOTE && *ptr != '$') // degisken isminin uzunlugu alindi
	{
		count++;
		ptr++;
	}
	ptr = ft_strpcpy(NULL, (*src) + 1, count); // dolar sonrasindan degisken ismi uzunlugu kadar alindi
	expand_envs(dst, ptr); // alinan pointer expand envs ile bagli listede arandi ve dst'ye yerlestirildi
	free(ptr);
	*src += count;
}
