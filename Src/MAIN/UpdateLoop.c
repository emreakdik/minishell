/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UpdateLoop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:00:55 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 14:00:55 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/**
 * @brief Bu fonksiyon, minishell'in ana döngüsünü günceller.
 * 
 * update_exec_output() fonksiyonunu çağırır ve g_core.is_read_arg değişkenini sıfırlar.
 */
void	update_loop(void)
{
	update_exec_output();
	g_core.is_read_arg = 0;
}

/**
 * @brief Bu fonksiyon, kullanıcının girdiği komutu tarihe ekler.
 * 
 * @param cmd Eklenecek komut.
 */
void	update_history(char *cmd)
{
	char	*ptr;

	if (!cmd)
		return ;
	ptr = cmd;
	trim_spaces(&ptr);
	if (!*ptr)
		return ;
	add_history(cmd);
}

/**
 * @brief Bu fonksiyon, g_core.exec_output ve g_core.old_exec_output değişkenlerini günceller.
 * 
 * g_core.old_exec_output ve g_core.exec_output değişkenlerinin değerlerini birbirleriyle değiştirir.
 * 
 */
void	update_exec_output(void)
{
	g_core.old_exec_output = g_core.old_exec_output ^ g_core.exec_output;
	g_core.exec_output = g_core.old_exec_output ^ g_core.exec_output;
	g_core.old_exec_output = g_core.old_exec_output ^ g_core.exec_output;
	g_core.exec_output = 0;
}
