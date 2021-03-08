/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:07:36 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:27:55 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		built_set(void)
{
	t_env	*tmp;
	char	*t;

	tmp = g_shell.var_list;
	errno = 0;
	while (tmp)
	{
		t = !*tmp->value ? "\"\"" : tmp->value;
		printf("%s=%s\n", tmp->key, t);
		tmp = tmp->next;
	}
	return (1);
}
