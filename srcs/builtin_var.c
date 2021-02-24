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

	w = 0;
	if (c == 1)
	{
		tmp = get_key_env(g_shell.table_list[i]->content, &w);
		remove_t_env(&g_shell.var_list, tmp, &ft_memcmp, &free);
		ft_push_front_env(&g_shell.var_list,
			ft_create_node_env(g_shell.table_list[i]->content));
	}
	else
	{
		tmp = get_key_env(g_shell.table_list[i]->next->content, &w);
		remove_t_env(&g_shell.var_list, tmp, &ft_memcmp, &free);
		ft_push_front_env(&g_shell.var_list,
			ft_create_node_env(g_shell.table_list[i]->next->content));
	}
}

int		built_set(void)
{
	t_env	*tmp;
	char	*t;

	tmp = g_shell.var_list;
	while (tmp)
	{
		t = !*tmp->value ? "\'\'" : tmp->value;
		printf("%s=%s\n", tmp->key, t);
		tmp = tmp->next;
	}
	errno = 0;
	return (1);
}

void	built_export(int i)
{
	t_list *tmp;

	tmp = g_shell.table_list[i]->next;
	if (!tmp && (built_env() && built_set()))
		return ;
	else if (var_search(tmp, '=', &ft_strchr))
		add_var_list(i, 0);
}
