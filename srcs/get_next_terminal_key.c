/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_terminal_key.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:09:22 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:28:46 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		key_del(void)
{
	int		at;
	int		len_print;
	char	*escape;

	at = (g_shell.curs - 1) - g_shell.len_prompt;
	ft_memmove(&g_shell.final_string[at], &g_shell.final_string[at + 1],
		g_shell.len_string - at);
	g_shell.len_string--;
	write(1, "\x1b[D", 3);
	write(1, " ", 1);
	g_shell.curs--;
	write(1, "\x1b[D", 3);
	len_print = (g_shell.final_string + g_shell.len_string) -
		&g_shell.final_string[g_shell.curs - g_shell.len_prompt];
	write(1, &g_shell.final_string[g_shell.curs - g_shell.len_prompt],
		len_print);
	write(1, " ", 1);
	escape = escape_cursor_create((g_shell.len_string + g_shell.len_prompt) -
		g_shell.curs + 1, "D");
	write(1, escape, ft_strlen(escape));
	free(escape);
	return (1);
}

void	key_home_end(char c)
{
	char	*escape;

	if (c == 'H')
	{
		escape = escape_cursor_create(g_shell.len_prompt + 1, "G");
		write(1, escape, strlen(escape));
		g_shell.curs = g_shell.len_prompt;
		free(escape);
	}
	else if (c == 'F')
	{
		escape = escape_cursor_create(g_shell.len_string +
			g_shell.len_prompt + 1, "G");
		write(1, escape, strlen(escape));
		g_shell.curs = g_shell.len_string + g_shell.len_prompt;
		free(escape);
	}
}

int		key_arrow_support(char c)
{
	int		start;

	if (c == 'H' || c == 'F')
		key_home_end(c);
	else if (c == 'D')
	{
		if ((g_shell.curs > g_shell.len_prompt) && g_shell.curs--)
			write(1, "\x1b[D", 3);
	}
	else if (c == 'C')
	{
		start = g_shell.curs - g_shell.len_prompt;
		if ((start < g_shell.len_string) && g_shell.curs++)
			write(1, "\x1b[C", 3);
	}
	else if (c == 'A')
		navigate_history(UP);
	else if (c == 'B')
		navigate_history(DW);
	return (1);
}

void	exec_ctrl_left_right(void)
{
	char	seq[3];

	read(STDIN_FILENO, &seq[1], 1);
	read(STDIN_FILENO, &seq[2], 2);
	if (seq[1] == '5')
	{
		if (seq[2] == 'D')
			ctrl_left();
		else if (seq[2] == 'C')
			ctrl_right();
	}
}

int		key_arrow(void)
{
	char	seq[3];
	int		start;

	start = 0;
	read(STDIN_FILENO, &seq[0], 1);
	read(STDIN_FILENO, &seq[1], 1);
	if (seq[0] == '[')
	{
		if (seq[1] >= '0' && seq[1] <= '9')
		{
			read(STDIN_FILENO, &seq[2], 1);
			if (seq[2] == ';')
				exec_ctrl_left_right();
		}
		else if (seq[1] == 'H' || seq[1] == 'F' || seq[1] == 'D' ||
			seq[1] == 'C' || seq[1] == 'A' || seq[1] == 'B')
			key_arrow_support(seq[1]);
	}
	return (1);
}
