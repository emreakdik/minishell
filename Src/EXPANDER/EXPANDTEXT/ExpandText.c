/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpandText.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:45:21 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 16:45:21 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/**
 * Verilen bir karakter dizisindeki çevre değişkenlerini genişletir.
 * Eğer çevre değişkeni varsa, değeri ile değiştirir.
 * 
 * @param dst genişletilmiş karakter dizisinin adresi
 * @param ptr genişletilecek karakter dizisi
 */

void	expand_envs(char **dst, char *ptr)
{
	t_env	*copy_envs;

	copy_envs = g_core.env_table;
	while (copy_envs)
	{
		if (str_compare(ptr, copy_envs->env_name))
		{
			own_strjoin(dst, copy_envs->content);
			break ;
		}
		copy_envs = copy_envs->next;
	}
}

/**
 * Verilen bir karakter dizisindeki değişkenleri genişletir.
 * Eğer değişken varsa, değeri ile değiştirir.
 * 
 * @param dst genişletilmiş karakter dizisinin adresi
 * @param src genişletilecek karakter dizisi
 */
void	expand_order(char **dst, char **src)
{
	if (**src == *DOLLAR)
		expand_dollar(dst, src);
	else
		expand_envs(dst, "HOME");
}
