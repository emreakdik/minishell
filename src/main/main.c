/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:07:54 by akaniber          #+#    #+#             */
/*   Updated: 2023/11/25 09:52:05 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

int	g_does_have_heredoc;

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
	shell->cmd = readline("minishell-$ ");
	if (shell->cmd && !is_space(shell->cmd))
	{
		free(shell->cmd);
		get_readline(shell);
	}
	if (!shell->cmd)
	{
		free_loop(shell, 0);
		free_(shell);
		free(shell->lex_list);
		free(shell);
		exit(1);
	}
	add_history(shell->cmd);
}

void	go_parser(t_shell *shell, char **env)
{
	if (ft_strcmp(shell->cmd, ""))
	{
		if (ft_parser(shell))
			exec(shell, env);
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
			if (control)
				go_parser(shell, env);
			else
				error_free(&(shell->lex_list)->lex);
		}
		free_loop(shell, control);
		system("leaks minishell");
	}
}
