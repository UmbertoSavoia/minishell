#include "libft.h"

void	ft_lstremove_if(t_list **head, void *data, int (*cmp)(void*, void*, size_t),
	void (*del)(void*))
{
	t_list *it;
	t_list *tmp;

	it = *head;
	while (it && !cmp(data, it->content, ft_strlen(data)))
	{
		*head = it->next;
		ft_lstdelone(it, del);
		it = *head;
	}
	if (!it)
		return ;
	while (it->next)
	{
		if (!cmp(data, it->next->content, ft_strlen(data)))
		{
			tmp = it->next;
			it->next = tmp->next;
			ft_lstdelone(tmp, del);
		}
		else
			it = it->next;
	}
}
