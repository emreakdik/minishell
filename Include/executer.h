/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:51:55 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:51:55 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "tables.h"
# include "macros.h"

//MAIN
void	executer(void);

//RUNCOMMAND
void	run_single_command(t_cmdlist *cmd_list, int *fd);
void	run_multiple_command(t_cmdlist *cmd_list);

void	exec_command(t_cmdlist *cmd_node, int *fd, int fd_index);
char	*get_cmd(char *cmd);

void	run_process(t_cmdlist *cmd_list, int *fd, int fd_index);
void	wait_all(void);

int		*create_pipe(void);
void	clear_pipe(int *fd);
void	switch_pipe(int **fd);

//BUILTIN
void	run_builtin(t_cmdlist *cmd_node, int builtin, int *fd, int fd_index);
int		is_builtin(char *cmd);

void	run_cd(t_cmdlist *cmd_node);
void	cd_single_arg(void);
void	cd_double_arg(t_cmdlist *cmd_node);
int		change_dir(char *path);
int		update_pwd_from_export(char *pwd_name, char *pwd_content);

void	run_echo(t_cmdlist *cmd_node);

void	run_unset(t_cmdlist *cmd_node);
void	delete_env(char *name);

void	run_env(t_cmdlist *cmd_node);

void	run_exit(t_cmdlist *cmd_node);
int		is_all_numeric(char *text);

void	run_export(t_cmdlist *cmd_node);
void	single_export_arg(t_cmdlist *cmd_node);
void	double_export_arg(char *env_cmd);
int		change_env(char *envname, char *arg, int is_equal);

void	run_pwd(t_cmdlist *cmd_node);

//EXECVE
void	run_execve(t_cmdlist *cmd_node, int *fd, int fd_index);

//DUPw
void	create_dup(t_cmdlist *cmd_list, int *fd, int fd_index);

#endif
