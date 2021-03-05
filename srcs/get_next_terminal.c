#include "../include/minishell.h"

void	print_error(int error)
{
	(void)error;
	printf(RED"\n%s"NC, strerror(errno));
	exit(1);
}

void disable_raw_mode(void)
{
	int		ret;

	ret = 0;
	if ((ret = tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_shell.orig_termios)) == -1)
		print_error(ret);
}

void enable_raw_mode(void)
{
	int				ret;

	ret = 0;
	if ((ret = tcgetattr(STDIN_FILENO, &g_shell.orig_termios)) == -1)
		print_error(ret);
	g_shell.raw = g_shell.orig_termios;
	g_shell.raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	g_shell.raw.c_cflag |= (CS8);
	g_shell.raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);						//attivare la funzione per andare ai signal
	g_shell.raw.c_cc[VMIN] = 0;
	g_shell.raw.c_cc[VTIME] = 1;
	if ((ret = tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_shell.raw)) == -1)
		print_error(ret);
}

char	*escape_cursor_create(int pos)
{
	char	*ret;
	char	*temp;
	char	*num;
	int		i;
	int		len_num;
	int		j;

	j = 0;
	i = 5;
	num = ft_itoa(pos);
	len_num = ft_strlen(num);
	temp = ft_strjoin("\x1b[", num);
	ret = ft_strjoin(temp, "D");
	free(temp);
	free(num);
	return (ret);
}

char editor_read_key(void)
{
	int nread;
	char c;

	while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
	{
		if (nread == -1 && errno != EAGAIN)
			print_error(nread);
	}
	return (c);
}

int		key_del(void)
{
	int		at;
	int		len_print;
	char	*escape;

	at = (g_shell.curs - 1) - g_shell.len_prompt;
	ft_memmove(&g_shell.final_string[at], &g_shell.final_string[at + 1], g_shell.len_string - at);
	g_shell.len_string--;
	write(1, "\x1b[D", 3);
	write(1, " ", 1);
	g_shell.curs--;
	write(1, "\x1b[D", 3);
	len_print = (g_shell.final_string + g_shell.len_string) - &g_shell.final_string[g_shell.curs - g_shell.len_prompt];
	write(1, &g_shell.final_string[g_shell.curs - g_shell.len_prompt], len_print);
	write(1, " ", 1);
	escape = escape_cursor_create((g_shell.len_string + g_shell.len_prompt) - g_shell.curs + 1);
	write(1, escape, ft_strlen(escape));
	free(escape);

	return (1);
}

int		key_char(char c)
{
	int		at;
	int		len_print;
	char	*escape;
	int		i;

	if (g_shell.curs < (g_shell.len_string + g_shell.len_prompt))
	{
		at = g_shell.curs - g_shell.len_prompt;
		i = g_shell.len_string+1;
		while (i > at)
		{
			g_shell.final_string[i] = g_shell.final_string[i-1];
			i--;
		}
		g_shell.final_string[i] = c;
		g_shell.len_string++;
		len_print = (g_shell.final_string + g_shell.len_string) - &g_shell.final_string[at];
		write(1, &g_shell.final_string[at], len_print);
		escape = escape_cursor_create((g_shell.len_string - 2 + g_shell.len_prompt) - g_shell.curs + 1);
		g_shell.curs++;
		write(1, escape, ft_strlen(escape));
		free(escape);
	}
	else
	{
		g_shell.final_string[g_shell.curs - g_shell.len_prompt] = c;
		g_shell.curs++;
		write(1, &c, 1);
		g_shell.len_string++;
	}
	return (1);
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
		if (seq[1] == 'D')
		{
			if ((g_shell.curs > g_shell.len_prompt) && g_shell.curs--)
				write(1, "\x1b[D", 3);
		}
		else if (seq[1] == 'C')
		{
			start = g_shell.curs - g_shell.len_prompt;
			if ((start < g_shell.len_string) && g_shell.curs++)
				write(1, "\x1b[C", 3);
		}
	}
	return (1);
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
	//if (ft_memcmp(&g_shell.orig_termios, &g_shell.raw, sizeof(struct termios)))
		enable_raw_mode();
	while (1)
	{
		c = editor_read_key();
		if (c == '\r')
		{
			write(1, "\n\r", 2);
			/* while (i++ < g_shell.len_string)
				write(1, " ", 1); */
			write(1, "\r", 1);
			break;
		}
		if (!(ret = process_keypress(c)))
			return (0);
	}
	*input = ft_strdup(g_shell.final_string);
	return (1);
}
