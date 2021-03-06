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
	int				len_cpy;

	if (!size)
		size = g_shell.hist_size;
	printf("[%d]\n", g_shell.hist_size);
	if (dir == UP && size >= 1)
	{
		printf("{%d}\n", size);
		//clean_prompt(len);
		len = ft_strlen((char*)g_shell.history->content);
		write(1, ((char*)g_shell.history->content), len);
		(g_shell.history->next) ? g_shell.history = g_shell.history->next : 0;
		(size != 1) ? size-- : 0;
		return ;
	}
	else if (dir == DW && size < g_shell.hist_size)
	{
		printf("(%d)\n", size);
		size++;
		(g_shell.history->prev) ? g_shell.history = g_shell.history->prev : 0;
		//clean_promp(len);
		len = ft_strlen((char*)g_shell.history->content);
		write(1, ((char*)g_shell.history->content), len);
		return ;
	}
	else if (size > g_shell.hist_size)
	{
		len_cpy = len;
		while (len--)
			write(1, "\b", 1);
		len = len_cpy;
		while (len_cpy--)
			write(1, " ", 1);
		len_cpy = len;
		while (len_cpy--)
			write(1, "\b", 1);
	}
}
