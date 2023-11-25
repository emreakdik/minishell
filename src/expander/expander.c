#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int ft_ultimatestrcmp(char *key, char *tmp, int i)
{
	int j;

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

char *get_env(t_list *env, char *key)
{
	t_env *tmp;
	char *ret;

	ret = NULL;
	while (env)
	{
		tmp = env->content;
		if (ft_ultimatestrcmp(tmp->key, key, 0))
		{
			ret = ft_strjoin(tmp->value, key + ft_ultimatestrcmp(tmp->key, key, 0));
			return (ret);
		}
		env = env->next;
	}
	return (ret);
}

static void expander_dollar(t_shell *shell, t_list *lex)
{
	char *temp;
	char *new_value;
	char *before;
	char *after;

	temp = ft_strchr(lex->content, '$'); // freelenemez
	before = ft_substr(lex->content, 0, temp - (char *)lex->content);
	if (temp[1] == '?')
	{
		after = ft_strdup(temp + 2);
		free(lex->content);
		new_value = ft_itoa(shell->exec_status);
		lex->content = ft_strjoin(before, ft_strjoin(new_value, after));
		free(new_value);
		free(after);
		free(before);
	}
	else
	{
		before = ft_strchr(lex->content, '$') - 1; // freelenemez
		if (*before == ' ' || *before == '\0')
		{
			if (ft_isdigit(temp[1]))
			{
				new_value = ft_strdup(temp + 2); // freelenemez
				free(lex->content);
				lex->content = new_value;
			}
			else if (get_env(shell->env, temp + 1))
			{
				new_value = ft_strdup((char *)get_env(shell->env, temp + 1)); // freelenemez
				free(lex->content);
				lex->content = new_value;
			}
		}
	}
}

static void expander_tilde(t_shell *shell, t_list *lex)
{
	char *tmp;

	if (((char *)lex->content)[0] == '~' && ((char *)lex->content)[1] == '/')
	{
		tmp = ft_strdup(lex->content);
		free(lex->content);
		lex->content = ft_strjoin(get_env(shell->env, "HOME"), tmp + 1);
		free(tmp); // Freeing tmp here to fix the memory leak
	}
	else if (((char *)lex->content)[0] == '~' && ((char *)lex->content)[1] == '\0')
	{
		free(lex->content);
		lex->content = ft_strdup(get_env(shell->env, "HOME"));
	}
}

void	expander(t_shell *shell)
{
	t_list	*lex;

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
