/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:07:14 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:27:51 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	built_pwd(void)
{
	char tmp[PATH_MAX];

	errno = 0;
	getcwd(tmp, PATH_MAX);
	ft_putendl_fd(tmp, 1);
}

int		built_env(int i)
{
	t_env *tmp;

	tmp = g_shell.envp;
	errno = 0;
	if (g_shell.table_list[i]->next != 0)
	{
		ft_putendl_fd(RED"env: too many arguments"NC, 1);
		errno = 1;
		return (0);
	}
	while (tmp)
	{
		if (tmp->key[0] != '?')
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (1);
}
