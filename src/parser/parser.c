/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:24:15 by bakilli           #+#    #+#             */
/*   Updated: 2023/12/03 15:18:04 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

t_parse	*parse_init(size_t len)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (NULL);
	(parse)->next = NULL;
	(parse)->cmd = NULL;
	(parse)->text = ft_calloc(sizeof(char *), len + 1);
	if (!(parse)->text)
		return (NULL);
	(parse)->type = 0;
	(parse)->infile = STDINN;
	(parse)->outfile = STDOUT;
	(parse)->fd = 1;
	(parse)->pid = 0;
	(parse)->control = 0;
	return (parse);
}

void	tokenize_type_m(t_parse **parse, const char *str)
{
	if (str[0] == '|')
		(*parse)->type = PIPE;
	else if (str[0] == '>' && str[1] == '>')
		(*parse)->type = GREATER;
	else if (str[0] == '<' && str[1] == '<')
	{
		(*parse)->type = HEREDOC;
		g_does_have_heredoc = 1;
	}
	else if (str[0] == '>')
		(*parse)->type = GREAT;
	else if (str[0] == '<')
		(*parse)->type = LESS;
}

void	parse_text_m(t_parse *parse, char *str, int *j, int *flag)
{
	parse->text[*j] = ft_strdup(str);
	*j += 1;
	parse->text[*j] = NULL;
	*flag = 1;
}

void	flag_(t_parse *parse)
{
	free_text(parse->text);
	parse->text = NULL;
}

void	mini_parse(t_list *lex, t_shell *m_shell, int a[3])
{
	char		*str;
	t_parse	*parse;

	parse = parse_init((size_t)ft_lstsize(lex));
	m_shell->parse = parse;
	while (lex != NULL)
	{
		str = lex->content;
		if (a[0]++ == 0 && ft_strcmp(str, "<<"))
			parse->cmd = ft_strdup(str);
		else if (str[0] == '|' || str[0] == '>' || str[0] == '<')
		{
			if (tokenize_type_m(&parse, str), str[0] == '|')
				a[0] = 0;
			parse->next = parse_init((size_t)ft_lstsize(lex));
			a[1] = 0;
			parse = parse->next;
		}
		else if (ft_strcmp(str, ""))
			parse_text_m(parse, str, &a[1], &a[2]);
		lex = lex->next;
	}
	if (a[2] == 0)
		flag_(parse);
}
