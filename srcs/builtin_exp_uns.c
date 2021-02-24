#include "../include/minishell.h"

void	env_lstdelone(t_env *lst, void (*del)(void*))
{
	if (lst)
	{
		if (del)
		{
			del(lst->key);
			del(lst->value);
		}
		free(lst);
	}
}

int		remove_t_env(t_env **head, void *data,
			int (*cmp)(const void*, const void*, size_t), void (*del)(void*))
{
	t_env	*it;
	t_env	*tmp;
	int		ret;

	it = *head;
	ret = 0;
	while (it && !cmp(data, it->key, ft_strlen(data)))
	{
		*head = it->next;
		env_lstdelone(it, del);
		it = *head;
		ret = 1;
	}
	if (!it)
		return (ret);
	while (it->next)
	{
		if (!cmp(data, it->next->key, ft_strlen(data)))
		{
			tmp = it->next;
			it->next = tmp->next;
			env_lstdelone(tmp, del);
			ret = 1;
		}
		else
			it = it->next;
	}
	return (ret);
}

void	built_unset(int i)
{
	t_list *tmp;

	tmp = g_shell.table_list[i]->next;
	while (tmp != 0)
	{
		if (g_shell.envp)
			remove_t_env(&g_shell.envp,
				tmp->content, &ft_memcmp, &free);
		if (g_shell.var_list)
			remove_t_env(&g_shell.var_list,
				tmp->content, &ft_memcmp, &free);
		errno = 0;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	ft_putendl_fd(RED"unset: not enough arguments"NC, 1);
	errno = 1;
}
