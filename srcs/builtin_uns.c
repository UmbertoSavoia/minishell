#include "../include/minishell.h"

void	built_unset(int i)
{
	t_list *tmp;

	tmp = g_shell.table_list[i]->next;
	while (tmp != 0)
	{
		if (g_shell.envp)
			remove_t_env(&g_shell.envp,
				tmp->content, &ft_memcmp, &free);
		if (g_shell.var_list)
			remove_t_env(&g_shell.var_list,
				tmp->content, &ft_memcmp, &free);
		errno = 0;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	ft_putendl_fd(RED"unset: not enough arguments"NC, 1);
	errno = 1;
}
