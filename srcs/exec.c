#include "../include/minishell.h"

int		findexec(int i, int j, char *tmp2, char **tmp3)
{
	char			**path;
	DIR				*folder;
	size_t			len_command;
	struct dirent	*entry;
	char			*tmp;

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
		if (j == -1)
			break ;
		j++;
	}
	closedir(folder);
	tmp3 = ft_list_to_arr(i);
	ft_free_arr(path);
	path = ft_split(g_shell.table_list[i]->content, ' ');
	int id = fork();
	if (id == 0)
	{
		execve(tmp, tmp3, g_shell.envp_real);
		free(tmp);
		free(tmp2);
		ft_free_arr(path);
		built_exit();
	}
	wait(NULL);
	free(tmp);
	free(tmp2);
	ft_free_arr(path);
	//return (j < 0 ? 0 : 1);
	return (1);
}
