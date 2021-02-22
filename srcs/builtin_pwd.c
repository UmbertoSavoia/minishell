#include "../include/minishell.h"

void	built_pwd(int i)
{
	t_env *tmp;

	if (g_shell.table_list[i]->next != 0)
	{
		ft_putendl_fd(RED"pwd: too many arguments"NC, 1);
		errno = 1;
		return ;
	}
	tmp = get_value_env("PWD");
	ft_putendl_fd(tmp->value, 1);
}
