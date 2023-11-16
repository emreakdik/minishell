/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 06:03:07 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 06:03:07 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tables.h"
# include "macros.h"

//MAIN
void		parser(void);

//CREATECMDTABLE
void		create_cmdtable(t_lexlist *lex_table);
void		fill_cmdtable_node(t_cmdlist *node);
void		create_cmdtable_nodes(int count);

//FILLTABLE
void		fill_cmdtable(void);
void		fill_cmdnode(t_cmdlist *node, t_lexlist **lex_list);

char		**create_path(t_lexlist *lex_list);

int			create_new_filelist(t_cmdlist *node, t_lexlist **lex_list);
t_filelist	*add_filelist(t_filelist **file_list, char *filename, char *meta);

//CREATEFILES
void		create_files(t_cmdlist *node);

void		run_heradocs(t_cmdlist *node);
int			read_heradoc(t_cmdlist *node, char *eof);
void		set_heradoc_value(t_cmdlist *node, int *fd);
void		fill_heradoc(char *eof, int *fd);
char		*get_heradoc_values(char *eof);

void		close_heradoc_file(void);
void		open_heradoc_file(char	*create_mode);

void		create_infile(t_cmdlist *node, t_filelist *file);

void		create_outfile(t_cmdlist *node, t_filelist *file);

int			check_directory_error(char *file_name);
int			raise_file_error(t_filelist *file, int *file_output);

//FREEPARSER
void		free_parser(void);
void		free_filelist(t_filelist *files);

void		print_files(t_filelist *temp_filelist);
void		print_parser(void);

#endif
