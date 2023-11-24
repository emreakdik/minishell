/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaniber <akaniber@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:22:56 by akaniber          #+#    #+#             */
/*   Updated: 2023/10/13 18:18:32 by akaniber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

char	*get_hard(t_list *lex)
{
	char	*str;
	char	*ret;
	int		i;

	i = 0;
	str = (char *)lex->content;
	ret = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	free_tmp(t_list *tmp)
{
	while (tmp)
	{
		free(tmp->content);
		tmp = tmp->next;
	}
	free(tmp);
}

void	free_node(t_list *node)
{
	if (!node)
		return ;
	if (node->next != NULL)
		free_node(node->next);
	if (node->content)
		node->content = (free(node->content), NULL);
	if (node)
		node = (free(node), NULL);
}

void	parse_priority_order(t_shell *shell, t_lexer *lexer)
{
	t_parse_params	params;
	t_list			*new_node;
	t_list			*new;
	t_list			*tmp;
	char			*str;

	new_node = NULL;
	new = NULL;
	str = NULL;
	tmp = lexer->lex;
	memset(&params, 0, sizeof(params));
	while (lexer->lex)
	{
		str = get_hard(lexer->lex);
		if (new_node == NULL)
			new_node = ft_lstnew(str);
		else
			new = ft_lstnew((str));
		ft_lstadd_back(&new_node, new);
		lexer->lex = lexer->lex->next;
	}
	free_node(tmp);
	welcome_to_parse(shell, new_node, params);
	free_node(new_node);
}

int	ft_parser(t_shell *shell)
{
	parse_priority_order(shell, shell->lex_list);
	return (create_files(shell));
}
