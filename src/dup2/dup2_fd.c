/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:20:58 by ealbayra          #+#    #+#             */
/*   Updated: 2023/12/03 17:02:16 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	_create_dup(t_shell *m_shell)
{
	int		new_fd[2];

	pipe(new_fd);
	write(new_fd[1], m_shell->heredoc,
		ft_strlen(m_shell->heredoc));
	dup2(new_fd[0], 0);
	close (new_fd[1]);
	close(new_fd[0]);
}

void	create_dup(t_shell *m_shell, t_parse *parse)
{
	(void)m_shell;
	if (parse->infile > STDERR)
		dup2(parse->infile, 0);
	if (parse->outfile > STDERR)
		dup2(parse->outfile, 1);
}

void	create_dup_one(t_parse *parse, int *fd)
{
	t_parse	*new_parse;

	new_parse = parse->next;
	close(fd[0]);
	if (new_parse->next && fd && new_parse->cmd)
		dup2(fd[1], 1);
	else if (new_parse->type == HEREDOC && new_parse->next->next)
		dup2(fd[1], 1);
	close(fd[1]);
}

void	create_dup_two(t_parse *parse, int *fd, int fd_index, t_shell *m_shell)
{
	(void)fd_index;
	close(fd[1]);
	if (parse->type == HEREDOC)
		_create_dup(m_shell);
	else if (fd)
		dup2(fd[0], 0);
	close(fd[0]);
}
