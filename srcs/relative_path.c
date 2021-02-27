#include "../include/minishell.h"

void	relative_path(int i)
{
	char			*tmp;
	int				len_path;
	char			*path;
	int				pid;
	DIR				*folder;
	struct dirent	*entry;
	char			**args;

	pid = 0;
	errno = 0;
	tmp = ft_strrchr((char*)g_shell.table_list[i]->content, '/');
	len_path = tmp - (char*)g_shell.table_list[i]->content;
	path = malloc(len_path + 2);
	ft_memcpy(path, (char*)g_shell.table_list[i]->content, len_path);
	path[len_path] = 0;
	if (!(folder = opendir(path)))
	{
		printf(RED"minishell: %s%s: No such file or directory"NC"\n", path, tmp);
		free(path);
		return ;
	}
	while ((entry = readdir(folder)) && errno == 0)
	{
		if (!(ft_memcmp(tmp + 1, entry->d_name, ft_strlen(tmp + 1))))
		{
			pid = 1;
			break ;
		}
	}
	closedir(folder);
	if (pid)
	{
		if ((pid = fork()) == -1)
			return ;
		wait(NULL);
		if (pid == 0)
		{
			args = ft_split(tmp, ' ');
			execve((char*)g_shell.table_list[i]->content, args, g_shell.envp_real);
			ft_free_arr(args);
			free(path);
			built_exit();
		}
	}
	free(path);
}
