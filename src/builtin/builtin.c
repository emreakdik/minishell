

#include "minishell.h"
#include <stdlib.h>

void	execute_builtin_command(t_parse *parse, t_shell *m_shell)
{
	t_parse	*new_parse;

	new_parse = parse;
	if ((ft_strcmp(new_parse->cmd, "echo") == 0) || (ft_strcmp(new_parse->cmd,
				"ECHO") == 0))
		exec_echo(new_parse, m_shell);
	if (ft_strcmp(new_parse->cmd, "cd") == 0)
		exec_cd(new_parse, m_shell);
	if ((ft_strcmp(new_parse->cmd, "pwd") == 0) || (ft_strcmp(new_parse->cmd,
				"PWD") == 0))
		exec_pwd(new_parse, m_shell);
	if (ft_strcmp(new_parse->cmd, "export") == 0)
		exec_export(new_parse, m_shell);
	if (ft_strcmp(new_parse->cmd, "unset") == 0)
		exec_unset(new_parse, m_shell, 0, 0);
	if (((ft_strcmp(new_parse->cmd, "env") == 0) || (ft_strcmp(new_parse->cmd,
					"ENV") == 0)))
		exec_env(m_shell);
}

int	is_builtin(t_parse *data)
{
	if ((ft_strcmp(data->cmd, "echo") == 0) || (ft_strcmp(data->cmd,
				"ECHO") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "pwd") == 0) || (ft_strcmp(data->cmd,
				"PWD") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "env") == 0) || (ft_strcmp(data->cmd,
				"ENV") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "cd") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "export") == 0))
		return (1);
	if ((ft_strcmp(data->cmd, "unset") == 0))
		return (1);
	return (0);
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
	int	i;

	if (text[0] == '=' || ft_isdigit(text[0]))
		return (0);
	i = 0;
	while (text[i] && text[i] != '=' && (ft_isalnum(text[i]) || text[i] == '_'))
		i++;
	if (text[i] == '=' || !text[i])
		return (1);
	return (0);
}

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
