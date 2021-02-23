
#include "../include/minishell.h"

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
	else if (g_shell.table_list[i])
		if (chdir(g_shell.table_list[i]->next->content) < 0)
		{
			ft_putstr_fd(RED, 1);
			ft_putendl_fd(strerror(errno), 1);
			ft_putstr_fd(NC, 1);
			return ;
		}
	errno = 0;
}

void	built_exit(void)
{
	env_clear();
	clear_table_list();
	exit(0);
}