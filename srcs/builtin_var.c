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
			ptr = ptr->next;
		}

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
		t = !*tmp->value ? "\"\"" : tmp->value;
		printf("%s=%s\n", tmp->key, t);
		tmp = tmp->next;
	}
	errno = 0;
	return (1);
}

void	add_env_list(int i)
{
	char	*tmp;
	int		w;
	int		j;

	j = 0;
	w = 0;
	tmp = get_key_env(g_shell.table_list[i]->next->content, &w);
	if (*(char*)(g_shell.table_list[i]->next->content + w + 1) == 0)
		return ;
	remove_t_env(&g_shell.envp, tmp, &ft_memcmp, &free);
	ft_push_front_env(&g_shell.envp, node_dup(get_value_set(tmp)));
	remove_t_env(&g_shell.var_list, tmp, &ft_memcmp, &free);
}

void	built_export(int i)
{
	t_list *tmp;

	tmp = g_shell.table_list[i]->next;
	if (!tmp && print_export())
		return ;
	else if (!var_search(tmp, '=', &ft_strchr))
	{
		if (get_value_set((char*)tmp->content))
			add_env_list(i);
		else
			add_var_list(i, 0);
	}
	else if (var_search(tmp, '=', &ft_strchr))
		add_env_full(i);
}
