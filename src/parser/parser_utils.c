/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:30:44 by aaybaz            #+#    #+#             */
/*   Updated: 2023/12/05 14:49:33 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

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

void	parse_text_m(t_parse *parse, char *str, int *j, int *flag)
{
	parse->text[*j] = ft_strdup(str);
	*j += 1;
	parse->text[*j] = NULL;
	*flag = 1;
}

/**
 * Bu fonksiyon,
	t_parse yapısı içindeki text alanını serbest bırakır ve NULL olarak ayarlar.
 *
 * @param parse t_parse yapısı
 */
void	flag_(t_parse *parse)
{
	free_text(parse->text);
	parse->text = NULL;
}

/**
 * Bu fonksiyon, verilen bir karakter dizisini analiz ederek,
	belirli bir tür ataması yapar.
 *
 * @param parse - Analiz edilen verinin türünü tutan parse yapısı
 * @param str - Analiz edilecek karakter dizisi
 */
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
