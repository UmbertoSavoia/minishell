#include "../include/minishell.h"

void	built_dollar(int i, char **node)
{
	t_env				*tmp;
	t_list				*ptr;
	int					j;

	j = 0;
	ptr = g_shell.table_list[i];
	while (ptr)
	{
		if (!ft_strncmp(ptr->content, *node, ft_strlen(*node)))
			break ;
		j++;
		ptr = ptr->next;
	}
	if ((tmp = get_value_set(*node + 1)))
	{
		if (!j)
			free(*node);
		*node = ft_strdup(tmp->value);
		return ;
	}
	else if ((tmp = get_value_env(*node + 1)))
	{
		if (!j)
			free(*node);
		*node = ft_strdup(tmp->value);
		return ;
	}
	else
	{
		if (!j)
			free(*node);
		*node = ft_strdup("");
		errno = 1;
		return ;
	}
}
