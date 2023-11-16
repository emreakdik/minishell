/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetEnvName.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:49:26 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 13:49:26 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/**
 * Verilen string icerisindeki environment variable'in ismini ayirir.
 * 
 * @param content Environment variable'in tamamini iceren string.
 * @return Environment variable'in ismini iceren string.
 */
char	*get_env_name(char *content)
{
	// Verilen string icerisindeki environment variable'in ismini ayirir.
	// Ornegin, "PATH=/usr/bin" stringi icin "PATH" stringini dondurur.
	
	int		env_name_len;
	char	*name;
	char	*temp_name;

	env_name_len = get_env_name_count(content);
	if (!env_name_len)
		return (NULL);
	name = (char *)malloc(sizeof(char) * (env_name_len + 1));
	temp_name = name;
	while (content && *content && *content != '=')
		*(temp_name++) = *(content++);
	*temp_name = 0;
	return (name);
}

/**
 * Verilen string icerisindeki environment variable'in isminin uzunlugunu hesaplar.
 * 
 * @param content Environment variable'in tamamini iceren string.
 * @return Environment variable'in isminin uzunlugu.
 */
int	get_env_name_count(char *env_arg)
{
	int	count;

	count = 0;
	while (env_arg && *env_arg && *(env_arg++) != '=')
		count++;
	return (count);
}
