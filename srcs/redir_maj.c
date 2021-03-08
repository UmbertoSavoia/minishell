/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_maj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:11:06 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:29:22 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char			**ft_list_to_arr_delim(t_list *start, t_list *end)
{
	int		j;
	char	**ret;
	t_list	*tmp;
	char	*tmp_content;

	tmp_content = start->content;
	j = 0;
	if (((char*)start->content)[0] == '.' || ((char*)start->content)[0] == '/')
		start->content = ft_strrchr((char*)start->content, '/') + 1;
	tmp = start;
	calc_size(tmp, end, &j);
	ret = malloc(j * sizeof(char**) + 1);
	tmp = start;
	j = 0;
	while (tmp != end)
	{
		ret[j] = ft_strdup(tmp->content);
		tmp = tmp->next;
		j++;
	}
	ret[j] = 0;
	start->content = tmp_content;
	return (ret);
}

int				check_error_syntax_redir(t_list *node, char *sign)
{
	t_list		*tmp;

	tmp = node;
	while (tmp)
	{
		if (tmp->next &&
			!(ft_memcmp((char*)tmp->content, sign, ft_strlen(sign) + 1)) &&
			!(ft_memcmp((char*)tmp->next->content, sign, ft_strlen(sign) + 1)))
		{
			ft_putstr_fd(RED, 2);
			ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
			ft_putstr_fd(sign, 2);
			ft_putendl_fd(NC, 2);
			errno = 1;
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static	void	child_process(int fd, char *path, char **args)
{
	int		wstatus;

	g_shell.pid = fork();
	if (g_shell.pid == 0)
	{
		dup2(fd, 1);
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

void			redir_maj(t_list *node, char *sign, int flag, int fd)
{
	t_list		*tmp;
	t_list		*finded;
	char		**args;
	char		*path;
	int			j;

	j = 0;
	tmp = node;
	if (check_error_syntax_redir(node, sign) == -1)
		return ;
	while (ft_memcmp((char*)tmp->content, sign, ft_strlen(sign) + 1))
		tmp = tmp->next;
	finded = tmp;
	while (tmp)
	{
		if (((char*)tmp->content)[0] == '|')
			break ;
		else if (ft_memcmp((char*)tmp->content, sign, ft_strlen(sign) + 1))
			fd = open(tmp->content, O_CREAT | O_RDWR | flag, 0666);
		tmp = tmp->next;
	}
	args = ft_list_to_arr_delim(node, finded);
	path = get_path_command(node->content, &j);
	(j == -1) ? child_process(fd, path, args) : father_process(fd, args, node);
}
