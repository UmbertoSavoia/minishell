#include "../include/minishell.h"

char	var_search(t_list *head, char c,
	char *(*f)(const char*, int))
{
	if (((*f)(head->content, c)))
		return (1);
	return (0);
}

void	add_var_list(int i, char c)
{
	char	*tmp;
	int		w;
	t_list	*ptr;

	w = 0;
	if (c == 1)
	{
		ptr = g_shell.table_list[i];
		while (ptr)
		{
			tmp = get_key_env(ptr->content, &w);
			remove_t_env(&g_shell.var_list, tmp, &ft_memcmp, &free);
			if (remove_t_env(&g_shell.envp, tmp, &ft_memcmp, &free))
				ft_push_front_env(&g_shell.envp,
				ft_create_node_env(ptr->content));
			ft_push_front_env(&g_shell.var_list,
				ft_create_node_env(ptr->content));
			free(tmp);
			ptr = ptr->next;
		}
	}
	else
	{
		tmp = get_key_env(g_shell.table_list[i]->next->content, &w);
		remove_t_env(&g_shell.var_list, tmp, &ft_memcmp, &free);
		ft_push_front_env(&g_shell.var_list,
			ft_create_node_env(g_shell.table_list[i]->next->content));
		free(tmp);
	}
}
