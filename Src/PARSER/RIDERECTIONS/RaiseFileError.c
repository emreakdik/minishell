/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RaiseFileError.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozsayar <aozsayar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 05:19:29 by aozsayar          #+#    #+#             */
/*   Updated: 2022/12/28 05:19:29 by aozsayar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

int	check_directory_error(char *file_name)
{
	char	*temp_file_name;

	temp_file_name = file_name;
	while (file_name && *file_name)
	{
		if (*(file_name++) == '/')
		{
			print_error("-bash: ", temp_file_name, ": Is a directory\n");
			return (0);
		}
	}
	return (1);
}

int	raise_file_error(t_filelist *file, int *file_output)
{
	int		error;

	error = 0;
	if (!check_directory_error(file->filename))
		error = 1;
	if (!error && *file->filename == '\"')
	{
		error = 1;
		print_error("-bash: : No such file or directory\n", NULL, NULL);
	}
	else if (!error && *file->filename == '$')
	{
		error = 1;
		print_error("-bash: ", file->filename, ": ambiguous redirect\n");
	}
	if (!error)
		return (error);
	file->fd = SSTDERR;
	*file_output = file->fd;
	return (error);
}
