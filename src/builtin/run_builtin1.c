/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaybaz < aaybaz@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:24:00 by aaybaz            #+#    #+#             */
/*   Updated: 2023/10/25 12:30:35 by aaybaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	edit_env(t_shell *shell, t_list *node, char *key, char *value)
{
	t_env	*new_env;
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
	if (node == NULL)
	{
		new_env = malloc(sizeof(t_env));
		new_env->key = key;
		new_env->value = value;
		ft_lstadd_back(&(shell->env), ft_lstnew(new_env));
	}
}

void	declare_export(t_shell *shell, void *data)
{
	t_parse	*str;
	t_env	*new;
	int		i;

	i = 0;
	str = shell->parse->content;
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

void	exec_export(t_shell *shell, t_parse *data)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	key = NULL;
	value = NULL;
	if (data->text == NULL)
		ft_newlstiter(shell->env, declare_export, shell);
	else if (!ft_strchr(data->text[0], '='))
		return ;
	else
	{
		while (data->text[i])
		{
			key = ft_substr(data->text[i], 0,
					ft_strchrindex(data->text[i], '='));
			value = ft_substr(data->text[i],
					ft_strchrindex(data->text[i], '=') + 1,
					(ft_strlen(*data->text) - 1));
			edit_env(shell, shell->env, key, value);
			i++;
		}
	}
	shell->exec_status = 0;
}

void	unset_edit(t_shell *shell, t_list **node, t_list **prev_node)
{
	t_env	*tmp;

	tmp = (*node)->content;
	if (prev_node == NULL)
		shell->env = (*node)->next;
	else
		(*prev_node)->next = (*node)->next;
	free(tmp->key);
	free(tmp->value);
	free((*node)->content);
	free(*node);
}

void	exec_unset(t_shell *shell, t_parse *data)
{
	int		i;
	char	*key;
	t_list	*prev_node;
	t_list	*node;

	i = 0;
	if (data->text == NULL)
		return ;
	while (data->text[i])
	{
		key = data->text[i];
		prev_node = NULL;
		node = shell->env;
		while (node != NULL)
		{
			if (ft_strcmp(((t_env *)node->content)->key, key) == 0)
				unset_edit(shell, &node, &prev_node);
			prev_node = node;
			node = node->next;
		}
		i++;
	}
}
