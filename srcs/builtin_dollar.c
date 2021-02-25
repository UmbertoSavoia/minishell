#include "../include/minishell.h"

void	built_dollar(int i, char **node)
{
	unsigned long long	diff;
	t_env				*tmp;

	diff = *node - g_shell.st_t_list[i];
	if ((tmp = get_value_set(*node + 1)))
	{
		if (!diff)
			free(*node);
		*node = ft_strdup(tmp->value);
		return ;
	}
	else if ((tmp = get_value_env(*node + 1)))
	{
		if (!diff)
			free(*node);
		*node = ft_strdup(tmp->value);
		return ;
	}
	else
		errno = 0;
	return ;
}
