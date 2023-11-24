#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

static char	*get_env(t_list *env, char *key)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->content;
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		env = env->next;
	}
	return (NULL);
}

static void	expander_dollar(t_shell *shell, t_list *lex)
{
	char	*temp;
	char	*new_value;
	char	*before;
	char	*after;

	temp = ft_strchr(lex->content, '$');
	before = ft_substr(lex->content, 0, temp - (char *)lex->content);
	if (temp[1] == '?')
	{
		after = ft_strdup(temp + 2);
		free(lex->content);
		new_value = ft_itoa(shell->exec_status);
		lex->content = ft_strjoin(before, ft_strjoin(new_value, after));
	}
	else
	{
		before = ft_strchr(lex->content, '$') - 1;
		if (*before == ' ' || *before == '\0')
		{
			if (ft_isdigit(temp[1]))
			{
				new_value = ft_strdup(temp + 2);
				free(lex->content);
				lex->content = new_value;
			}
			else if (get_env(shell->env, temp + 1))
			{
				new_value = ft_strdup((char *)get_env(shell->env, temp + 1));
				free(lex->content);
				lex->content = new_value;
			}
		}
	}
}

static void	expander_tilde(t_shell *shell, t_list *lex)
{
	char	*tmp;

	if (((char *)lex->content)[0] == '~' && ((char *)lex->content)[1] == '/')
	{
		tmp = ft_strdup(lex->content);
		free(lex->content);
		lex->content = ft_strjoin(get_env(shell->env, "HOME"), tmp + 1);
	}
	else if (((char *)lex->content)[0] == '~'
		&& ((char *)lex->content)[1] == '\0')
	{
		free(lex->content);
		lex->content = ft_strdup(get_env(shell->env, "HOME"));
	}
}

void	expander_deneme(t_shell *shell)
{
	t_list *lex;

	lex = shell->lex_list->lex;
	while (lex && ((char *)lex->content)[0] != '\'')
	{
		if (ft_strchr(lex->content, '$'))
			expander_dollar(shell, lex);
		if (ft_strchr(lex->content, '~'))
			expander_tilde(shell, lex);
		lex = lex->next;
	}
}
