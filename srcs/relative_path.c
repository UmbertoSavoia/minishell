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
	int				wstatus;
	int				status_code;

	pid = 0;
	tmp = ft_strrchr((char*)g_shell.table_list[i]->content, '/');
	len_path = tmp - (char*)g_shell.table_list[i]->content;
	path = malloc(len_path + 2);
	ft_memcpy(path, (char*)g_shell.table_list[i]->content, len_path);
	folder = opendir(path);
	while ((entry = readdir(folder)))
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
		wait(&wstatus);
		pid = fork();
		if (pid == 0)
		{
			args = ft_split(tmp, ' ');
			execve((char*)g_shell.table_list[i]->content, args, g_shell.envp_real);
			ft_free_arr(args);
			free(path);
			built_exit();
		}
		else
		{
			status_code = WEXITSTATUS(wstatus);
			if (status_code != 0)
				printf("\n[%d]\n", status_code);
		}
	}
	free(path);
}
