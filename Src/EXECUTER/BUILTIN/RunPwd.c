/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunPwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:42:23 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:42:23 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

void	run_pwd(t_cmdlist *cmd_node)
{
	char	cwd[256];
	char	*pwd;

	pwd = getcwd(cwd, 256);
	write(cmd_node->outfile, pwd, ft_strlen(pwd));
	write(cmd_node->outfile, "\n", 1);
}
