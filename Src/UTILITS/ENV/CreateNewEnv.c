/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateNewEnv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:32:46 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:32:46 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	mainde 3.parametre olarak aldığımız env değişkenini alır
	ve bağlı liste yapısına doldurur.
*/
void	fill_envs(char **env)
{
	while (env && *env)
		add_newenv(&g_core.env_table, *(env++));
}


/**
 * Yeni bir t_env yapısı oluşturur ve verilen env değişkenini bu yapıya ekler.
 * 
 * @param env_table env değişkeninin ekleneceği t_env yapısı.
 * @param env t_env yapısına eklenecek env değişkeni.
 * @return t_env yapısının son elemanı.
 */
t_env	*add_newenv(t_env **env_table, char *env)
{
	// Eğer env_table boş ise, yeni bir t_env yapısı oluşturulur ve last_node bu yapıya atanır.
	// Aksi takdirde, last_node env_table'ın son elemanına atanır.
	t_env	*last_node;
	char	*content;

	if (!*env_table)
	{
		*env_table = (t_env *)malloc(sizeof(t_env));
		last_node = *env_table;
	}
	else
	{
		last_node = *env_table;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = (t_env *)malloc(sizeof(t_env));
		last_node = last_node->next;
	}
	// last_node'un env_name özelliği, env değişkeninin ismini yani "=" operatorunden oncesini içerir.
	last_node->env_name = get_env_name(env);
	// content değişkeni, env değişkeninin env_name'den yani "=" operatorunden sonraki kısmını içerir.
	content = env + ft_strlen(last_node->env_name);
	if (*content == '=' && *(content + 1))
		last_node->content = ft_strdup(content + 1);
	else
		last_node->content = NULL;
	last_node->next = NULL;
	return (last_node);
}
