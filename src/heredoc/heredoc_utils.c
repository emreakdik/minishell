/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:24:46 by ealbayra          #+#    #+#             */
/*   Updated: 2023/12/16 19:24:46 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

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
