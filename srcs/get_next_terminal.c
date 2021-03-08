/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_terminal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:03:23 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:26:36 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		termios_reset_mode(void)
{
	struct termios new;

	if (tcgetattr(STDIN_FILENO, &new) == -1)
	{
		printf("tcgetattr can't get\n%s\n", strerror(errno));
		return (0);
	}
	if (!ft_memcmp(&g_shell.orig_termios, &new, sizeof(struct termios)))
		return (1);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_shell.orig_termios) == -1)
	{
		printf("tcgetattr can't get\n%s\n", strerror(errno));
		return (0);
	}
	return (1);
}

void	enable_raw_mode(void)
{
	int				ret;

	ret = 0;
	if ((ret = tcgetattr(STDIN_FILENO, &g_shell.orig_termios)) == -1)
		print_error(ret);
	g_shell.raw = g_shell.orig_termios;
	g_shell.raw.c_iflag &= ~(ICRNL | IXON);
	g_shell.raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	g_shell.raw.c_cc[VMIN] = 0;
	g_shell.raw.c_cc[VTIME] = 1;
	if ((ret = tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_shell.raw)) == -1)
		print_error(ret);
}

char	editor_read_key(void)
{
	int		nread;
	char	c;

	while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
	{
		if (nread == -1 && errno != EAGAIN)
			print_error(nread);
	}
	return (c);
}

int		process_keypress(char c)
{
	if (c == CTRL_KEY('q'))
		exit(0);
	else if (c == CTRL_KEY('d'))
		return (0);
	else if ((c == 127) && (g_shell.curs > g_shell.len_prompt))
		key_del();
	else if (' ' <= c && c <= 126)
		key_char(c);
	else if (c == '\x1b')
		key_arrow();
	else
		return (-1);
	return (1);
}

int		get_next_terminal(char **input)
{
	char	c;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	ft_bzero(g_shell.final_string, sizeof(g_shell.final_string));
	enable_raw_mode();
	while (1)
	{
		c = editor_read_key();
		if (c == '\r')
		{
			write(1, "\n\r", 2);
			write(1, "\r", 1);
			break ;
		}
		if (!(ret = process_keypress(c)))
			return (0);
	}
	*input = ft_strdup(g_shell.final_string);
	return (1);
}
