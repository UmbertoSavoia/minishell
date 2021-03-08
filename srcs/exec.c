/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:08:40 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:28:28 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_t_path(t_path *p, char *node)
{
	p->j = -1;
	p->lc = ft_strlen(node) + 1;
}

char	*get_path_command(char *node, int *found)
{
	t_path		p;

	init_t_path(&p, node);
	if (((node)[0] == '.' || (node)[0] == '/') && (*found = -1))
		return ((p.ret = ft_strdup(node)));
	p.path = ft_split((GVE("PATH") ? GVE("PATH")->value : 0), ':');
	while (p.path[++p.j])
	{
		p.folder = opendir(p.path[p.j]);
		while ((p.entry = readdir(p.folder)))
		{
			if (!(ft_memcmp(node, p.entry->d_name, p.lc)))
			{
				p.tmp2 = ft_strjoin(p.path[p.j], "/");
				p.ret = ft_strjoin(p.tmp2, node);
				*found = -2 + ft_free(p.tmp2);
				break ;
			}
		}
		closedir(p.folder);
		if (*found == -1)
			break ;
	}
	ft_free_arr(p.path);
	return (p.ret);
}

void	child_find_exec(char *path, char **tmp3)
{
	if ((execve(path, tmp3, g_shell.envp_real)) == -1)
	{
		printf(RED"minishell: %s: No file or directory"NC"\n", path);
		exit(1);
	}
	exit(0);
}

int		findexec(int i)
{
	char			*path;
	int				j;
	char			**tmp3;
	int				freeable;
	int				wstatus;

	j = 0;
	errno = 0;
	freeable = 0;
	path = get_path_command(g_shell.table_list[i]->content, &j);
	if (j == -1)
	{
		if (g_shell.table_list[i]->next &&
			ft_strchr(((char*)g_shell.table_list[i]->next->content), '$'))
			built_dollar(i, (char**)&(GNC), &freeable);
		tmp3 = ft_list_to_arr(i);
		g_shell.pid = fork();
		if (g_shell.pid == 0)
			child_find_exec(path, tmp3);
		wait(&wstatus);
		errno = (wstatus == 3) ? 131 : wstatus;
		if (ft_free(path) && ft_free_arr(tmp3) && freeable)
			free(g_shell.table_list[i]->next->content);
	}
	return (j >= 0 ? 0 : 1);
}
