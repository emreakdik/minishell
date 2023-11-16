/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:56:29 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 13:56:29 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/**
 * @brief Sinyal işleyicisi fonksiyonu.
 * 
 * @param signum Sinyal numarası.
 * 
 * Bu fonksiyon, sinyal işleyicisi olarak kullanılır. Sinyal alındığında, 
 * sinyal numarasına göre işlem yapar. Eğer sinyal okuma işlemi sırasında 
 * alındıysa, işlem yapmadan geri döner. Eğer bir komut çalışırken sinyal 
 * alındıysa, işlem yapmadan geri döner. Aksi takdirde, sinyal numarasını 
 * g_core.exec_output değişkenine atar ve bir alt satıra geçer. Ardından, 
 * bellekten ayrılmış olan tüm verileri serbest bırakır ve readline 
 * kütüphanesinin rl_on_new_line() ve rl_redisplay() fonksiyonlarını 
 * çağırarak yeni bir satır oluşturur ve ekrana yazar.
 * 
 * @return void
 */
void	sig_handler(int signum)
{
	(void)signum;
	if (signal_in_reading())
		return ;
	if (signal_while_cmd_works())
		return ;
	g_core.exec_output = SIGNAL_C;
	write(1, "\n", 1);
	free_for_loop();
	rl_on_new_line();
	// rl_replace_line("", 0); calismiyor 
	rl_redisplay();
}

/**
 * @brief Okuma işlemi sırasında sinyal alınıp alınmadığını kontrol eder.
 * 
 * Bu fonksiyon, okuma işlemi sırasında sinyal alınıp alınmadığını kontrol 
 * eder. Eğer sinyal alındıysa, g_core.exec_output değişkenine SIGNAL_C 
 * değerini atar ve 1 değerini döndürür. Aksi takdirde, 0 değerini döndürür.
 * 
 * @return int 1: Sinyal alındı, 0: Sinyal alınmadı.
 */
int	signal_in_reading(void)
{
	if (getpid() != g_core.main_pid && g_core.is_read_arg)
	{
		write(1, "\n", 1);
		free_for_loop();
		free_core();
		exit(SIGNAL_C);
	}
	else if (g_core.is_read_arg)
	{
		g_core.exec_output = SIGNAL_C;
		return (1);
	}
	return (0);
}

/**
 * @brief Komut çalışırken sinyal alınıp alınmadığını kontrol eder.
 * 
 * Bu fonksiyon, komut çalışırken sinyal alınıp alınmadığını kontrol eder. 
 * Eğer sinyal alındıysa, 1 değerini döndürür. Aksi takdirde, 0 değerini 
 * döndürür.
 * 
 * @return int 1: Sinyal alındı, 0: Sinyal alınmadı.
 */
int	signal_while_cmd_works(void)
{
	t_cmdlist	*cmd_list;
	int			return_value;

	if (getpid() != g_core.main_pid)
		return (1);
	return_value = 0;
	cmd_list = g_core.cmd_table;
	while (cmd_list)
	{
		if (cmd_list->pid >= 0)
			return_value |= waitpid(cmd_list->pid, 0, 0);
		cmd_list = cmd_list->next;
	}
	if (return_value && getpid() == g_core.main_pid)
	{
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

/**
 * @brief Çıkış sinyali alınıp alınmadığını kontrol eder.
 * 
 * Bu fonksiyon, çıkış sinyali alınıp alınmadığını kontrol eder. Eğer 
 * g_core.cmd değişkeni NULL ise, "Exit" yazısını ekrana yazar ve bellekten 
 * ayrılmış olan tüm verileri serbest bırakarak programı sonlandırır.
 * 
 * @return void
 */
void	exit_signal_check(void)
{
	if (!g_core.cmd)
	{
		write(1, "Exit\n", 6);
		free_core();
		exit(EXIT_SUCCESS);
	}
}
