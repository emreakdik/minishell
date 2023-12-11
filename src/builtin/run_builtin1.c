/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:17:26 by ealbayra          #+#    #+#             */
/*   Updated: 2023/12/03 16:24:20 by yakdik           ###   ########.fr       */
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
	t_env		*new;
	int			i;

	i = 0;
	str = m_shell->parse;
	new = (t_env *)data;
	write(str->outfile, "declare -x ", 11);
	while (new->key[i])
		write(str->outfile, &new->key[i++], 1);
	write(str->outfile, "=", 1);
	i = 0;
	while (new->value[i])
		write(str->outfile, &new->value[i++], 1);
	write(str->outfile, "\n", 1);
}

void	exec_export(t_parse *data, t_shell *m_shell)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	key = NULL;
	value = NULL;
	if (data->text == NULL)
		ft_newlstiter(m_shell->env, declare_export, m_shell);
	else if (ft_strchr(data->text[0], '='))
		return (write(2, "minishell: export: `", 20) + write(2, data->text[0],
				ft_strlen(data->text[0])) + write(2,
				"': not a valid identifier\n", 26));
	else
	{
		while (data->text[i])
		{
			key = ft_substr(data->text[i], 0,
					ft_strchrindex(data->text[i], '='));
			value = ft_substr(data->text[i],
					ft_strchrindex(data->text[i], '=') + 1,
					(ft_strlen(data->cmd) - 1));
			edit_env(m_shell->env, key, value, m_shell);
			i++;
		}
	}
	m_shell->exec_status = 0;
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
