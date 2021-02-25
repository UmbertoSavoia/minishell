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
		built_dollar(i, g_shell.table_list[i]->content);
	else if ((list_search(g_shell.table_list[i], "echo", &ft_memcmp)))
		built_echo(i);
	else if ((list_search(g_shell.table_list[i], "pwd", &ft_memcmp)))
		built_pwd(i);
	else if ((list_search(g_shell.table_list[i], "cd", &ft_memcmp)))
		built_cd(i);
	else if ((list_search(g_shell.table_list[i], "export", &ft_memcmp)))
		built_export(i);
	else if ((list_search(g_shell.table_list[i], "unset", &ft_memcmp)))
		built_unset(i);
	else if ((list_search(g_shell.table_list[i], "env", &ft_memcmp)))
		built_env();
	else if ((list_search(g_shell.table_list[i], "set", &ft_memcmp)))
		built_set();
	else if ((list_search(g_shell.table_list[i], "exit", &ft_memcmp)))
		built_exit();
	else
		return(0);
	return (1);
}

char	find_command(int i)
{
	if ((var_search(g_shell.table_list[i], '=', &ft_strchr)))
		add_var_list(i, 1);
	else
	{
		printf(RED"minishell: %s: command not found\n"NC,
			g_shell.table_list[i]->content);
		return (0);
	}
	return (1);
}