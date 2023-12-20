

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	expand_dollar_variable(t_shell *shell, t_list *lex, char **temp,
		char *before)
{
	char	*new_value;

	if (ft_isdigit((*temp)[1]))
	{
		new_value = ft_strdup(*temp + 2);
		free(lex->content);
		lex->content = ft_strjoin(before, new_value);
		free(new_value);
		*temp = ft_strchr(lex->content + ft_strlen(before), '$');
	}
	else if (!ft_isdigit((*temp)[1]))
	{
		new_value = get_env(shell->env, *temp + 1);
		free(lex->content);
		lex->content = ft_strjoin(before, new_value);
		if ((char *)lex->content == NULL)
			lex->content = ft_strdup(before);
		free(new_value);
		*temp = ft_strchr(lex->content + ft_strlen(before), '$');
	}
}

void	expand_question_mark(t_shell *shell, t_list *lex, char **temp,
		char *before)
{
	char	*after;
	char	*back;
	char	*new_value;

	after = ft_strdup(*temp + 2);
	free(lex->content);
	new_value = ft_itoa(shell->exec_status);
	back = ft_strjoin(new_value, after);
	free(new_value);
	free(after);
	lex->content = ft_strjoin(before, back);
	free(back);
	*temp = ft_strchr(lex->content + ft_strlen(before), '$');
}

static void	expander_tilde(t_shell *shell, t_list *lex)
{
	char	*tmp;
	char	*home;

	home = get_env(shell->env, "HOME");
	if (((char *)lex->content)[0] == '~' && ((char *)lex->content)[1] == '/')
	{
		tmp = ft_strdup(lex->content);
		free(lex->content);
		lex->content = ft_strjoin(home, tmp + 1);
		free(tmp);
		free(home);
	}
	else if (((char *)lex->content)[0] == '~'
		&& ((char *)lex->content)[1] == '\0')
	{
		free(lex->content);
		lex->content = home;
	}
	else
		free(home);
}

void	handle_dollar(t_shell *shell, t_list *lex, char **temp, char *before)
{
	if ((*temp)[1] == '?')
		expand_question_mark(shell, lex, temp, before);
	else if ((*temp)[1] != '$' && ft_strcmp((*temp), "$") != 0)
		expand_dollar_variable(shell, lex, temp, before);
	else
		*temp = ft_strchr(*temp + 1, '$');
}

void	expander(t_shell *shell)
{
	char	*temp;
	t_list	*lex;
	char	*before;

	lex = shell->lex_list->lex;
	while (lex)
	{
		if (((char *)lex->content)[0] == '~')
			expander_tilde(shell, lex);
		temp = ft_strchr(lex->content, '$');
		while (temp)
		{
			before = ft_substr(lex->content, 0, temp - (char *)lex->content);
			if (check_quote(before, temp))
				handle_dollar(shell, lex, &temp, before);
			else
				temp = ft_strchr(temp + 1, '$');
			free(before);
		}
		lex = lex->next;
	}
}
