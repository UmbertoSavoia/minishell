#include "../include/minishell.h"

char	find_redir(int i)
{
	if ((list_search(g_shell.table_list[i], ">", &ft_memcmp)))
		printf("trovato >\n");
	else if ((list_search(g_shell.table_list[i], ">>", &ft_memcmp)))
		printf("trovato >>\n");
	else if ((list_search(g_shell.table_list[i], "|", &ft_memcmp)))
		printf("trovato |\n");
	else if ((list_search(g_shell.table_list[i], "<", &ft_memcmp)))
		printf("trovato <\n");
	else
		return (0);
	return (1);
}

char	find_builtin(int i)
{
	if ((var_search(g_shell.table_list[i], '$', &ft_strchr)))
		built_dollar(i, (char**)&(g_shell.table_list[i]->content));
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
	if (((char*)g_shell.table_list[i]->content)[0] == '$')
		return (0);
	if ((var_search(g_shell.table_list[i], '=', &ft_strchr)))
		add_var_list(i, 1);
	else if (findexec(i, 0, 0))
		return (1);
	else
	{
		printf(RED"minishell: %s: command not found"NC"\n",
			g_shell.table_list[i]->content);
		errno = 127;
		return (0);
	}
	return (1);
}
