#include "../include/minishell.h"

int		findexec(int i, int j, char *tmp2, char **tmp3)
{
	char			**path;
	DIR				*folder;
	size_t			len_command;
	struct dirent	*entry;
	char			*tmp;

	errno = 0;
	len_command = ft_strlen((char*)g_shell.table_list[i]->content) + 1;
	path = ft_split(get_value_env("PATH")->value, ':');
	while (path[j])
	{
		folder = opendir(path[j]);
		while ((entry = readdir(folder)))
		{
			if (!(ft_memcmp((char*)g_shell.table_list[i]->content, entry->d_name, len_command)))
			{
				tmp2 = ft_strjoin(path[j], "/");
				tmp = ft_strjoin(tmp2, (char*)g_shell.table_list[i]->content);
				j = -1;
				break ;
			}
		}
		closedir(folder);
		if (j == -1)
			break ;
		j++;
	}
	ft_free_arr(path);
	if ((j = -1) && tmp2)
	{
		path = ft_split(g_shell.table_list[i]->content, ' ');
		tmp3 = ft_list_to_arr(i);
		int id = fork();
		if (id == 0)
		{
			execve(tmp, tmp3, g_shell.envp_real);
			free(tmp);
			free(tmp2);
			ft_free_arr(path);
			ft_free_arr(tmp3);
			built_exit();
		}
		j = 0;
		wait(NULL);
		free(tmp);
		free(tmp2);
		ft_free_arr(path);
		ft_free_arr(tmp3);
	}
	return (j < 0 ? 0 : 1);
}
