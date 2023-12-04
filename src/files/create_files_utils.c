/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:20:44 by ealbayra          #+#    #+#             */
/*   Updated: 2023/12/05 00:51:24 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int	create_in_files_me(t_parse *parse)
{
	t_parse	*nparse;
	char		str[256];
	char		*pwd;
	char		*tmp;

	nparse = parse->next;
	getcwd(str, 256);
	tmp = ft_strjoin(str, "/");
	pwd = ft_strjoin(tmp, nparse->text[0]);
	if (tmp)
		free(tmp);
	if (!access(pwd, F_OK))
		nparse->fd = open(pwd, O_RDONLY, 0777);
	else
	{
		if (pwd)
			free(pwd);
		printf("minishell: %s: No such file or directory\n", parse->text[0]);
		return (0);
	}
	if (pwd)
		free(pwd);
	parse->infile = nparse->fd;
	return (1);
}
