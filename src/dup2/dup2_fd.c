/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaniber <akaniber@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:40:40 by aaybaz            #+#    #+#             */
/*   Updated: 2023/10/15 13:29:53 by akaniber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	_create_dup(t_shell *shell)
{
	int		new_fd[2];

	pipe(new_fd);
	write(new_fd[1], shell->heredoc,
		ft_strlen(shell->heredoc));
	dup2(new_fd[0], 0);
	close (new_fd[1]);
	close(new_fd[0]);
}

void	create_dup(t_shell *shell, t_list *data1, t_fd_params fd)
{
	t_parse	*data;
	t_parse	*tmp;

	tmp = NULL;
	if (data1->next)
		tmp = data1->next->content;
	data = data1->content;
	if (data->type == HEREDOC)
		_create_dup(shell);
	else if (data->infile > STDERR)
		dup2(data->infile, 0);
	else if (fd.fd && data->control != 1)
		dup2(fd.fd[fd.fd_index - 2], 0);
	if (data->outfile > STDERR)
		dup2(data->outfile, 1);
	else if (data->infile > STDERR && data1->next->next)
		dup2(fd.fd[fd.fd_index + 1], 1);
	else if (data->type == HEREDOC && data1->next->next)
		dup2(fd.fd[fd.fd_index + 1], 1);
	else if (data1->next && fd.fd && tmp->cmd)
		dup2(fd.fd[fd.fd_index + 1], 1);
	if (fd.fd_index >= 0)
		clear_pipe(fd.fd);
}

void	clear_pipe(int *fd)
{
	int	index;

	if (fd)
	{
		index = -1;
		while (++index < 6)
		{
			if (fd[index])
				close(fd[index]);
		}
		if (fd)
			free(fd);
	}
}

void	switch_pipe(int **fd)
{
	int	temp;

	temp = (*fd)[0];
	(*fd)[0] = (*fd)[2];
	(*fd)[2] = temp;
	temp = (*fd)[1];
	(*fd)[1] = (*fd)[3];
	(*fd)[3] = temp;
	temp = (*fd)[5];
	(*fd)[5] = (*fd)[3];
	(*fd)[3] = temp;
	temp = (*fd)[2];
	(*fd)[2] = (*fd)[4];
	(*fd)[4] = temp;
}

void	wait_all(t_shell *shell)
{
	t_list	*cmd_list;
	t_parse	*data;

	cmd_list = shell->parse;
	while (cmd_list)
	{
		data = cmd_list->content;
		if (!cmd_list->next)
			waitpid(data->pid, &shell->exec_status, 0);
		else
			waitpid(data->pid, 0, 0);
		cmd_list = cmd_list->next;
	}
	shell->exec_status = WEXITSTATUS(shell->exec_status);
}
