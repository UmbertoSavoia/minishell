/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_t_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:11:26 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:29:30 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		env_lstdelone(t_env *lst, void (*del)(void*))
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
	return (1);
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
		ret = env_lstdelone(it, del);
		it = *head;
	}
	while (it && it->next)
	{
		if (!cmp(data, it->next->key, ft_strlen(data)))
		{
			tmp = it->next;
			it->next = tmp->next;
			ret = env_lstdelone(tmp, del);
		}
		else
			it = it->next;
	}
	return (ret);
}
