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

	exit_value = 0;
	printf("exit\n");
	if (!(*m_shell)->parse->text)
		exit(EXIT_SUCCESS);
	status = is_numeric((*m_shell)->parse->text[0]);
	if (status == false)
	{
		printf("bash: exit: %s: numeric argument required\n",
			(*m_shell)->parse->text[0]);
		exit_value = 255;
	}
	else if (status == true && !(*m_shell)->parse->text[1])
		exit_value = ft_atoi((*m_shell)->parse->text[0]);
	else
	{
		printf("bash: exit: too many arguments\n");
		(*m_shell)->exec_status = 1;
		return ;
	}
	(free_loop(1, *m_shell), free_(*m_shell));
	(free((*m_shell)->lex_list), free(*m_shell));
	exit(exit_value);
}
