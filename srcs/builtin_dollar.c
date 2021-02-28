#include "../include/minishell.h"

int		built_dollar_support(int j, char **node, t_env *tmp)
{
	if ((tmp = get_value_set(*node + 1)))
	{
		if (!j)
			free(*node);
		*node = ft_strdup(tmp->value);
		errno = 0;
		return (1);
	}
	else if ((tmp = get_value_env(*node + 1)))
	{
		if (!j)
			free(*node);
		*node = ft_strdup(tmp->value);
		errno = 0;
		return (1);
	}
	return (0);
}

void	built_dollar(int i, char **node)
{
	t_list				*ptr;
	char				*tmp;
	int					j;
	char				c;

	j = 0;
	c = 0;
	int w = ft_strlen(*node);
	ptr = g_shell.table_list[i];
	while (ptr)
	{
		if (!ft_strncmp(ptr->content, *node, ft_strlen(*node)))
			break ;
		j++;
		ptr = ptr->next;
	}
	if ((*node)[0] == '\'' && (*node)[w - 1] == '\'')
	{
		if (!j)
		{
			tmp = ft_strdup((*node) + 1);
			free(*node);
			*node = tmp;
		}
		else
			(*node)++;
		(*node)[w - 2] = 0;
		return ;
	}
	if (built_dollar_support(j, node, 0))
		return ;
}
