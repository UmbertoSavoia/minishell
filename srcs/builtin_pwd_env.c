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

void	built_env(void)
{
	t_env *tmp;

	tmp = g_shell.envp;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
