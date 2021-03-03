#include "../include/minishell.h"

void	exec_pipe(int pip[][2], int j, int i)
{
	int k;

	k = 0;
	g_shell.pid = fork();
	wait(NULL);
	if (g_shell.pid == 0)
	{
			close(pip[k][0]);
			dup2(pip[k][1], 1);
			close(pip[k][1]);
			if (find_redir(i) || find_command(i))
				;
		ft_lstremove_if_until(&g_shell.table_list[i], "|", &ft_memcmp, 0);
		while (k < (j - 1))
		{
			k++;
		}
		exit(0);
	}
	g_shell.pid = fork();
	if (g_shell.pid == 0)
	{
		close(pip[k][1]);
		dup2(pip[k][0], 0);
		close(pip[k][0]);
		while (j--)
			ft_lstremove_if_until(&g_shell.table_list[i], "|", &ft_memcmp, 0);
		if (find_redir(i) || find_command(i))
			;
		exit(0);
	}
	while (k >= 0)
	{
		close(pip[k][0]);
		close(pip[k][1]);
		k--;
	}
	wait(NULL);
	ft_lstremove_if_until(&g_shell.table_list[i], "|", &ft_memcmp, 0);
}

void	open_pipe(int j, int i)
{
	int pip[j][2];
	int k;

	k = 0;
	while (k < j)
	{
		pipe(pip[k]);
		k++;
	}
	exec_pipe(pip, j, i);
}

void	built_pipe(int i)
{
	t_list	*tmp;
	char	*cpy_content;
	int		j;

	j = 0;
	cpy_content = (char*)g_shell.table_list[i]->content;
	tmp = g_shell.table_list[i];
	while (tmp)
	{
		if (((char*)tmp->content)[0] == '|')
			j++;
		tmp = tmp->next;
	}
	open_pipe(j, i);
	g_shell.table_list[i]->content = cpy_content;
}
