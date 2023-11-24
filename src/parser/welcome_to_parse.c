/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome_to_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaniber <akaniber@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:30:38 by aaybaz            #+#    #+#             */
/*   Updated: 2023/10/15 13:36:51 by akaniber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void	parse_if(t_shell *shell, t_list *new, t_parse **parse)
{
	if (!new->next && shell->parse->content == NULL)
		shell->parse->content = (*parse);
	else if (shell->parse->content != NULL && !new->next)
		(*parse)->text = (free((*parse)->text), \
	ft_lstadd_back(&(shell->parse), ft_lstnew((*parse))), NULL);
}

void	parse_else_if(t_shell *shell, t_parse **parse, t_list *new, int *j)
{
	char	*str;

	str = new->content;
	get_text(&(*parse), str, *j, 2);
	*j += 1;
	if (!new->next)
	{
		if (shell->parse->content == NULL)
			shell->parse->content = (*parse);
		else
			ft_lstadd_back(&(shell->parse), ft_lstnew((*parse)));
	}
}

void	parse_else(t_shell *shell, t_parse *parse, int *i, char *str)
{
	if (shell->parse->content == NULL)
		shell->parse->content = parse;
	else
		ft_lstadd_back(&(shell->parse), ft_lstnew(parse));
	if (str[0] == '|')
		*i = 0;
}

t_parse	*get_parse(t_parse *parse, t_list *new, t_parse_params arg)
{
	parse = parse_(&arg.j, new, &arg.i);
	if (ft_lstsize(new) == 1)
		parse->text = (free(parse->text), NULL);
	return (parse);
}

void	welcome_to_parse(t_shell *shell, t_list	*node, t_parse_params arg)
{
	t_list	*new;
	t_parse	*parse;
	char	*str;

	new = (parse_init(shell), node);
	memset(&parse, 0, sizeof(parse));
	parse = get_parse(parse, new, arg);
	while (new)
	{
		str = new->content;
		if (arg.i++ == 0 && !(str[0] == '<' && str[1] == '<'))
			parse_if(shell, new, &parse);
		else if ((!ft_strcmp(str, "")) || (str[0] != '|' && (str[0] != '>'
					&& str[1] != '>') && str[0] != '>'
				&& (str[0] != '<' && str[1] != '<') && str[0] != '<'))
			arg.flag = (parse_else_if(shell, &parse, new, &arg.j), 1);
		else
		{
			if (tokenize_type(&parse, str), arg.flag == 0)
				parse->text = (free(parse->text), NULL);
			parse = (parse_else(shell, parse, &arg.i, str), \
				parse_(&arg.j, new, &arg.i));
		}
		new = new->next;
	}
}
