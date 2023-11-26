#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

// remove qutoes from string if its there on start or on end
void	remove_quotes(t_list *lex)
{
	char	*temp;

	if (((char *)lex->content)[0] == '\"' || ((char *)lex->content)[0] == '\'')
	{
		temp = ft_substr(lex->content, 1, ft_strlen(lex->content) - 2);
		free(lex->content);
		lex->content = temp;
	}
}

int	ft_ultimatestrcmp(char *key, char *tmp, int i)
{
	int	j;

	j = 0;
	if (tmp[i] != key[0])
		return (0);
	while (tmp[i])
	{
		j = 0;
		while (tmp[i] == key[j])
		{
			i++;
			j++;
			if (!key[j])
			{
				if (!ft_isalnum(tmp[i]))
					return (i);
				return (0);
			}
		}
		i++;
	}
	return (0);
}

char	*get_env(t_list *env, char *key)
{
	t_env	*tmp;
	char	*ret;

	ret = NULL;
	while (env)
	{
		tmp = env->content;
		if (ft_ultimatestrcmp(tmp->key, key, 0))
		{
			ret = ft_strjoin(tmp->value, key + ft_ultimatestrcmp(tmp->key, key,
						0));
			return (ret);
		}
		env = env->next;
	}
	return (ret);
}

static void	expander_dollar(t_shell *shell, t_list *lex)
{
	char	*temp;
	char	*new_value;
	char	*before;
	char	*after;
	char	*back;

	temp = ft_strchr(lex->content, '$');
	if (temp && temp[1] == '?')
	{
		before = ft_substr(lex->content, 0, temp - (char *)lex->content);
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
	temp = ft_strchr(lex->content, '$');
	if (temp)
	{
		before = ft_substr(lex->content, 0, temp - (char *)lex->content);
		if (before && (before == lex->content || !ft_isalnum(*(before - 1))))
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
				if (new_value)
				{
					free(lex->content);
					lex->content = ft_strjoin(before, new_value);
					free(new_value);
				}
			}
		}
		free(before);
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
			if (ft_strchr(lex->content, '~')
				&& ((char *)lex->content)[0] != '\"'
				&& ((char *)lex->content)[0] != '\'')
				expander_tilde(shell, lex);
			if (ft_strchr(lex->content, '$')
				&& ((char *)lex->content)[0] != '\'')
				expander_dollar(shell, lex);
			remove_quotes(lex);
			lex = lex->next;
		}
	}
	else
		remove_quotes(lex);
}
