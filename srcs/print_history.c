/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:10:40 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:42:21 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_hist(void)
{
	g_shell.history = malloc(sizeof(t_hist));
	g_shell.history->content = ft_strdup("\a");
	g_shell.history->next = 0;
	g_shell.history->prev = malloc(sizeof(t_hist));
	g_shell.history->prev->content = ft_strdup("");
	g_shell.history->prev->next = g_shell.history;
	g_shell.history->prev->prev = 0;
	g_shell.hist_size = 2;
}

void	navigate_next(int len)
{
	write(1, "\x1b[1K", 4);
	write(1, "\r", 1);
	print_prompt();
	ft_memcpy(g_shell.final_string, g_shell.history->content, len);
	g_shell.len_string = len;
	g_shell.curs += len;
}

void	navigate_prev(int len)
{
	write(1, "\x1b[1K", 4);
	write(1, "\r", 1);
	print_prompt();
	ft_memcpy(g_shell.final_string, g_shell.history->content, len);
	g_shell.len_string = len;
	g_shell.curs += len;
}

void	stop_navigate(void)
{
	write(1, "\x1b[1K", 4);
	write(1, "\r", 1);
	print_prompt();
}

void	navigate_history(int dir)
{
	static int		len;
	static int		size;

	if (!size)
		size = g_shell.hist_size;
	if (dir == UP && size >= 2)
	{
		(g_shell.history->next) ? g_shell.history = g_shell.history->next : 0;
		len = ft_strlen((char*)g_shell.history->content);
		navigate_next(len);
		write(1, ((char*)g_shell.history->content), len);
		(size != 2) ? size-- : 0;
		return ;
	}
	else if (dir == DW && size < g_shell.hist_size)
	{
		size++;
		(g_shell.history->prev) ? g_shell.history = g_shell.history->prev : 0;
		len = ft_strlen((char*)g_shell.history->content);
		navigate_prev(len);
		write(1, ((char*)g_shell.history->content), len);
		return ;
	}
	else if (size >= g_shell.hist_size)
		stop_navigate();
}
