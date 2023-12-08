/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:29:16 by aaybaz            #+#    #+#             */
/*   Updated: 2023/12/08 19:01:56 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void get_title_from_env(t_shell **shell)
{
	char *user;
	char *pwd;
	char *title;
	char *temp;

	user = get_env((*shell)->env, "USER");
	pwd = get_env((*shell)->env, "PWD");
	title = ft_strjoin("\033[1;36m", user);
	free(user);
	temp = ft_strjoin(title, "@");
	free(title);
	title = temp;
	temp = ft_strjoin(title, pwd);
	free(title);
	title = temp;
	temp = ft_strjoin(title, "$ \033[0m");
	free(title);
	(*shell)->title = temp;
	free(pwd);
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void env_get(char **env, t_shell **shell)
{
	t_env *a;
	char **str;

	free((*shell)->env);
	(*shell)->env = NULL;
	while (*env)
	{
		a = malloc(sizeof(t_env));
		str = ft_split(*env, '=');
		if (str && str[0] && str[1])
		{
			a->key = ft_strdup(str[0]);
			a->value = ft_strdup(str[1]);
			ft_lstadd_back(&(*shell)->env, ft_lstnew(a));
		}
		free_str(str);
		env++;
	}
}
