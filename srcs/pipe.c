#include "../include/minishell.h"

void	exec_pipe(int pip[][2], int j, int i)
{
	int k;
	int wstatus;

	k = 0;
	g_shell.pid = fork();
	if (g_shell.pid == 0)
	{
		dup2(pip[k][1], 1);
		while (j > 0)
		{
			j--;
			close(pip[j][0]);
			close(pip[j][1]);
		}
		if (find_redir(i) || find_command(i))
			;
		exit(0);
	}
	wait(&wstatus);
	errno = (wstatus == 3) ? 131 : wstatus;
	while (k < (j - 1))
	{
		ft_lstremove_if_until(&g_shell.table_list[i], "|", &ft_memcmp, 0);
		g_shell.pid = fork();
		if (g_shell.pid == 0)
		{
			dup2(pip[k][0], 0);
			k++;
			dup2(pip[k][1], 1);
			while (j > 0)
			{
				j--;
				close(pip[j][0]);
				close(pip[j][1]);
			}
			t_list *tmp;
			tmp = g_shell.table_list[i];
			while (((char*)tmp->next->content)[0] != '|')
				tmp = tmp->next;
			tmp->next = 0;
			if (find_redir(i) || find_command(i))
				;
			exit(0);
		}
		close(pip[k][0]);
		close(pip[k][1]);
		wait(&wstatus);
		errno = (wstatus == 3) ? 131 : wstatus;
		k++;
	}
	g_shell.pid = fork();
	if (g_shell.pid == 0)
	{
		close(pip[k][1]);
		dup2(pip[k][0], 0);
		close(pip[k][0]);
		ft_lstremove_if_until(&g_shell.table_list[i], "|", &ft_memcmp, 0);
		if (find_redir(i) || find_command(i))
			;
		exit(0);
	}
	close(pip[k][0]);
	close(pip[k][1]);
	wait(&wstatus);
	errno = (wstatus == 3) ? 131 : wstatus;
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
	errno = 0;
	cpy_content = (char*)g_shell.table_list[i]->content;
	tmp = g_shell.table_list[i];
	while (tmp)
	{
		if (((char*)tmp->content)[0] == '|')
			j++;
		tmp = tmp->next;
	}
	open_pipe(j, i);
	if (!(g_shell.table_list[i]))
	{
		printf(RED"invalid argument"NC"\n");
		return ;
	}
	g_shell.table_list[i]->content = cpy_content;
}
