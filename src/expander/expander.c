/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:16:27 by yakdik            #+#    #+#             */
/*   Updated: 2023/12/08 16:13:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	expand_dollar_variable(t_shell *shell, t_list *lex, char *temp)
{
	char	*before;
	char	*new_value;

	before = ft_substr(lex->content, 0, temp - (char *)lex->content);
	if (!is_count_odd(before, '\'') && !is_count_odd(((char *)lex->content)
			+ ft_strlen(before), '\''))
	{
			if (ft_isdigit(temp[1]))
			{
				new_value = ft_strdup(temp + 2);
				free(lex->content);
				lex->content = ft_strjoin(before, new_value);
				free(new_value);
			}
			else
			{
				new_value = get_env(shell->env, temp + 1);
				free(lex->content);
				lex->content = ft_strjoin(before, new_value);
				if ((char *)lex->content == NULL)
					lex->content = ft_strdup(before);
				free(new_value);
			}
		if (ft_strchr(lex->content, '$'))
			handle_dollar(shell, lex);
	}
	free(before);
}

void	expand_question_mark(t_shell *shell, t_list *lex, char *temp)
{
	char	*before;
	char	*after;
	char	*back;
	char	*new_value;

	before = ft_substr(lex->content, 0, temp - (char *)lex->content);
	if (!is_count_odd(before, '\'') && !is_count_odd(((char *)lex->content)
			+ ft_strlen(before), '\''))
	{
		after = ft_strdup(temp + 2);
		free(lex->content);
		new_value = ft_itoa(shell->exec_status);
		back = ft_strjoin(new_value, after);
		free(new_value);
		free(after);
		lex->content = ft_strjoin(before, back);
		free(back);
		free(before);
	}
	if (ft_strchr(lex->content, '$'))
		handle_dollar(shell, lex);
}

void	handle_dollar(t_shell *shell, t_list *lex)
{
	char	*temp;

	if (ft_strcmp(lex->content, "$") == 0 || ft_strcmp(lex->content,
			"\"$\"") == 0)
		return ;
	temp = ft_strchr(lex->content, '$');
	if (temp && temp[1] == '?')
		expand_question_mark(shell, lex, temp);
	else if (ft_strchr(lex->content, '$'))
	{
		temp = ft_strchr(lex->content, '$');
		expand_dollar_variable(shell, lex, temp);
	}
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

void	expander(t_shell *shell)
{
	t_list	*lex;

	lex = shell->lex_list->lex;
	if (((char *)lex->content)[0] != '\'')
	{
		while (lex)
		{
			if (ft_strchr(lex->content, '~'))
				expander_tilde(shell, lex);
			if (ft_strchr(lex->content, '$'))
				handle_dollar(shell, lex);
			remove_quotes(lex);
			lex = lex->next;
		}
	}
	else
		remove_quotes(lex);
}