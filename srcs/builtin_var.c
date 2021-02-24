#include "../include/minishell.h"

char	var_search(t_list *head, char c,
	char *(*f)(const char*, int))
{
	while (head)
	{
		if (((*f)(head->content, c)))
			return (1);
		head = head->next;
	}
	return (0);
}

void	add_var_list(int i)
{
	ft_push_front_env(&g_shell.var_list,
		ft_create_node_env(g_shell.table_list[i]->content));
}

void	built_set(void)
{
	t_env *tmp;

	tmp = g_shell.var_list;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	errno = 0;
}
