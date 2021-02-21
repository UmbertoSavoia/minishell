/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:31:00 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 14:48:51 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *temp;
	t_list *list;

	if (lst && *lst)
	{
		list = *lst;
		*lst = 0;
		while (list)
		{
			temp = list->next;
			ft_lstdelone(list, del);
			list = temp;
		}
	}
}
