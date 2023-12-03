/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:20:50 by ealbayra          #+#    #+#             */
/*   Updated: 2023/12/03 17:08:10 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	other_out_filesme(t_parse *parse)
{
	char		str[256];
	char		*pwd;
	char		*pwd1;
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

void	other_text_create_me(t_parse *m_parse)
{
	t_parse	*n_parse;
	int			i;
	int			j;

	n_parse = m_parse->next;
	i = 0;
	while (m_parse->text[i])
		i++;
	while (n_parse->next && n_parse->type != 2)
	{
		j = 1;
		while (n_parse->text[j])
		{
			m_parse->text[i] = ft_strdup(n_parse->text[j]);
			i++;
			j++;
		}
		n_parse = n_parse->next;
	}
	m_parse->text[i] = NULL;
	other_out_filesme(m_parse);
}

char	*ft_strjoin2(char *s1, const char *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free(s1);
	return (str);
}

void	create_out_files_me(t_parse *m_parse, t_parse *prev_parse)
{
	char		str[256];
	char		*pwd;
	t_parse	*m_next;

	getcwd(str, 256);
	m_next = m_parse->next;
	if (m_next->type == 3 || m_next->type == 4)
		return (other_text_create_me(m_parse));
	pwd = ft_strjoin(str, "/");
	pwd = ft_strjoin2(pwd, m_next->text[0]);
	if (m_parse->type == 4)
		m_next->fd = open(pwd, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (m_parse->type == 3)
		m_next->fd = open(pwd, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (m_parse->cmd)
		m_parse->outfile = m_next->fd;
	else if (prev_parse->cmd)
		prev_parse->outfile = m_next->fd;
	if (pwd)
		free(pwd);
}

int	create_files_m(t_shell *m_shell)
{
	t_parse	*parse;
	int			i;

	i = 1;
	parse = m_shell->parse;
	while (parse)
	{
		if (parse->type == 3 || parse->type == 4)
			create_out_files_me(parse, m_shell->parse);
		else if (parse->type == 5)
			i = create_in_files_me(parse);
		parse = parse->next;
	}
	return (i);
}
