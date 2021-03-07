#include "../include/minishell.h"

void	init_hist(void)
{
	g_shell.history = malloc(sizeof(t_hist) + 1);
	g_shell.history->content = ft_strdup("\a");
	g_shell.history->next = 0;
	g_shell.history->prev = 0;
	g_shell.hist_size = 1;
}

void	navigate_history(int dir)
{
	static int		len;
	static int		size;

	if (!size)
		size = g_shell.hist_size;
	if (dir == UP && size >= 1)
	{
		write(1, "\x1b[1K", 4);
		write(1, "\r", 1);
		print_prompt();
		len = ft_strlen((char*)g_shell.history->content);
		ft_memcpy(g_shell.final_string, g_shell.history->content, len);
		g_shell.len_string = len;
		g_shell.curs += len;
		write(1, ((char*)g_shell.history->content), len);
		(g_shell.history->next) ? g_shell.history = g_shell.history->next : 0;
		(size != 1) ? size-- : 0;
		return ;
	}
	else if (dir == DW && size < g_shell.hist_size && len)
	{
		size++;
		(g_shell.history->prev) ? g_shell.history = g_shell.history->prev : 0;
		(g_shell.history->prev) ? g_shell.history = g_shell.history->prev : 0;
		write(1, "\x1b[1K", 4);
		write(1, "\r", 1);
		print_prompt();
		len = ft_strlen((char*)g_shell.history->content);
		ft_memcpy(g_shell.final_string, g_shell.history->content, len);
		g_shell.len_string = len;
		g_shell.curs += len;
		write(1, ((char*)g_shell.history->content), len);
		return ;
	}
	else if (size >= g_shell.hist_size)
	{
		write(1, "\x1b[1K", 4);
		write(1, "\r", 1);
		print_prompt();
	}
}
