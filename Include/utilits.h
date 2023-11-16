/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 06:09:52 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 06:09:52 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITS_H
# define UTILITS_H

# include "tables.h"
# include "macros.h"

//ENV
void	fill_envs(char **env);
t_env	*add_newenv(t_env **env_table, char *env);

char	*get_env_name(char *content);
int		get_env_name_count(char *env_arg);

int		update_env(char *env_name, char *new_arg);

char	**get_env_cpy(void);
int		get_env_len(void);
void	free_env_cpy(char **envlist);

int		env_arg_control(char *env);

//METACHAR
char	*compare_metachars(char *cmd_line);
void	set_metachars(void);

//STR
int		ft_atoi(const char *str);

char	*ft_itoa(int number);
int		get_numbercount(int number);

char	*ft_strdup(char *ptr);

char	*ft_strpcpy(char *dst, char *src, int count);

size_t	ft_strlen(char *ptr);

void	own_strjoin(char **dst, char *src);

void	str_addchar(char **dst, char c);

int		get_array_len(char **array);

int		str_compare(char *str1, char *str2);

size_t	trim_spaces(char **cmd_line);

//TITLE
void	set_title(void);
void	change_title(void);

//ERROR
int		print_lex_error(t_lexlist *lex_list);
void	print_error(char *ptr1, char *ptr2, char *ptr3);

//FREE
void	free_metachars(void);
void	free_envtable(void);
void	free_title(void);

#endif
