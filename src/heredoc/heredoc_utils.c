/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:30:56 by aaybaz            #+#    #+#             */
/*   Updated: 2023/11/21 18:21:09 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>

void	killer(int sig)
{
	(void)sig;
	g_does_have_heredoc = -3;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	// rl_replace_line("", 0);
	rl_on_new_line();
}

void	set_heredoc(int sig)
{
	(void)sig;
	g_does_have_heredoc = -10;
}
