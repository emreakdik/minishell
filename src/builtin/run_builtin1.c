/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:17:26 by ealbayra          #+#    #+#             */
/*   Updated: 2023/12/12 16:06:47 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	edit_env(t_list *node, char *key, char *value, t_shell *m_shell)
{
	t_env	*env;

	while (node != NULL)
	{
		env = (t_env *)node->content;
		if (ft_strcmp(env->key, key) == 0)
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(value);
			if (value)
				free(value);
			free(key);
			return ;
		}
		node = node->next;
	}
	edit_env_(node, key, value, m_shell);
}

void	declare_export(void *data, t_shell *m_shell)
{
	t_parse	*str;
	t_env	*new;
	int		i;

	i = 0;
	str = m_shell->parse;
	new = (t_env *)data;
	write(str->outfile, "declare -x ", 11);
	while (new->key[i])
		write(str->outfile, &new->key[i++], 1);
	if (new->value && new->key[0] > 31)
		write(str->outfile, "=", 1);
	i = 0;
	while (new->value && new->value[i])
		write(str->outfile, &new->value[i++], 1);
	write(str->outfile, "\n", 1);
}

int	ft_strchrindex_0(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	export_key_control(char *text)
{
	int		i;

	if (text[0] == '=' || ft_isdigit(text[0]))
		return (0);
	i = 0;
	while (text[i] && text[i] != '=' && (ft_isalnum(text[i]) || text[i] == '_'))
		i++;
	if (text[i] == '=' || !text[i])
		return (1);
	return (0);
}

int	exec_export(t_parse *data, t_shell *m_shell)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	key = NULL;
	value = NULL;
	if (data->text == NULL)
	{
		ft_newlstiter(m_shell->env, declare_export, m_shell);
	}
	else
	{
		while (data->text[i])
		{
			if (!export_key_control(data->text[i]))
				return (write(2, "minishell: export: `", 20) + write(2, data->text[i],
						ft_strlen(data->text[i])) + write(2,
						"': not a valid identifier\n", 26));
			if (ft_strchrindex_0(data->text[i], '=') != -1)
			{
				key = ft_substr(data->text[i], 0, ft_strchrindex(data->text[i],
							'='));
				value = ft_substr(data->text[i], ft_strchrindex(data->text[i], '=')
						+ 1, (ft_strlen(data->cmd) - 1));
			}
			else
			{
				key = ft_substr(data->text[i], 0, ft_strlen(data->text[i]));
			}
			edit_env(m_shell->env, key, value, m_shell);
			i++;
		}
	}
	m_shell->exec_status = 0;
	return (0);
}

int	unset_edit(t_list **node, t_list **prev_node, t_shell *m_shell)
{
	t_env	*tmp;

	tmp = (*node)->content;
	if (*prev_node == NULL)
		m_shell->env = (*node)->next;
	else
		(*prev_node)->next = (*node)->next;
	free(tmp->key);
	free(tmp->value);
	free((*node)->content);
	free(*node);
	return (1);
}

void	exec_unset(t_parse *data, t_shell *m_shell, int i, int x)
{
	t_list	*prev_node;
	t_list	*node;
	t_env	*env;

	env = NULL;
	if (data->text == NULL)
		return ;
	while (data->text[i])
	{
		prev_node = NULL;
		node = m_shell->env;
		while (node != NULL)
		{
			env = (t_env *)node->content;
			if (ft_strcmp(env->key, data->text[i]) == 0)
				x = unset_edit(&node, &prev_node, m_shell);
			if (x)
				break ;
			prev_node = node;
			node = node->next;
		}
		i++;
	}
}
