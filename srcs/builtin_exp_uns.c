
#include "../include/minishell.h"

t_env	*get_prev_value_env(char *key)
{
	t_env	*tmp;
	int		len_key;

	len_key = ft_strlen(key);
	tmp = g_shell.envp;
	while (tmp->next)
	{
		if (!ft_strncmp(tmp->next->key, key, len_key))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

void	built_unset(int i)
{
	t_env	*prev;
	t_env	*node;

	if (g_shell.table_list[i]->next != 0)
	{
		prev = get_prev_value_env(g_shell.table_list[i]->next->content);
		node = prev->next;
		prev->next = node->next;
		node->next = 0;
		free(node->key);
		free(node->value);
		free(node);
	}
	else
		ft_putendl_fd(RED"unset: not enough arguments"NC, 1);
}