/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:37:46 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/23 16:37:48 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>

static void	tilde_build(char *tmp, char *str, t_list *data)
{
	int		y;
	int		i;
	int		j;
	char	*key;

	j = 0;
	y = 0;
	i = 0;
	key = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (ft_strchr(tmp, '/'))
	{
		tmp = ft_strchr(tmp, '/');
		y++;
	}
	while (str[i])
	{
		key[j] = str[i++];
		j++;
	}
	key[j] = '\0';
	if (y == 1)
		ft_tilde_build1(data, key, tmp);
	else
		ft_tilde_build2(data, str);
	free(key);
}

static int	check_and_expand(t_shell *shell, t_list *data, char *tmp, int i)
{
	t_env	*y;
	char	*content_backup;
	t_list	*shell_data;

	shell_data = shell->env;
	content_backup = ft_strdup((char *)data->content);
	while (shell_data)
	{
		y = shell_data->content;
		if (tmp[i] == '~' && ft_strcmp(y->key, "HOME") == 0)
			tilde_build(tmp, y->value, data);
		if (tmp[i] == '$' && tmp[i + 1] == '?')
			ft_exit_status(shell, tmp, data);
		else if (tmp[i] == '$' && ft_isdigit(tmp[i + 1]) && tmp[i + 2])
			get_after_num(tmp, data, i + 2);
		else if (tmp[i] == '$')
			does_dollar_make_sense(tmp, data, shell_data, i + 1);
		shell_data = shell_data->next;
	}
	if (!ft_strcmp(content_backup, (char *)data->content))
		erase_after(tmp, data, i + 1);
	free(content_backup);
	return (0);
}

/**
 * _get_env_to_lexlist fonksiyonu, shell ve tmp parametrelerini alır ve
 * data parametresiyle işaretlenen liste öğesinin içeriğini tmp'ye kopyalar.
 * Eğer tmp'nin i. indeksi '~' karakterine eşitse ve tmp'nin ilk karakteri '\'' veya '\"'
 * karakteri değilse ve tmp'nin i+1. indeksi '/' karakterine eşit veya boş ise,
 * check_env fonksiyonunu çağırır.
 *
 * @param shell Shell yapısı
 * @param tmp Geçici karakter dizisi
 * @param i İndeks değeri
 * @param data Liste öğesi
 */
static void tilde_to_expand(t_shell *shell, char **tmp, int i, t_list **data)
{
	if (*data && (*tmp)[i] == '~' && ((*tmp)[0] != '\'' || (*tmp)[0] != '\"')
		&& ((*tmp)[i + 1] == '/' || !(*tmp)[i + 1]))
	{
		if (i >= 1 && !ft_isprint((*tmp)[i - 1]))
			check_and_expand(shell, *data, *tmp, i);
		else
			check_and_expand(shell, *data, *tmp, i);
	}
}

/**
 * Bu fonksiyon, shell ve lex_list parametrelerini alarak çeviri listesine
 * ortam değişkenlerini ekler.
 *
 * @param shell Shell yapısı
 * @param lex_list Çeviri listesi
 */
static void expand_lexlist(t_shell *shell, t_lexer **lex_list)
{
	t_list *data;
	char *tmp;
	int i;

	data = (*lex_list)->lex;
	while (data)
	{
		i = 0;
		tmp = ft_strdup(data->content);
		while (tmp[i])
		{
			tilde_to_expand(shell, &tmp, i, &data);
			if (tmp[i] == '$' && tmp[0] != '\'')
			{
				check_and_expand(shell, data, tmp, i);
				if (data && !ft_strcmp(data->content, ""))
					break;
			}
			i++;
		}
		replace_data(&data, tmp);
	}
}

void	expander(t_shell *shell)
{
	if (ft_strcmp(shell->cmd, ""))
		expand_lexlist(shell, &(shell->lex_list));
}
