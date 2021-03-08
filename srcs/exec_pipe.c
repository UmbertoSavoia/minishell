/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromalde <cromalde@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:08:31 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 16:26:52 by cromalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_pipe(int pip[][2], int j, int i)
{
	int k;
	int wstatus;
	t_list	*tmp;

	k = 0;
	g_shell.pid = fork();
	if (g_shell.pid == 0)
	{
		dup2(pip[k][1], 1);
		pipe_close(j, pip);
		tmp = g_shell.table_list[i];
		while (((char*)tmp->next->content)[0] != '|')
			tmp = tmp->next;
		tmp->next = 0;
		if (find_redir(i) || find_command(i))
			;
		exit(0);
	}
	wait(&wstatus);
	errno = (wstatus == 3) ? 131 : wstatus;
	multi_pipe_cicle(&k, j, pip, i);
	g_shell.pid = fork();
	if (g_shell.pid == 0)
		do_last_command(pip, k, i);
	close(pip[k][0]);
	close(pip[k][1]);
	wait(&wstatus);
	errno = (wstatus == 3) ? 131 : wstatus;
	ft_lstremove_if_until(&g_shell.table_list[i], "|", &ft_memcmp, 0);
}
