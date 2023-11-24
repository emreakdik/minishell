/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaniber <akaniber@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:31:17 by aaybaz            #+#    #+#             */
/*   Updated: 2023/10/15 14:54:32 by akaniber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void	other_out_files(t_list *tmp3, t_list *tmp)
{
	char	str[256];
	char	*pwd;
	char	*pwd1;
	t_parse	*data;
	t_parse	*garbage;

	getcwd(str, 256);
	data = tmp->content;
	garbage = tmp3->next->content;
	pwd = ft_strjoin(str, "/");
	pwd1 = ft_strjoin(pwd, garbage->text[0]);
	if (garbage->text)
		open(pwd1, O_CREAT | O_RDWR, 0777);
	free(pwd1);
	pwd1 = ft_strjoin(pwd, data->text[0]);
	data = tmp3->content;
	if (data->type == 4)
		data->fd = open(pwd1, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (data->type == 3)
		data->fd = open(pwd1, O_CREAT | O_RDWR | O_TRUNC, 0777);
	data->outfile = data->fd;
	if (pwd)
		free(pwd);
	if (pwd1)
		free(pwd1);
}

void	other_text_create(t_list *tmp3, t_list *tmp)
{
	t_parse	*data;
	t_parse	*data2;
	int		i;
	int		j;

	i = 0;
	data = tmp3->content;
	while (data->text[i])
		i++;
	data2 = tmp->content;
	while (tmp->next && data2->type != 2)
	{
		j = 1;
		data2 = tmp->content;
		while (data2->text[j])
		{
			data->text[i] = ft_strdup(data2->text[j]);
			i++;
			j++;
		}
		tmp = tmp->next;
	}
	data->text[i] = NULL;
	other_out_files(tmp3, tmp);
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

void	create_out_files(t_parse *data3, t_list *tmp3, t_parse *tmp1)
{
	t_parse	*data;
	t_list	*tmp;
	t_parse	*value;
	char	str[256];
	char	*pwd;

	getcwd(str, 256);
	tmp = tmp3->next;
	value = tmp->content;
	if (value->type == 3 || value->type == 4)
		return (other_text_create(tmp3, tmp));
	pwd = ft_strjoin(str, "/");
	tmp3 = tmp3->next;
	data = tmp3->content;
	pwd = ft_strjoin2(pwd, data->text[0]);
	if (data3->type == 4)
		data->fd = open(pwd, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (data3->type == 3)
		data->fd = open(pwd, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (data3->cmd)
		data3->outfile = data->fd;
	else if (tmp1->cmd)
		tmp1->outfile = data->fd;
	if (pwd)
		free(pwd);
}

int	create_files(t_shell *shell)
{
	t_parse	*data;
	t_list	*tmp;
	t_parse	*tmp1;
	int		i;

	i = 1;
	tmp = shell->parse;
	while (tmp)
	{
		data = tmp->content;
		if (data->cmd)
			tmp1 = data;
		if (data->type == 3 || data->type == 4)
			create_out_files(data, tmp, tmp1);
		else if (data->type == 5)
			i = create_in_files(data, tmp);
		tmp = tmp->next;
	}
	return (i);
}
