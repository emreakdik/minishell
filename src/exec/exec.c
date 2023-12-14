/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:21:19 by ealbayra          #+#    #+#             */
/*   Updated: 2023/12/13 22:38:05 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	run_command(char **env, t_parse *tmp, int *fd, t_shell *m_shell)
{
	int			control;

	control = is_builtin(tmp);
	if (control)
		execute_builtin_command(tmp, m_shell);
	else
		exec_others(tmp, env, fd, m_shell);
	free_(m_shell);
	free_loop(1, m_shell);
	free(m_shell->lex_list);
	free(m_shell);
	exit(0);
}

void	run_single_command(char **env, t_parse *parse, t_shell *m_shell)
{
	int	control;

	control = 0;
	if (parse->type != HEREDOC)
		control = is_builtin(parse);
	if (control)
		execute_builtin_command(m_shell->parse, m_shell);
	else
		exec_others(m_shell->parse, env, NULL, m_shell);
}

void	multi_command_(t_parse *parse, char **env, t_shell *m_shell, int *fd)
{
	t_parse	*nparse;

	while (parse)
	{
		if (parse->next)
			pipe(fd);
		nparse = _next_command(&parse);
		parse->pid = fork();
		if (parse->pid == 0)
		{
			create_dup_one(parse, fd);
			run_command(env, parse, fd, m_shell);
		}
		if (nparse)
			create_dup_two(nparse, fd);
		parse = nparse;
	}
}

void	multi_command(char **env, int x, t_parse *parse, t_shell *m_shell)
{
	int			*fd;

	(void)x;
	m_shell->parse->std_in = dup(0);
	fd = (int *)malloc(sizeof(int) * 2);
	if (!fd)
		return ;
	multi_command_(parse, env, m_shell, fd);
	dup2(m_shell->parse->std_in, 0);
	clear_pipe(fd);
	wait_all(m_shell);
}

void	exec(char **env, t_shell *m_shell)
{
	int			x;

	if (g_does_have_heredoc != 0)
		loop_heredoc(m_shell);
	if (!ft_strcmp(m_shell->cmd, ""))
		return ;
	if (m_shell->parse->cmd)
	{
		if (ft_strcmp(m_shell->parse->cmd, "exit") == 0
			&& g_does_have_heredoc != -10)
		{
			free_(m_shell);
			free_loop(1, m_shell);
			free(m_shell->lex_list);
			free(m_shell);
			write(1, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
	}
	x = single_or_multi_command(m_shell);
	if (!x && g_does_have_heredoc != -10)
		run_single_command(env, m_shell->parse, m_shell);
	else if (g_does_have_heredoc != -10)
		multi_command(env, 0, m_shell->parse, m_shell);
	g_does_have_heredoc = 0;
}
