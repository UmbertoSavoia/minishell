#include "../include/minishell.h"

int		is_valid_content(void *content)
{
	int i;

	i = 0;
	if (!content || !((char*)content)[i])
		return (0);
	while (((char*)content)[i] && ((char*)content)[i] == 32)
		i++;
	if (!((char*)content)[i])
		return (0);
	return (1);
}

t_hist	*ft_histnew(void *content)
{
	t_hist	*ret;

	if (is_valid_content(content))
	{
		if (!(ret = malloc(sizeof(t_hist))))
			return (0);
		ret->content = ft_strdup((char*)content);
		ret->prev = 0;
		ret->next = 0;
		return (ret);
	}
	return (0);
}

int		ft_histadd_front(t_hist **lst, t_hist *nuovo)
{
	int first;

	first = 0;
	if (!*lst)
		first = 1;
	if (!nuovo)
		return (0);
	while (*lst && (*lst)->prev)
		*lst = (*lst)->prev;
	nuovo->next = *lst;
	*lst = nuovo;
	if (!first)
		nuovo->next->prev = *lst;
	return (1);
}

void	ft_hist_clear(t_hist **lst, void (*del)(void*))
{
	t_hist *temp;
	t_hist *list;

	if (lst && *lst)
	{
		list = *lst;
		*lst = 0;
		while (list)
		{
			list->next->prev = 0;
			temp = list->next;
			ft_hist_delone(list, del);
			list = temp;
		}
	}
}

void	ft_hist_delone(t_hist *lst, void (*del)(void*))
{
	if (lst)
	{
		if (del)
			del(lst->content);
		free(lst);
	}
}
