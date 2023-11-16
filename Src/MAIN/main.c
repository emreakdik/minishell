/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:49:11 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 14:01:51 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	init_core(env); // cevre degiskenlerini, meta karakterleri ve full_title degiskenini hazirliyoruz.
	signal(SIGINT, &sig_handler);
	while (1)
	{
		update_loop();
		g_core.cmd = readline(g_core.title.full_title); // prompt ile girdi
		exit_signal_check();
		lexer(); // girdiyi tokenlara boluyoruz ve syntax kontrol ediyoruz
		expander(); // tokenlerin genisleme islemini tamamliyoruz
		parser();
		executer();
		update_history(g_core.cmd);
		free_for_loop();
	}
	free_core();
}
