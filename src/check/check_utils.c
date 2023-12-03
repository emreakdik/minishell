/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:31:03 by aaybaz            #+#    #+#             */
/*   Updated: 2023/11/25 09:48:17 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	free_tmp_tmp2(char *tmp, char *tmp1)
{
	free(tmp);
	free(tmp1);
}

void quote_build(char **tmp, char **data, int *i, int *j)
{
	char a;
	int x;
	int y;

	x = *i;
	y = *j;
	a = (*tmp)[x++]; // Tırnak işaretini al
	*i += 1;
	while ((*tmp)[x] && (*tmp)[x] != a) // Tırnak işaretinin sonuna kadar
	{
		(*data)[y] = (*tmp)[x++];
		*i += 1;
		*j += 1;
		y++;
	}
}

/**
 * Bu fonksiyon, verilen bir karakter dizisindeki tırnak işaretlerini kontrol eder
 * ve tırnak içindeki veriyi yeni bir karakter dizisine kopyalar.
 * 
 * bu fonksiyon tirnak isareti hic yoksa normal kopyalama yapar
 * 
 * @param tmp   Kontrol edilecek karakter dizisi
 * @return      Tırnak işaretleri kontrol edilmiş ve tırnak içindeki verinin kopyalandığı yeni karakter dizisi
 */
char *quote_control(char *tmp)
{
	char *data;
	int i;
	int j;

	i = 0;
	j = 0;
	data = malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'') // Tırnak işareti varsa
			quote_build(&tmp, &data, &i, &j);
		else // Tırnak işareti yoksa
		{
			data[j] = tmp[i]; // Karakter dizisini kopyala
			j++;
		}
		i++;
	}
	data[j] = '\0';
	return (data);
}

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
