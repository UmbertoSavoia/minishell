#include "../include/minishell.h"

int		zero_to_space(int i)
{
	t_list	*tmp;
	char	*last;
	char	*begin;

	tmp = g_shell.table_list[i]->next;
	begin = g_shell.table_list[i]->next->content;
	while (tmp->next)
		tmp = tmp->next;
	last = tmp->content;
	while (*last)
		last++;
	while (begin != last)
	{
		if (!*begin)
			*begin = ' ';
		begin++;
	}
	return (1);
}

void	built_cd(int i)
{
	t_env	*home;

	home = get_value_env("HOME");
	if ((!g_shell.table_list[i]->next))
	{
		if (!home)
		{
			ft_putendl_fd(RED"cd : HOME not set"NC, 1);
			errno = 1;
			return ;
		}
		chdir(home->value);
		errno = 0;
	}
	else if (g_shell.table_list[i] && zero_to_space(i))
	{
		if (chdir(g_shell.table_list[i]->next->content) < 0)
		{
			ft_putstr_fd(RED, 1);
			ft_putendl_fd(strerror(errno), 1);
			ft_putstr_fd(NC, 1);
			return ;
		}
	}
	errno = 0;
}

void	built_exit(void)
{
	if (g_shell.envp)
		env_clear();
	if (g_shell.table_list)
		clear_table_list();
	ft_putendl_fd("exit", 1);
	exit(0);
}
