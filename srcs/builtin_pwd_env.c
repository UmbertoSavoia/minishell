#include "../include/minishell.h"

void	built_pwd(void)
{
	char tmp[PATH_MAX];

	getcwd(tmp, PATH_MAX);
	ft_putendl_fd(tmp, 1);
	errno = 0;
}

int		built_env(int i)
{
	t_env *tmp;

	tmp = g_shell.envp;
	if (g_shell.table_list[i]->next != 0)
	{
		ft_putendl_fd(RED"env: too many arguments"NC, 1);
		errno = 1;
		return (0);
	}
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	errno = 0;
	return (1);
}
