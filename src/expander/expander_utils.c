

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	is_count_odd(char *before, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (before[i])
	{
		if (before[i] == c)
			count++;
		i++;
	}
	if (count == 0)
		return (-2);
	i = 0;
	if (count % 2 == 1)
	{
		while (before[i])
		{
			if (before[i] == c)
				return (i);
			i++;
		}
	}
	return (-1);
}

int	check_quote(char *before, char *after)
{
	int	single_quotes_before;
	int	single_quotes_after;
	int	double_quotes_before;
	int	double_quotes_after;

	single_quotes_before = is_count_odd(before, '\'');
	single_quotes_after = is_count_odd(after, '\'');
	double_quotes_before = is_count_odd(before, '\"');
	double_quotes_after = is_count_odd(after, '\"');
	if (double_quotes_after > -1 && after[1] == '\"')
		return (0);
	else if ((single_quotes_before > -1 && single_quotes_after < 0))
		return (1);
	else if ((single_quotes_before > -1 && single_quotes_after > -1)
		&& (double_quotes_before > -1 && double_quotes_after > -1))
		return (single_quotes_before > double_quotes_before);
	else if ((single_quotes_before > -1 && single_quotes_after > -1)
		&& (double_quotes_before < 0 && double_quotes_after < 0))
		return (0);
	else if ((single_quotes_before < 0 && single_quotes_after < 0)
		&& (double_quotes_before > -1 && double_quotes_after > -1))
		return (1);
	return (1);
}

static void	if_there_is_no_env(char *key, char **ret)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (key[i] && ft_isalnum(key[i]))
		i++;
	j = i;
	while (key[j])
		j++;
	*ret = ft_substr(key, i, j - i);
}

char	*get_env(t_list *env, char *key)
{
	t_env	*tmp;
	char	*ret;
	int		flag;

	flag = 0;
	ret = NULL;
	while (env)
	{
		tmp = env->content;
		if (ft_ultimatestrcmp(tmp->key, key, 0, &flag))
		{
			if (flag == 1)
				ret = ft_strdup(key + ft_ultimatestrcmp(tmp->key, key, 0,
							&flag));
			else
				ret = ft_strjoin(tmp->value, key + ft_ultimatestrcmp(tmp->key,
							key, 0, &flag));
			return (ret);
		}
		env = env->next;
	}
	if_there_is_no_env(key, &ret);
	return (ret);
}

int	ft_ultimatestrcmp(char *key, char *tmp, int i, int *flag)
{
	int	j;

	j = 0;
	while (tmp[i++] == key[j++])
	{
		if (!key[j])
		{
			if (!ft_isalnum(tmp[i]))
				return (i);
			while (ft_isalnum(tmp[i]))
				i++;
			if (tmp[i])
			{
				*flag = 1;
				return (i);
			}
			return (0);
		}
	}
	return (0);
}
