/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:08:03 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:28:04 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	var_search(t_list *head, char c,
	char *(*f)(const char*, int))
{
	if (((*f)(head->content, c)))
		return (1);
	return (0);
}

void	create_var_list(t_list *ptr)
{
	char	*tmp;
	int		w;

	w = 0;
	while (ptr)
	{
		tmp = get_key_env(ptr->content, &w);
		remove_t_env(&g_shell.var_list, tmp, &ft_memcmp, &free);
		if (remove_t_env(&g_shell.envp, tmp, &ft_memcmp, &free))
			ft_push_front_env(&g_shell.envp,
				ft_create_node_env(ptr->content));
		ft_push_front_env(&g_shell.var_list,
			ft_create_node_env(ptr->content));
		ft_free(tmp);
		ptr = ptr->next;
	}
}

int		add_var_list(int i, char c)
{
	char	*tmp;
	int		w;
	t_list	*ptr;

	w = 0;
	if ((errno = 0) && !ft_isalpha(((char*)g_shell.table_list[i]->content)[0]))
	{
		printf(RED"minishell: %s: command not found"NC"\n",
		((char*)g_shell.table_list[i]->content));
		return (1);
	}
	if (c == 1)
	{
		ptr = g_shell.table_list[i];
		create_var_list(ptr);
	}
	else
	{
		tmp = get_key_env(g_shell.table_list[i]->next->content, &w);
		remove_t_env(&g_shell.var_list, tmp, &ft_memcmp, &free);
		ft_push_front_env(&g_shell.var_list,
			ft_create_node_env(g_shell.table_list[i]->next->content));
		ft_free(tmp);
	}
	return (0);
}
