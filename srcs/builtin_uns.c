/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_uns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:07:48 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:28:00 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	built_unset(int i)
{
	t_list *tmp;

	tmp = g_shell.table_list[i]->next;
	if (!ft_isalpha(((char*)tmp->content)[0]))
	{
		(printf(RED"minishell: unset: '%s': not a valid identifier"NC"\n",
			(char*)tmp->content));
		return ;
	}
	while (tmp != 0)
	{
		errno = 0;
		if (((char*)tmp->content)[0] == '?')
			break ;
		if (g_shell.envp)
			remove_t_env(&g_shell.envp,
				tmp->content, &ft_memcmp, &free);
		if (g_shell.var_list)
			remove_t_env(&g_shell.var_list,
				tmp->content, &ft_memcmp, &free);
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
}
