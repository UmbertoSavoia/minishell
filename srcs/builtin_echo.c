/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:06:50 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:27:42 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	built_echo_option(int i, t_list *tmp, int *freeable)
{
	tmp = tmp->next->next;
	while (tmp)
	{
		if (ft_strchr(((char*)tmp->content), '$'))
			built_dollar(i, (char**)&(tmp->content), freeable);
		ft_putstr_fd(((char*)tmp->content), 1);
		ft_putstr_fd(" ", 1);
		if (*freeable)
			free(tmp->content);
		tmp = tmp->next;
	}
	ft_putstr_fd("\b", 1);
}

static	void	echo_no_option(int i, t_list *tmp, int *freeable)
{
	while (tmp)
	{
		if (ft_strchr(((char*)tmp->content), '$'))
			built_dollar(i, (char**)&(tmp->content), freeable);
		ft_putstr_fd(((char*)tmp->content), 1);
		ft_putstr_fd(" ", 1);
		if (*freeable)
			free(tmp->content);
		tmp = tmp->next;
	}
}

void			built_echo(int i)
{
	t_list	*tmp;
	int		freeable;

	freeable = 0;
	errno = 0;
	tmp = g_shell.table_list[i];
	if (tmp->next)
	{
		if (!ft_memcmp(tmp->next->content, "-n", 3))
			built_echo_option(i, tmp, &freeable);
		else
		{
			tmp = tmp->next;
			echo_no_option(i, tmp, &freeable);
			ft_putstr_fd("\b", 1);
			ft_putendl_fd("", 1);
		}
	}
	else
		printf("\n");
}
