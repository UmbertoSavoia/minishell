#include "../include/minishell.h"

void	navigate_history(int dir)
{
	int 			len;

	if (dir == UP && (g_shell.history->next || g_shell.history->content))
	{
			len = ft_strlen((char*)g_shell.history->content);
			write(1, ((char*)g_shell.history->content), len);
			g_shell.history = (g_shell.history->next) ? g_shell.history->next  : g_shell.history;
			return ;
	}
	else if (dir == DW)
	{
		len = ft_strlen((char*)g_shell.history->content);
		write(1, ((char*)g_shell.history->content), len);
		g_shell.history = (g_shell.history->prev) ? g_shell.history->prev : g_shell.history;
		return ;
	}
}
