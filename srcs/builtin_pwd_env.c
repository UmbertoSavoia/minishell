#include "../include/minishell.h"

void	built_pwd(int i)
{
	char tmp[PATH_MAX];

	if (g_shell.table_list[i]->next != 0)
	{
		ft_putendl_fd(RED"pwd: too many arguments"NC, 1);
		errno = 1;
		return ;
	}
	getcwd(tmp, PATH_MAX);
	ft_putendl_fd(tmp, 1);
	errno = 0;
}

int		built_env(void)
{
	t_env *tmp;

	tmp = g_shell.envp;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	errno = 0;
	return (1);
}
