/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SetMetachars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:54:35 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 13:54:35 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	global degiskende ki metachars degiskenine 2 boyutlu bir dizi olusturur
	ve icerisine teker teker belirlenen metakarakterleri atar.
	metakarakterler sirasiyla ">>", "<<", "<", ">", "|"'dir
*/
void	set_metachars(void)
{
	char	**meta_list;

	meta_list = (char **)malloc(sizeof(char *) * (METACHAR_NUM + 1));
	g_core.metachars = meta_list;
	*(meta_list++) = ft_strdup(DOUBLE_GREAT);
	*(meta_list++) = ft_strdup(DOUBLE_LESS);
	*(meta_list++) = ft_strdup(SINGLE_LESS);
	*(meta_list++) = ft_strdup(SINGLE_GREAT);
	*(meta_list++) = ft_strdup(PIPE);
	*(meta_list++) = NULL;
}
