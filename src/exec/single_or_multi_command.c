

#include "../../includes/minishell.h"

int	single_or_multi_command(t_shell *m_shell)
{
	t_parse	*parse;
	int		i;

	i = 0;
	parse = m_shell->parse;
	while (parse)
	{
		if (parse->type == 2)
			i++;
		parse = parse->next;
	}
	return (i);
}
