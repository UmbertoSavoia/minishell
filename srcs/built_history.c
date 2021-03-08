/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:04:47 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:27:13 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_hist	*tmp;

	if (!nuovo)
		return (0);
	while (*lst && (*lst)->prev)
		*lst = (*lst)->prev;
	tmp = (*lst)->next;
	(*lst)->next = nuovo;
	nuovo->next = tmp;
	nuovo->prev = *lst;
	tmp->prev = nuovo;
	return (1);
}

void	ft_hist_clear(t_hist **lst)
{
	t_hist *temp;
	t_hist *list;

	if (lst && *lst)
	{
		list = *lst;
		*lst = 0;
		while (list)
		{
			temp = list->next;
			free(list->content);
			free(list);
			list = temp;
		}
	}
}
