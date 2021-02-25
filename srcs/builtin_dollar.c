#include "../include/minishell.h"

void	built_dollar(char **node)
{
	t_env	*tmp;

	if ((tmp = get_value_set(*node + 1)))
	{
		//free(*node);
		*node = ft_strdup(tmp->value);
		return ;
	}
	else if ((tmp = get_value_env(*node + 1)))
	{
		//free(*node);
		*node = ft_strdup(tmp->value);
		return ;
	}
	else
		errno = 0;
	return ;
}
