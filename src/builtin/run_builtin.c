/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaybaz < aaybaz@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:14:25 by aaybaz            #+#    #+#             */
/*   Updated: 2023/10/25 12:31:11 by aaybaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

void	run_echo(t_parse *data, int *i)
{
	int	x;
	int	j;

	x = *i;
	while (data->text[x])
	{
		j = 0;
		while (data->text[x][j])
			write(data->outfile, &data->text[x][j++], 1);
		if (data->text[x][j] == '\0' && data->text[x + 1] != NULL)
			write(data->outfile, " ", 1);
		x++;
		*i += 1;
	}
}

void	exec_echo(t_shell *shell, t_parse *data)
{
	int	i;

	i = 0;
	if (!data->text)
		write(data->outfile, "\n", 1);
	else
	{
		if (ft_strcmp(data->text[0], "-n") == 0)
		{
			i = 1;
			if (data->text[1])
				run_echo(data, &i);
		}
		else
		{
			run_echo(data, &i);
			if (!data->text[i])
				write(data->outfile, "\n", 1);
		}
	}
	shell->exec_status = 0;
}

void	print_list(t_shell *shell, void *data)
{
	t_parse	*str;
	t_env	*new;
	int		i;

	i = 0;
	str = shell->parse->content;
	new = (t_env *)data;
	while (new->key[i])
		write(str->outfile, &new->key[i++], 1);
	write(str->outfile, "=", 1);
	i = 0;
	while (new->value[i])
		write(str->outfile, &new->value[i++], 1);
	write(str->outfile, "\n", 1);
}

void	exec_env(t_shell *shell)
{
	ft_newlstiter(shell->env, print_list, shell);
	shell->exec_status = 0;
}
