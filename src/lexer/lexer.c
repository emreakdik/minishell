/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:21:22 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/28 20:25:07 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	ignore_quote(char const *cmd, int i)
{
	if (cmd[i] == '\"')
	{
		i++;
		while (cmd[i] != '\"')
			i++;
	}
	else if (cmd[i] == '\'')
	{
		i++;
		while (cmd[i] != '\'')
			i++;
	}
	return (i);
}

static int	len_for_separate(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !*cmd)
		return (0);
	if (cmd[i] == '<' && cmd[i + 1] == '<')
		return (2);
	if (cmd[i] == '>' && cmd[i + 1] == '>')
		return (2);
	if (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|')
		return (1);
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '>' && cmd[i] != '<'
		&& cmd[i] != '|')
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			i = ignore_quote(cmd, i) + 1;
		}
		else
			i++;
	}
	return (i);
}

static void	separate_cmd(char *cmd, t_lexer **lex_list)
{
	int		len;
	char	*content;
	char	*trimmed_content;

	if (!cmd || !*cmd)
		return ;
	cmd = ft_strtrim(cmd, " ");
	len = len_for_separate(cmd);
	content = ft_substr(cmd, 0, len);
	trimmed_content = ft_strtrim(content, " ");
	free(content);
	ft_lstadd_back(&(*lex_list)->lex, ft_lstnew(trimmed_content));
	separate_cmd(cmd + len, lex_list);
	free(cmd);
}

// static void	print_lexer(t_lexer *lex_list)
// {
// 	t_list	*lex;

// 	lex = lex_list->lex;
// 	while (lex)
// 	{
// 		printf(";;%s;;\n", (char *)lex->content);
// 		lex = lex->next;
// 	}
// 	printf("\n");
// }

void	lexer(t_shell *shell)
{
	shell->lex_list->lex = NULL;
	separate_cmd(shell->cmd, &shell->lex_list);
	// print_lexer(shell->lex_list);
}
