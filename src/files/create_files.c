/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:20:50 by ealbayra          #+#    #+#             */
/*   Updated: 2023/12/06 20:34:54 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	other_out_filesme(t_parse *parse)
{
	char	str[256];
	char	*pwd;
	char	*pwd1;
	t_parse	*nparse;

	getcwd(str, 256);
	nparse = parse->next;
	pwd = ft_strjoin(str, "/");
	pwd1 = ft_strjoin(pwd, nparse->text[0]);
	open(pwd1, O_CREAT | O_RDWR, 0777);
	free(pwd1);
	pwd1 = ft_strjoin(pwd, nparse->next->text[0]);
	if (nparse->type == 4)
		parse->fd = open(pwd1, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (parse->type == 3)
		parse->fd = open(pwd1, O_CREAT | O_RDWR | O_TRUNC, 0777);
	parse->outfile = parse->fd;
	if (pwd)
		free(pwd);
	if (pwd1)
		free(pwd1);
}

void	other_text_create_me(t_parse *current_parse)
{
	t_parse	*n_parse;
	int		i;
	int		j;

	n_parse = current_parse->next;
	i = 0;
	while (current_parse->text[i])
		i++;
	while (n_parse && n_parse->type != 2)
	{
		j = 1;
		while (n_parse->text[j])
		{
			current_parse->text[i] = ft_strdup(n_parse->text[j]);
			i++;
			j++;
		}
		n_parse = n_parse->next;
	}
	current_parse->text[i] = NULL;
	other_out_filesme(current_parse);
}

void	create_out_files_me(t_parse *current_parse, t_parse *first_parse)
{
	char	str[256];
	char	*pwd;
	t_parse	*m_next;
	char	*temp;

	getcwd(str, 256);
	m_next = current_parse->next;
	if (m_next->type == 3 || m_next->type == 4)
		return (other_text_create_me(current_parse));
	pwd = ft_strjoin(str, "/");
	temp = ft_strjoin(pwd, m_next->text[0]);
	free(pwd);
	pwd = temp;
	if (current_parse->type == 4)
		m_next->fd = open(pwd, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (current_parse->type == 3)
		m_next->fd = open(pwd, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (current_parse->cmd)
		current_parse->outfile = m_next->fd;
	else if (first_parse->cmd)
		first_parse->outfile = m_next->fd;
	if (pwd)
		free(pwd);
}

int	create_files_m(t_shell *m_shell)
{
	t_parse	*current_parse;
	t_parse  *first_parse;
	int		i;

	i = 1;
	current_parse = m_shell->parse;
	first_parse = m_shell->parse;
	while (current_parse)
	{
		if (current_parse->type == 3 || current_parse->type == 4)
			create_out_files_me(current_parse, first_parse);
		else if (current_parse->type == 5)
			i = create_in_files_me(current_parse);
		current_parse = current_parse->next;
	}
	return (i);
}
