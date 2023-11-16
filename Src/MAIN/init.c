/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:48:59 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 13:48:59 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/**
 * @brief Minishell'in çekirdek fonksiyonu olan init_core'un çalışma mantığını açıklar.
 * 
 * @param env Minishell'in çalışacağı ortam değişkenlerini içeren dizi.
 * 
 * @details Bu fonksiyon, Minishell'in çekirdek özelliklerini başlatır. Bu özellikler arasında, 
 * ortam değişkenlerinin doldurulması, metakarakterlerin ayarlanması, başlık ayarlarının yapılması 
 * ve diğer bazı değişkenlerin başlatılması yer alır.
 */
void	init_core(char **env)
{
	fill_envs(env);
	set_metachars();
	set_title();
	g_core.exec_output = 0;
	g_core.old_exec_output = 0;
	g_core.main_pid = getpid(); // getpid yasak
}
