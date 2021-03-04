#include "../include/minishell.h"

void	relative_path(int i)
{
	char			*tmp;
	int				len_path;
	char			*path;
	int				finded;
	DIR				*folder;
	struct dirent	*entry;
	char			**args;
	int				wstatus;

	finded = 0;
	errno = 0;
	wstatus = 0;
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
			finded = 1;
			break ;
		}
	}
	closedir(folder);
	if (finded)
	{
		if ((g_shell.pid = fork()) == -1)
			return ;
		if (g_shell.pid == 0)
		{
			args = ft_list_to_arr(i);
			execve((char*)g_shell.table_list[i]->content, args, g_shell.envp_real);
			exit(0);
		}
		wait(&wstatus);
		if (WIFEXITED(wstatus))
			errno = (WEXITSTATUS(wstatus) == 0) ? 0 : 127;
	}
	free(path);
}
