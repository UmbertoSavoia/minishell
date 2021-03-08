/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_terminal_alpha_key.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:09:00 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:28:38 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	insert_char_in_the_middle(char c)
{
	char	*escape;
	int		len_print;
	int		i;
	int		at;

	at = g_shell.curs - g_shell.len_prompt;
	i = g_shell.len_string + 1;
	while (i > at)
	{
		g_shell.final_string[i] = g_shell.final_string[i - 1];
		i--;
	}
	g_shell.final_string[i] = c;
	g_shell.len_string++;
	len_print = (g_shell.final_string + g_shell.len_string) -
		&g_shell.final_string[at];
	write(1, &g_shell.final_string[at], len_print);
	escape = escape_cursor_create((g_shell.len_string - 2 +
		g_shell.len_prompt) - g_shell.curs + 1, "D");
	g_shell.curs++;
	write(1, escape, ft_strlen(escape));
	free(escape);
}

int		key_char(char c)
{
	if (g_shell.curs < (g_shell.len_string + g_shell.len_prompt))
		insert_char_in_the_middle(c);
	else
	{
		g_shell.final_string[g_shell.curs - g_shell.len_prompt] = c;
		g_shell.curs++;
		write(1, &c, 1);
		g_shell.len_string++;
	}
	return (1);
}
