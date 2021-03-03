#include "../include/minishell.h"

void	redir_min(t_list *node, char *sign)
{
	t_list		*tmp;
	t_list		*ptr;
	t_list		*finded;
	char		**args;
	int			fd;
	int			j;
	char		*path;

	j = 0;
	tmp = node;
	if (check_error_syntax_redir(node, sign) == -1)
		return ;
	while (ft_memcmp((char*)tmp->content, sign, ft_strlen(sign) + 1))
		tmp = tmp->next;
	finded = tmp;
	while (tmp)
	{
		if (((char*)tmp->content)[0] == '<')
			ptr = tmp;
		else if ((fd = open(tmp->content, O_RDWR)) == -1)
		{
			int cl = 3;
			while (close(cl) != -1)
				cl++;
			printf(RED"minishell: %s: No such file or directory"NC"\n", ((char*)tmp->content));
			return ;
		}
		tmp = tmp->next;
	}
	args = ft_list_to_arr_delim(node, finded);
	path = get_path_command(node, &j);
	if (j == -1)
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
	else
	{
		while (fd > 2)
			close(fd--);
		ft_free_arr(args);
		printf(RED"minishell: %s: command not found"NC"\n", ((char*)node->content));
	}
}
