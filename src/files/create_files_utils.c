

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	handle_relative_path(char **pwd, t_parse *current_parse)
{
	char	*str;
	char	*temp;
	t_parse	*m_next;

	str = getcwd(NULL, 0);
	m_next = current_parse->next;
	*pwd = ft_strjoin(str, "/");
	free(str);
	temp = ft_strjoin(*pwd, m_next->text[0]);
	free(*pwd);
	*pwd = temp;
}

int	create_in_files_me(t_parse *parse, t_shell *shell)
{
	t_parse	*nparse;
	char	*pwd;
	char	*home;

	home = get_env(shell->env, "HOME");
	nparse = parse->next;
	if (!ft_strnstr(nparse->text[0], home, ft_strlen(home)))
		handle_relative_path(&pwd, parse);
	else
		pwd = ft_strdup(nparse->text[0]);
	if (!access(pwd, F_OK))
		nparse->fd = open(pwd, O_RDONLY, 0777);
	else
	{
		if (pwd)
			free(pwd);
		printf("minishell: %s: No such file or directory\n", nparse->text[0]);
		return (0);
	}
	if (pwd)
		free(pwd);
	free(home);
	parse->infile = nparse->fd;
	return (1);
}
