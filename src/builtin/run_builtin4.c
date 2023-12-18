#include "../../includes/minishell.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

bool	is_numeric(char *s)
{
	while ((9 <= *s && *s <= 13) || *s == 32)
		s++;
	if (*s == 43 || *s == 45)
		s++;
	while (48 <= *s && *s <= 57)
		s++;
	while ((9 <= *s && *s <= 13) || *s == 32)
		s++;
	if (*s != '\0')
		return (false);
	return (true);
}

void	builtin_exit(t_shell **m_shell)
{
	bool	status;
	int		exit_value;
	t_parse	*parse;

	exit_value = 0;
	parse = (*m_shell)->parse;
	printf("exit\n");
	if (!parse->text)
		exit(EXIT_SUCCESS);
	status = is_numeric(parse->text[0]);
	if (status == false)
	{
		printf("bash: exit: %s: numeric argument required\n", parse->text[0]);
		exit_value = 255;
	}
	else if (status == true && !parse->text[1])
		exit_value = ft_atoi(parse->text[0]);
	else
	{
		printf("bash: exit: too many arguments\n");
		return ;
	}
	free_loop(1, *m_shell);
	free_(*m_shell);
	free((*m_shell)->lex_list);
	free(*m_shell);
	exit(exit_value);
}
