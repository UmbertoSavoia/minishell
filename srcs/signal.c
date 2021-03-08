/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:11:45 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:29:37 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_sigint(int sig)
{
	if (g_shell.pid != 0)
	{
		ft_putchar_fd('\n', 1);
		errno = sig - 1;
		print_prompt();
	}
}

void	ft_sigquit(int sig)
{
	(void)sig;
	if (g_shell.pid != 0 && g_shell.curs != g_shell.len_prompt)
		ft_putstr_fd("\b\b  \b\b", 1);
}

void	ft_sigint_2(int sig)
{
	if (g_shell.pid != 0 && g_shell.curs != g_shell.len_prompt)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		ft_putchar_fd('\n', 1);
		errno = sig - 1;
	}
}
