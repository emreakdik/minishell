#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static void	remove_quotes_in_str(char *str)
{
	int		i;
	int		j;
	int		in_quotes;
	char	quote_char;

	i = 0;
	j = 0;
	in_quotes = 0;
	quote_char = '\0';
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && (!in_quotes
				|| quote_char == str[i]))
		{
			in_quotes = !in_quotes;
			if (in_quotes)
				quote_char = str[i];
			else
				quote_char = '\0';
		}
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

static void	remove_quotes_in_parse(t_parse *parse)
{
	char	**text_ptr;

	if (parse != NULL)
	{
		if (parse->cmd != NULL)
			remove_quotes_in_str(parse->cmd);
		if (parse->text != NULL)
		{
			text_ptr = parse->text;
			while (*text_ptr != NULL)
			{
				remove_quotes_in_str(*text_ptr);
				text_ptr++;
			}
		}
		remove_quotes_in_parse(parse->next);
	}
}

void	mini_parse(t_list *lex, t_shell *m_shell, int a[3], char *str)
{
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
			remove_quotes_in_parse(parse);
			parse = parse->next;
		}
		else if (ft_strcmp(str, ""))
			parse_text_m(parse, str, &a[1], &a[2]);
		remove_quotes_in_parse(parse);
		lex = lex->next;
	}
	if (a[2] == 0)
		flag_(parse);
}

int	ft_parser(t_shell *m_shell)
{
	int		a[3];
	char	*content;

	content = NULL;
	a[0] = 0;
	a[1] = 0;
	a[2] = 0;
	mini_parse(m_shell->lex_list->lex, m_shell, a, content);
	free_node(m_shell->lex_list->lex);
	return (create_files_m(m_shell));
}
