/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:04:14 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:27:16 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	built_exit_code(t_list *value)
{
	int i;

	i = 0;
	while (((char*)value->content)[i])
	{
		if (!ft_isdigit(((char*)value->content)[i]))
		{
			i = -1;
			break ;
		}
		i++;
	}
	if (i == -1)
	{
		printf(RED"minishell: exit: %s: numeric argument required"NC"\n",
		((char*)value->content));
		exit(255);
	}
	i = ft_atoi((char*)value->content);
	termios_reset_mode();
	exit(i);
}

void	clean_exit(void)
{
	if (g_shell.envp)
		env_clear(g_shell.envp);
	if (g_shell.table_list)
		clear_table_list();
	if (g_shell.var_list)
		env_clear(g_shell.var_list);
	ft_hist_clear(&g_shell.history);
	free(g_shell.user);
	ft_putendl_fd("exit", 1);
	exit(0);
}

void	built_exit(int i)
{
	t_list	*tmp;
	int		freeable;

	freeable = 0;
	if (i == -1)
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	tmp = g_shell.table_list[i];
	if (tmp->next && tmp->next->next)
	{
		printf(RED"exit \nminishell: exit: too many arguments"NC"\n");
		return ;
	}
	if (!tmp->next || i == -1)
		clean_exit();
	if (ft_strchr(((char*)tmp->next->content), '$'))
		built_dollar(i, (char**)&(tmp->next->content), &freeable);
	built_exit_code(tmp->next);
}
