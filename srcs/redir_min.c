/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_min.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:11:14 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:29:26 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	child_process(int fd, char *path, char **args)
{
	int	wstatus;

	g_shell.pid = fork();
	if (g_shell.pid == 0)
	{
		dup2(fd, 0);
		while (fd > 2)
			close(fd--);
		execve(path, args, g_shell.envp_real);
		exit(0);
	}
	while (fd > 2)
		close(fd--);
	wait(&wstatus);
	errno = (wstatus == 3) ? 131 : wstatus;
	free(path);
	ft_free_arr(args);
}

static	int		open_descriptor(t_list *tmp)
{
	t_list	*ptr;
	int		cl;
	int		fd;

	while (tmp)
	{
		if (((char*)tmp->content)[0] == '<')
			ptr = tmp;
		else if (((char*)tmp->content)[0] == '|' ||
		((char*)tmp->content)[0] == '>')
			break ;
		else if ((fd = open(tmp->content, O_RDWR)) == -1)
		{
			cl = 3;
			while (close(cl) != -1)
				cl++;
			ft_putstr_fd("\x1b[31m \bminishell:", 2);
			ft_putstr_fd(((char*)tmp->content), 2);
			ft_putendl_fd(": No such file or directory \033[0m", 2);
			return (0);
		}
		tmp = tmp->next;
	}
	return (fd);
}

static	void	father_process(int fd, char **args, t_list *node)
{
	while (fd > 2)
		close(fd--);
	ft_free_arr(args);
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(((char*)node->content), 2);
	ft_putstr_fd(": command not found", 2);
	ft_putendl_fd(NC, 2);
}

void			redir_min(t_list *node, char *sign, int fd)
{
	t_list		*tmp;
	t_list		*finded;
	char		**args;
	int			j;
	char		*path;

	j = 0;
	tmp = node;
	if (check_error_syntax_redir(node, sign) == -1)
		return ;
	while (ft_memcmp((char*)tmp->content, sign, ft_strlen(sign) + 1))
		tmp = tmp->next;
	finded = tmp;
	if (!(fd = open_descriptor(tmp)))
		return ;
	args = ft_list_to_arr_delim(node, finded);
	path = get_path_command(node->content, &j);
	if (j == -1)
		child_process(fd, path, args);
	else
		father_process(fd, args, node);
}
