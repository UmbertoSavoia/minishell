#include "../include/minishell.h"

void	ft_sigint(int sig)
{
	if (sig != SIGINT)
		return ;
	else if (g_shell.pid != 0)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		ft_putchar_fd('\n', 1);
		errno = 1;
		print_prompt();
	}
}

void	ft_sigquit(int sig)
{
	if (sig != SIGQUIT)
		return ;
	if (g_shell.pid != 0)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		errno = 131;
	}
}

void	ft_sigint_2(int sig)
{
	if (sig != SIGINT)
		return ;
	if (g_shell.pid != 0)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		errno = 1;
	}
}
