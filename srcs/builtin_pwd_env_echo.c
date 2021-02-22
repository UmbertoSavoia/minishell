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

void	built_echo(i)
{
	t_list *tmp;

	tmp = g_shell.table_list[i];
	if (tmp->next)
	{
		if (((char*)tmp->next->content)[0] == '-' &&
			((char*)tmp->next->content)[1] == 'n')
		{
			tmp = tmp->next->next;
			while (tmp)
			{
				ft_putstr_fd(tmp->content, 1);
				ft_putstr_fd(" ", 1);
				tmp = tmp->next;
			}
			ft_putstr_fd("\b", 1);
		}
		else
		{
			tmp = tmp->next;
			while (tmp)
			{
				ft_putstr_fd(tmp->content, 1);
				ft_putstr_fd(" ", 1);
				tmp = tmp->next;
			}
			ft_putstr_fd("\b", 1);
			ft_putendl_fd("", 1);
		}
	}
}
