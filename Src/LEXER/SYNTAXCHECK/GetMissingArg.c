/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetMissingArg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakdik <yakdik@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:34:31 by yakdik            #+#    #+#             */
/*   Updated: 2023/11/16 14:34:31 by yakdik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/**
 * get_missing_arg fonksiyonu, kullanıcıdan eksik argümanı okur ve bir karakter dizisi olarak döndürür.
 * 
 * @return Eksik argüman karakter dizisi.
 */

char	*get_missing_arg(void)
{
	char	*ptr;
	int		fd[2];
	char	c[1];

	pipe(fd);
	if (!read_missing_arg(fd))
		return (NULL);
	ptr = NULL;
	while (read(fd[0], c, 1)) // read_missing_arg fonksiyonu ile okunup yazilanlar parent process tarafindan okundu
		str_addchar(&ptr, *c);
	close(fd[0]);
	return (ptr);
}

/**
 * read_missing_arg fonksiyonu, kullanıcıdan eksik argümanı okur ve bir karakter dizisi olarak boru hattına yazar.
 * 
 * okuma islemi sinyal ile iptal edilebilecegi icin child process acilarak okuma islemi gerceklestirilir. 
 * 
 * @param fd Boru hattı dosya tanımlayıcıları.
 * @return Eksik argüman başarıyla okunursa 1, aksi takdirde 0.
 */

int	read_missing_arg(int *fd)
{
	int		pid;
	int		return_value;

	pid = fork(); // child process olusturuldu
	g_core.is_read_arg = 1;
	if (!pid)
		read_missing_arg_value(fd); // child process buraya girdi
	close(fd[1]);
	waitpid(pid, &return_value, 0); // child process beklendi ve donus degeri return_value degiskeninde tutuldu
	g_core.is_read_arg = 0;
	return_value = WEXITSTATUS(return_value);
	if (return_value == SIGNAL_C)
	{
		close(fd[0]);
		update_history(g_core.cmd);
		free_for_loop();
		return (0);
	}
	return (1);
}

/**
 * read_missing_arg_value fonksiyonu, kullanıcıdan eksik argümanı okur ve boru hattına yazar.
 * 
 * @param fd Boru hattı dosya tanımlayıcıları.
 */

void	read_missing_arg_value(int *fd)
{
	char	*ptr;

	close(fd[0]);
	while (1)
	{
		ptr = readline("> "); // girdi prompt'u
		if (!control_valid_arg(ptr)) // gecerli bir girdi gerekiyor yoksa tekrar yeni satirda girdi prompt'u veriliyor
			continue ;
		write(fd[1], ptr, ft_strlen(ptr)); // girdi parent process okuyabilsin diye pipe'in bir ucuna yaziliyor
		close(fd[1]);
		free(ptr);
		free_for_loop();
		free_core();
		exit(EXIT_SUCCESS);
	}
}

/**
 * control_valid_arg fonksiyonu, kullanıcının girdiği argümanın geçerli olup olmadığını kontrol eder.
 * 
 * @param ptr Kullanıcının girdiği argüman.
 * @return Argüman geçerliyse 1, aksi takdirde 0.
 */

int	control_valid_arg(char *ptr)
{
	char	*str;

	if (!ptr)
		return (0);
	str = ptr;
	trim_spaces(&str);
	if (!*str)
	{
		free(ptr);
		return (0);
	}
	return (1);
}
