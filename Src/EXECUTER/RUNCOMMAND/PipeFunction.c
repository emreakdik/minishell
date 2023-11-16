/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PipeFunction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:43:56 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:43:56 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

int	*create_pipe(void)
{
	int		index;
	int		*fd;

	fd = (int *)malloc(sizeof(int) * 6);
	index = -1;
	while (++index < 6)
		fd[index] = 0;
	return (fd);
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
		free(fd);
	}
}

void	switch_pipe(int **fd)
{
	(*fd)[0] = (*fd)[0] ^ (*fd)[2];
	(*fd)[2] = (*fd)[0] ^ (*fd)[2];
	(*fd)[0] = (*fd)[0] ^ (*fd)[2];
	(*fd)[1] = (*fd)[1] ^ (*fd)[3];
	(*fd)[3] = (*fd)[1] ^ (*fd)[3];
	(*fd)[1] = (*fd)[1] ^ (*fd)[3];
	(*fd)[5] = (*fd)[5] ^ (*fd)[3];
	(*fd)[3] = (*fd)[5] ^ (*fd)[3];
	(*fd)[5] = (*fd)[5] ^ (*fd)[3];
	(*fd)[4] = (*fd)[2] ^ (*fd)[4];
	(*fd)[2] = (*fd)[2] ^ (*fd)[4];
	(*fd)[4] = (*fd)[2] ^ (*fd)[4];
}
