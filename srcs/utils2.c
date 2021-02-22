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
