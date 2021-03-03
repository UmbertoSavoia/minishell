#include "../include/minishell.h"

static	void	child_process(int fd, char *path, char **args)
{
	g_shell.pid = fork();
	if (g_shell.pid == 0)
	{
		dup2(fd, 0);
		while (fd > 2)
			close(fd--);
		execve(path, args, g_shell.envp_real);
		free(path);
		ft_free_arr(args);
		built_exit();
	}
	while (fd > 2)
		close(fd--);
	wait(NULL);
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
		else if ((fd = open(tmp->content, O_RDWR)) == -1)
		{
			cl = 3;
			while (close(cl) != -1)
				cl++;
			printf(RED"minishell: %s: No such file or directory"NC"\n",
			((char*)tmp->content));
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
	printf(RED"minishell: %s: command not found"NC"\n",
	((char*)node->content));
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
	path = get_path_command(node, &j);
	if (j == -1)
		child_process(fd, path, args);
	else
		father_process(fd, args, node);
}
