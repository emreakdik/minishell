/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:20:50 by ealbayra          #+#    #+#             */
/*   Updated: 2023/12/05 14:40:44 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/**
 * Bu fonksiyon, parse parametresi olarak verilen struct'ın next ve next->text[0] değerlerini kullanarak
 * dosya oluşturma işlemlerini gerçekleştirir. Fonksiyon, parse->type değerine göre farklı işlemler yapar.
 * Eğer parse->type GREATER ise, dosya açılırken O_APPEND flag'i kullanılır. Eğer parse->type GREAT ise,
 * dosya açılırken O_TRUNC flag'i kullanılır. Dosya açma işlemi tamamlandıktan sonra parse->outfile ve
 * parse->fd değerleri güncellenir. Fonksiyonun sonunda kullanılan bellek alanları serbest bırakılır.
 *
 * @param parse Dosya oluşturma işlemlerinin yapılacağı parse struct'ı
 */
void	other_out_filesme(t_parse *parse)
{
	char		str[256];
	char		*pwd;
	char		*pwd1;
	t_parse	*nparse;

	getcwd(str, 256);
	nparse = parse->next;
	pwd = ft_strjoin(str, "/");
	pwd1 = ft_strjoin(pwd, nparse->text[0]);
	open(pwd1, O_CREAT | O_RDWR, 0777);
	free(pwd1);
	pwd1 = ft_strjoin(pwd, nparse->next->text[0]);
	if (nparse->type == GREATER)
		parse->fd = open(pwd1, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (parse->type == GREAT)
		parse->fd = open(pwd1, O_CREAT | O_RDWR | O_TRUNC, 0777);
	parse->outfile = parse->fd;
	if (pwd)
		free(pwd);
	if (pwd1)
		free(pwd1);
}

/**
 * Bu fonksiyon, verilen t_parse yapısı üzerinde işlem yaparak metin oluşturur.
 * 
 * @param m_parse işlem yapılacak t_parse yapısı
 */
void other_text_create_me(t_parse *m_parse)
{
	t_parse *n_parse;
	int i;
	int j;

	n_parse = m_parse->next;
	i = 0;
	while (m_parse->text[i])
		i++;
	while (n_parse->next && n_parse->type != PIPE)
	{
		j = 1;
		while (n_parse->text[j])
		{
			m_parse->text[i] = ft_strdup(n_parse->text[j]);
			i++;
			j++;
		}
		n_parse = n_parse->next;
	}
	m_parse->text[i] = NULL;
	other_out_filesme(m_parse);
}

/**
 * Birleştirilmiş bir dize döndüren ft_strjoin2 fonksiyonu.
 *
 * Bu fonksiyon, verilen iki diziyi birleştirerek yeni bir dize oluşturur.
 * İlk dizeyi ve ikinci diziyi birleştirirken, bellekte yeni bir dize oluşturur ve
 * bu yeni dizeyi döndürür. İlk dizeyi temsil eden s1 ve ikinci dizeyi temsil eden s2
 * parametreleri alır.
 *
 * @param s1 Birinci dize
 * @param s2 İkinci dize
 * @return Birleştirilmiş dize
 */
char	*ft_strjoin2(char *s1, const char *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free(s1);
	return (str);
}

/**
 * Bu fonksiyon, verilen parse yapılarına göre çıkış dosyalarını oluşturur.
 * 
 * @param m_parse   Mevcut parse yapısı
 * @param prev_parse   Önceki parse yapısı
 */
void create_out_files_me(t_parse *m_parse, t_parse *prev_parse)
{
	char str[256];
	char *pwd;
	t_parse *m_next;

	getcwd(str, 256); // mevcut çalışma dizinini al
	m_next = m_parse->next;
	if (m_next->type == GREAT || m_next->type == GREATER)
		return (other_text_create_me(m_parse));
	pwd = ft_strjoin(str, "/");
	pwd = ft_strjoin2(pwd, m_next->text[0]);
	if (m_parse->type == GREATER)
		m_next->fd = open(pwd, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (m_parse->type == GREAT)
		m_next->fd = open(pwd, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (m_parse->cmd)
		m_parse->outfile = m_next->fd;
	else if (prev_parse->cmd)
		prev_parse->outfile = m_next->fd;
	if (pwd)
		free(pwd);
}

/**
 * Bu fonksiyon, verilen bir shell yapısı üzerinde dosya oluşturma işlemlerini gerçekleştirir.
 * 
 * @param m_shell Shell yapısı
 * @return Oluşturma işlemi başarılıysa 1, aksi halde 0 döner.
 */
int create_files_m(t_shell *m_shell)
{
	t_parse *parse;
	int i;

	i = 1;
	parse = m_shell->parse;
	while (parse)
	{
		if (parse->type == GREAT || parse->type == GREATER)
			create_out_files_me(parse, m_shell->parse);
		else if (parse->type == LESS)
			i = create_in_files_me(parse);
		parse = parse->next;
	}
	return i;
}
