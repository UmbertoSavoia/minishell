#include "../include/minishell.h"

char	list_search(t_list *head, char *str,
	int (*f)(const void*, const void*, size_t))
{
	while (head)
	{
		if (!((*f)(str, head->content, ft_strlen(str) + 1)))
			return (1);
		head = head->next;
	}
	return (0);
}

void	clear_table_list(void)
{
	int		i;

	i = 0;
	while (g_shell.table_list[i])
	{
		free(g_shell.table_list[i]->content);
		ft_lstclear(&g_shell.table_list[i], 0);
		i++;
	}
	free(g_shell.table_list);
}
