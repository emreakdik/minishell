/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:02:01 by emre              #+#    #+#             */
/*   Updated: 2023/12/06 13:32:36 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

int		g_does_have_heredoc;

void	shell_init(t_shell **shell)
{
	*shell = malloc(sizeof(t_shell));
	(*shell)->env = malloc(sizeof(t_env));
	(*shell)->lex_list = malloc(sizeof(t_lexer));
	(*shell)->lex_list->lex = NULL;
	g_does_have_heredoc = 0;
	(*shell)->exec_status = 0;
	(*shell)->heredoc = NULL;
	(*shell)->cmd = NULL;
}

void	get_readline(t_shell *shell)
{
	get_title_from_env(&shell);
	shell->cmd = readline(shell->title);
	if (shell->cmd && !is_space(shell->cmd))
	{
		free(shell->cmd);
		free(shell->title);
		get_readline(shell);
	}
	if (!shell->cmd)
	{
		free_loop(0, shell);
		free_(shell);
		free(shell->lex_list);
		free(shell);
		exit(1);
	}
	add_history(shell->cmd);
}

/**
 * Bu fonksiyon, shell komutunu analiz eder ve gerekli işlemleri gerçekleştirir.
 *
 * @param shell Shell yapısı
 * @param env Çevre değişkenleri dizisi
 */
void	go_parser(t_shell *shell, char **env, int control)
{
	if (!control)
	{
		error_free(&(shell->lex_list)->lex);
		return ;
	}
	if (ft_strcmp(shell->cmd, ""))
	{
		if (ft_parser(shell))
			exec(env, shell);
	}
}

void	error_free(t_list **node)
{
	if (!*node)
		return ;
	if ((*node)->next != NULL)
		free_node((*node)->next);
	if ((*node)->content)
		(*node)->content = (free((*node)->content), NULL);
	if ((*node))
		(*node) = (free(*node), NULL);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;
	int		control;

	(void)av;
	control = 0;
	if (ac != 1)
		exit(write(2, "This program cannot accept any arguments\n", 41));
	shell_init(&shell);
	env_get(env, &shell);
	signals_control();
	while (1)
	{
		get_readline(shell);
		if (quote_check(shell->cmd))
		{
			lexer(shell);
			expander(shell);
			control = check(shell);
			go_parser(shell, env, control);
		}
		else
		{
			(free(shell->cmd), free(shell->title));
			continue ;
		}
		free_loop(control, shell);
	}
}
