#include "../include/minishell.h"

void	built_unset(int i)
{
	t_list *tmp;

	tmp = g_shell.table_list[i]->next;
	if (!ft_isalpha(((char*)tmp->content)[0]))
	{
		(printf(RED"minishell: unset: '%s': not a valid identifier"NC"\n",
			(char*)tmp->content));
		return ;
	}
	while (tmp != 0)
	{
		if (((char*)tmp->content)[0] == '?')
			break ;
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
}
