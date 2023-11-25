/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:28:18 by aaybaz            #+#    #+#             */
/*   Updated: 2023/11/25 19:08:56 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

void	_free_env(t_shell *shell, t_list *tmp2)
{
	t_env	*tmp;

	while (tmp2)
	{
		tmp = tmp2->content;
		if (tmp2->content)
		{
			if (tmp->key)
				free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
		}
		tmp2 = tmp2->next;
	}
	while (shell->env)
	{
		tmp2 = shell->env;
		shell->env = shell->env->next;
		if (tmp2)
			free(tmp2);
	}
}

void	free_env(t_shell *shell)
{
	t_list	*tmp2;

	tmp2 = shell->env;
	if (tmp2 && tmp2->content)
		_free_env(shell, tmp2);
	else if (shell->env && !shell->env->content)
		free(shell->env);
}

void	free_(t_shell *shell)
{
	free_env(shell);
	clear_history();
}

void	free_loop(t_shell *shell, int control)
{
	if (shell->cmd)
		free(shell->cmd);
	if (control)
	{
		if (shell->parse)
			free_parser(shell);
	}
	if (shell->heredoc)
	{
		free(shell->heredoc);
		shell->heredoc = NULL;
	}
	free(shell->title);
}

void	execve_child_free(t_shell *shell, char **str)
{
	free_(shell);
	free_loop(shell, 1);
	free_text(str);
	free(shell->lex_list);
	free(shell);
}
