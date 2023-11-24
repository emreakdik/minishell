/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaybaz < aaybaz@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:23:11 by akaniber          #+#    #+#             */
/*   Updated: 2023/10/25 00:53:11 by aaybaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

char	*add_char(char *str, char a)
{
	char	*tmp;
	int		i;
	int		len;

	len = ft_strlen(str);
	tmp = malloc(sizeof(char) * (len + 2));
	if (!tmp)
		return (NULL);
	i = 0;
	if (!a)
	{
		free(tmp);
		return (NULL);
	}
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = a;
	tmp[i + 1] = '\0';
	free(str);
	return (tmp);
}

void	get_var(t_shell *shell, int *fd)
{
	char	*a;

	a = malloc(sizeof(char));
	if (!a)
	{
		shell->heredoc = NULL;
		return ;
	}
	shell->heredoc = ft_calloc(sizeof(char), 2);
	if (!shell->heredoc)
	{
		free(a);
		return ;
	}
	while (read(fd[0], a, 1))
	{
		shell->heredoc = add_char(shell->heredoc, *a);
		free(a);
		a = malloc(sizeof(char));
	}
	if (a)
		free(a);
	close(fd[0]);
}

void	get_input(t_list *tmp, int *fd)
{
	char	*delimiter;
	char	*buffer;
	t_parse	*parse_list;

	parse_list = tmp->next->content;
	delimiter = parse_list->text[0];
	while (1 && g_does_have_heredoc != -3)
	{
		buffer = readline("> ");
		if (buffer && ft_strcmp(buffer, delimiter) == 0)
		{
			free(buffer);
			break ;
		}
		if (!buffer)
			break ;
		write(fd[1], buffer, ft_strlen(buffer));
		write(fd[1], "\n", 1);
		if (buffer)
			free(buffer);
	}
}

void	heredoc(t_shell *shell, t_list *tmp)
{
	int		fd[2];
	int		id;

	pipe(fd);
	signal(SIGINT, set_heredoc);
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, killer);
		close(fd[0]);
		get_input(tmp, fd);
		close(fd[1]);
		free_(shell);
		free_loop(shell, 1);
		free(shell->lex_list);
		free(shell);
		exit(1);
	}
	waitpid(-1, NULL, 0);
	signal(SIGINT, signals);
	close(fd[1]);
	get_var(shell, fd);
}

void	loop_heredoc(t_shell *shell)
{
	t_list	*tmp;
	t_parse	*parse_list;

	tmp = shell->parse;
	while (tmp)
	{
		parse_list = tmp->content;
		if (parse_list->type == HEREDOC)
			heredoc(shell, tmp);
		tmp = tmp->next;
	}
}
