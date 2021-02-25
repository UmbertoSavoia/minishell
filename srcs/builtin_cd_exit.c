#include "../include/minishell.h"

int		zero_to_space(int i, char c)
{
	t_list	*tmp;
	char	*last;
	char	*begin;

	tmp = g_shell.table_list[i]->next;
	begin = g_shell.table_list[i]->next->content;
	if (*begin == '\'' || *begin == '\"')
	{
		c = *begin++;
		g_shell.table_list[i]->next->content++;
	}
	while (tmp->next)
		tmp = tmp->next;
	last = tmp->content;
	while (*last)
		last++;
	while (begin != last)
		if (!*begin++)
			*(--begin) = ' ';
	if (c)
		while (*last != c)
			last--;
	*last = 0;
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
	else if (g_shell.table_list[i] && zero_to_space(i, 0))
	{
		if (chdir(g_shell.table_list[i]->next->content) < 0)
		{
			printf(RED"cd: %s: %s\n"NC,
				g_shell.table_list[i]->next->content, strerror(errno));
			return ;
		}
	}
	errno = 0;
}

void	built_exit(void)
{
	int i;

	i = 0;
	if (g_shell.envp)
		env_clear(g_shell.envp);
	if (g_shell.table_list)
		clear_table_list();
	if (g_shell.var_list)
		env_clear(g_shell.var_list);
	free(g_shell.user);
	if (g_shell.st_t_list)
		while (g_shell.st_t_list[i])
			free(g_shell.st_t_list[i++]);
	free(g_shell.st_t_list);
	ft_putendl_fd("exit", 1);
	exit(0);
}
