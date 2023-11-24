/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_or_multi_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaybaz <aaybaz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:53:50 by aaybaz            #+#    #+#             */
/*   Updated: 2023/07/19 19:55:00 by aaybaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	single_or_multi_command(t_shell *shell)
{
	t_list	*tmp;
	t_parse	*data;

	tmp = shell->parse;
	data = shell->parse->content;
	while (tmp)
	{
		data = tmp->content;
		if (data->type == 2)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
