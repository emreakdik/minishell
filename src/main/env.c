/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaniber <akaniber@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:29:16 by aaybaz            #+#    #+#             */
/*   Updated: 2023/10/15 13:30:06 by akaniber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	env_get(char **env, t_shell **shell)
{
	t_env	*a;
	char	**str;

	free((*shell)->env);
	(*shell)->env = NULL;
	while (*env)
	{
		a = malloc(sizeof(t_env));
		str = ft_split(*env, '=');
		a->key = ft_strdup(str[0]);
		a->value = ft_strdup(str[1]);
		ft_lstadd_back(&(*shell)->env, ft_lstnew(a));
		free_str(str);
		env++;
	}
}
