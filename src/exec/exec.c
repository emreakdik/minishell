/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaybaz < aaybaz@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:23:06 by akaniber          #+#    #+#             */
/*   Updated: 2023/10/23 23:38:51 by aaybaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	run_command(t_shell *shell, char **env, t_list *tmp, t_fd_params fd)
{
	int	control;

	control = is_builtin(tmp);
	if (control)
		execute_builtin_command(shell, tmp, fd);
	else
		exec_others(shell, tmp, env, fd);
	free_(shell);
	free_loop(shell, 1);
	free(shell->lex_list);
	free(shell);
	exit(0);
}

void	run_single_command(t_shell *shell, char **env, t_list *data)
{
	t_fd_params	fd;
	int			control;

	fd.fd = NULL;
	fd.fd_index = -1;
	control = is_builtin(data);
	if (control)
		execute_builtin_command(shell, shell->parse, fd);
	else
		exec_others(shell, shell->parse, env, fd);
}

void	_multi_command(void **_data, t_list **tmp)
{
	t_parse	**data;

	data = (t_parse **)_data;
	if ((*data)->infile > STDERR || (*data)->outfile > STDERR
		|| (*data)->type == HEREDOC)
		(*tmp) = (*tmp)->next->next;
	else
		(*tmp) = (*tmp)->next;
}

void	multi_command(t_shell *shell, char **env, int x, t_list	*tmp)
{
	t_fd_params	fd;

	fd.fd = create_pipe();
	fd.fd_index = 2;
	while (tmp)
	{
		switch_pipe(&fd.fd);
		pipe(&fd.fd[2]);
		((t_parse *)(tmp->content))->pid = fork();
		if (x++ == 0)
			((t_parse *)(tmp->content))->control = 1;
		if (((t_parse *)(tmp->content))->pid == 0)
			run_command(shell, env, tmp, fd);
		_multi_command(&tmp->content, &tmp);
		if (fd.fd[4] && fd.fd[5])
		{
			close(fd.fd[4]);
			close(fd.fd[5]);
			fd.fd[4] = 0;
			fd.fd[5] = 0;
		}
	}
	clear_pipe(fd.fd);
	wait_all(shell);
}

void	exec(t_shell *shell, char **env)
{
	int		x;
	t_list	*tmp;
	t_parse	*parse;

	tmp = shell->parse;
	parse = tmp->content;
	if (g_does_have_heredoc != 0)
		loop_heredoc(shell);
	if (!ft_strcmp(shell->cmd, ""))
		return ;
	if (ft_strcmp(parse->cmd, "exit") == 0 && g_does_have_heredoc != -10)
	{
		free_(shell);
		free_loop(shell, 1);
		free(shell->lex_list);
		free(shell);
		write(1, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	x = single_or_multi_command(shell);
	if (!x && g_does_have_heredoc != -10)
		run_single_command(shell, env, shell->parse);
	else if (g_does_have_heredoc != -10)
		multi_command(shell, env, 0, shell->parse);
	g_does_have_heredoc = 0;
}
