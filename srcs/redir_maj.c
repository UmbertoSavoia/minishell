#include "../include/minishell.h"

char	**ft_list_to_arr_delim(t_list *start, t_list *end)
{
	int		j;
	int		len_list;
	char	**ret;
	t_list	*tmp;

	j = 0;
	tmp = start;
	len_list = 0;
	while (tmp != end)
	{
		len_list++;
		tmp = tmp->next;
	}
	ret = malloc(len_list * sizeof(char**) + 1);
	tmp = start;
	while (tmp != end)
	{
		ret[j] = ft_strdup(tmp->content);
		tmp = tmp->next;
		j++;
	}
	ret[j] = 0;
	return (ret);
}

int		check_error_syntax_redir(t_list *node, char *sign)
{
	t_list		*tmp;

	tmp = node;
	while (tmp)
	{
		if (tmp->next &&
			!(ft_memcmp((char*)tmp->content, sign, ft_strlen(sign) + 1)) &&
			!(ft_memcmp((char*)tmp->next->content, sign, ft_strlen(sign) + 1)))
		{
			ft_putstr_fd(RED, 1);
			ft_putstr_fd("minishell: syntax error near unexpected token ", 1);
			ft_putstr_fd(sign, 1);
			ft_putstr_fd(NC, 1);
			ft_putstr_fd("\n", 1);
			errno = 1;
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	redir_maj(t_list *node, char *sign, int flag)
{
	t_list		*tmp;
	t_list		*finded;
	int			fd;
	char		**args;
	char		*path;
	int			j;

	errno = 0;
	j = 0;
	tmp = node;
	fd = 20;
	if (check_error_syntax_redir(node, sign) == -1)
		return ;
	while (ft_memcmp((char*)tmp->content, sign, ft_strlen(sign) + 1))
		tmp = tmp->next;
	finded = tmp;
	while (tmp)
	{
		if (ft_memcmp((char*)tmp->content, sign, ft_strlen(sign) + 1))
			fd = open(tmp->content, O_CREAT | O_RDWR | flag, 0666);
		tmp = tmp->next;
	}
	args = ft_list_to_arr_delim(node, finded);
	path = get_path_command(node, &j);
	if (j == -1)
	{
		g_shell.pid = fork();
		if (g_shell.pid == 0)
		{
			dup2(fd, 1);
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
