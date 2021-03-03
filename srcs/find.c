#include "../include/minishell.h"

char	find_redir(int i)
{
	if ((list_search(g_shell.table_list[i], "|", &ft_memcmp)))
		printf("trovato |\n");
	else if ((list_search(g_shell.table_list[i], ">", &ft_memcmp)))
		redir_maj(g_shell.table_list[i], ">", O_TRUNC, 0);
	else if ((list_search(g_shell.table_list[i], ">>", &ft_memcmp)))
	{
		errno = 0;
		redir_maj(g_shell.table_list[i], ">>", O_APPEND, 0);
	}
	else if ((list_search(g_shell.table_list[i], "<", &ft_memcmp)))
		redir_min(g_shell.table_list[i], "<", 0);
	else
		return (0);
	return (1);
}

char	find_builtin(int i, int *unused)
{
	if ((var_search(g_shell.table_list[i], '$', &ft_strchr)))
		built_dollar(i, (char**)&(g_shell.table_list[i]->content), unused);
	if ((list_search(g_shell.table_list[i], "echo", &ft_memcmp)))
		built_echo(i);
	else if ((list_search(g_shell.table_list[i], "pwd", &ft_memcmp)))
		built_pwd();
	else if ((list_search(g_shell.table_list[i], "cd", &ft_memcmp)))
		built_cd(i);
	else if ((list_search(g_shell.table_list[i], "export", &ft_memcmp)))
		built_export(i);
	else if ((list_search(g_shell.table_list[i], "unset", &ft_memcmp)))
		built_unset(i);
	else if ((list_search(g_shell.table_list[i], "env", &ft_memcmp)))
		built_env(i);
	else if ((list_search(g_shell.table_list[i], "set", &ft_memcmp)))
		built_set();
	else if ((list_search(g_shell.table_list[i], "exit", &ft_memcmp)))
		built_exit();
	else
		return (0);
	return (1);
}

char	find_command(int i)
{
	if ((var_search(g_shell.table_list[i], '=', &ft_strchr)))
		add_var_list(i, 1);
	else if (findexec(i))
		return (1);
	else if ((relative_search(g_shell.table_list[i], "./", &ft_memcmp)))
		relative_path(i);
	else
	{
		printf(RED"minishell: %s: command not found"NC"\n",
			((char*)g_shell.table_list[i]->content));
		errno = 127;
		return (0);
	}
	return (1);
}
