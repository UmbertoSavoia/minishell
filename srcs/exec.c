#include "../include/minishell.h"

char	*get_path_command(t_list *node, int *found)
{
	char			**path;
	DIR				*folder;
	size_t			len_command;
	struct dirent	*entry;
	int				j;
	char			*tmp2;
	char			*ret;

	j = 0;
	len_command = ft_strlen((char*)node->content) + 1;
	path = ft_split(get_value_env("PATH")->value, ':');
	while (path[j])
	{
		folder = opendir(path[j]);
		while ((entry = readdir(folder)))
		{
			if (!(ft_memcmp((char*)node->content, entry->d_name, len_command)))
			{
				tmp2 = ft_strjoin(path[j], "/");
				ret = ft_strjoin(tmp2, (char*)node->content);
				*found = -1;
				free(tmp2);
				break ;
			}
		}
		closedir(folder);
		if (*found == -1)
			break ;
		j++;
	}
	ft_free_arr(path);
	return (ret);
}

int		findexec(int i)
{
	char			*path;
	int				j;
	char			**tmp3;

	j = 0;
	errno = 0;
	path = get_path_command(g_shell.table_list[i], &j);
	if (j == -1)
	{
		tmp3 = ft_list_to_arr(i);
		g_shell.pid = fork();
		if (g_shell.pid == 0)
		{
			execve(path, tmp3, g_shell.envp_real);
			free(path);
 			ft_free_arr(tmp3);
 			built_exit(i);
 		}
		wait(NULL);
		free(path);
		ft_free_arr(tmp3);
	}
	return (j >= 0 ? 0 : 1);
}
