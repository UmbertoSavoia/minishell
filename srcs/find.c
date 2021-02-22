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
	if ((list_search(g_shell.table_list[i], "echo", &ft_memcmp)))
		printf("trovato echo\n");
	else if ((list_search(g_shell.table_list[i], "pwd", &ft_memcmp)))
		printf("trovato pwd\n");
	else if ((list_search(g_shell.table_list[i], "cd", &ft_memcmp)))
		printf("trovato cd\n");
	else if ((list_search(g_shell.table_list[i], "export", &ft_memcmp)))
		printf("trovato export\n");
	else if ((list_search(g_shell.table_list[i], "unset", &ft_memcmp)))
		printf("trovato unset\n");
	else if ((list_search(g_shell.table_list[i], "env", &ft_memcmp)))
		printf("trovato env\n");
	else if ((list_search(g_shell.table_list[i], "exit", &ft_memcmp)))
		printf("trovato exit\n");
	else
		return (0);
	return (1);
}

char	find_dollar(int i)
{
	i = 0;
	return 1;
}
