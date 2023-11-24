/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:31:03 by aaybaz            #+#    #+#             */
/*   Updated: 2023/11/23 15:49:24 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Bu fonksiyon, verilen veri listesinin içeriğini günceller.
 * İşlem sırasında geçici değişkenler kullanılır ve bellek yönetimi yapılır.
 *
 * @param data Veri listesi
 * @param tmp Geçici değişken 1
 * @param tmp2 Geçici değişken 2
 */
void replace_data(t_list **data, char *tmp2)
{
	char *tmp3;

	tmp3 = ft_strdup((*data)->content);
	free((*data)->content);
	(*data)->content = quote_control(tmp3);
	free_tmp_tmp2(tmp2, tmp3);
	(*data) = (*data)->next;
}

int	is_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (cmd[i] == '\0')
		return (0);
	return (1);
}

int	print_error(void)
{
	printf("%s\n", "minishell: syntax error near unexpected token");
	return (0);
}
