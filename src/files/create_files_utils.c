/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:20:44 by ealbayra          #+#    #+#             */
/*   Updated: 2023/12/17 17:52:48 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	handle_relative_path(char **pwd, t_parse *current_parse)
{
	char	*str;
	char *temp;
	t_parse *m_next;

	str = getcwd(NULL, 0);
	m_next = current_parse->next;
	*pwd = ft_strjoin(str, "/");
	temp = ft_strjoin(*pwd, m_next->text[0]);
	free(*pwd);
	*pwd = temp;
}

// int	is_absolue_path_in(char *pwd, t_parse *parse, t_shell *shell)
// {
// 	char	*home;
// 	t_parse	*next_parse;

// 	home = get_env(shell->env, "HOME");
// 	next_parse = parse->next;
// 	if (ft_strnstr(pwd, home, ft_strlen(home)))
// 	{
// 		if (!access(pwd, F_OK))
// 			next_parse->fd = open(pwd, O_RDONLY, 0777);
// 		else
// 		{
// 			printf("minishell: %s: No such file or directory\n",
// 				next_parse->text[0]);
// 			return (0);
// 		}
// 		parse->infile = next_parse->fd;
// 		return (1);
// 	}
// 	free(home);
// 	return (0);
// }

int	create_in_files_me(t_parse *parse, t_shell *shell)
{
	t_parse	*nparse;
	char	str[256];
	char	*pwd;
	char	*tmp;
	char	*home;

	home = get_env(shell->env, "HOME");
	nparse = parse->next;
	if (!ft_strnstr(nparse->text[0], home, ft_strlen(home)))
	{
		getcwd(str, 256);
		tmp = ft_strjoin(str, "/");
		pwd = ft_strjoin(tmp, nparse->text[0]);
		if (tmp)
			free(tmp);
	}
	else
		pwd = ft_strdup(nparse->text[0]);
	if (!access(pwd, F_OK))
		nparse->fd = open(pwd, O_RDONLY, 0777);
	else
	{
		if (pwd)
			free(pwd);
		printf("minishell: %s: No such file or directory\n", nparse->text[0]);
		return (0);
	}
	if (pwd)
		free(pwd);
	parse->infile = nparse->fd;
	return (1);
}
