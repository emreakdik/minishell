/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Title.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:53:07 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 13:53:07 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/**
 * Bu fonksiyon, minishell uygulamasında kullanılan başlık (title) özelliğini değiştirir.
 * Başlık, kullanıcının bulunduğu dizin ve kullanıcı adı gibi bilgileri içerir.
 * 
 * @param void
 * @return void
 */
void change_title(void)
{
	char cwd[256];

	if (g_core.title.full_title)
		free(g_core.title.full_title);
	g_core.title.full_title = NULL;
	own_strjoin(&g_core.title.full_title, g_core.title.head);
	own_strjoin(&g_core.title.full_title, (char *)getcwd(cwd, 256));
	own_strjoin(&g_core.title.full_title, "$ ");
}

/**
 * Bu fonksiyon, minishell uygulamasında kullanılan başlık (title) özelliğini ayarlar.
 * Başlık, kullanıcının bulunduğu dizin ve kullanıcı adı gibi bilgileri içerir.
 * 
 * Ornegin: emre@emres-MacBook-Air Desktop %
 * 
 * @param void
 * @return void
 */
void set_title(void)
{
	char cwd[256];

	g_core.title.head = NULL;
	g_core.title.full_title = NULL;
	expand_envs(&g_core.title.head, "LOGNAME");
	str_addchar(&g_core.title.head, '@');
	expand_envs(&g_core.title.head, "NAME");
	str_addchar(&g_core.title.head, ':');
	own_strjoin(&g_core.title.full_title, g_core.title.head);
	own_strjoin(&g_core.title.full_title, (char *)getcwd(cwd, 256));
	own_strjoin(&g_core.title.full_title, "$ ");
}
