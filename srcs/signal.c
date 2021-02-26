#include "../include/minishell.h"

void	ft_sigquit(int sig)
{
	int i;

	i = 0;
	if (sig != SIGQUIT)
		return ;
	printf(RED"\nSigquit\n\a"NC);
	if (g_shell.envp)
		env_clear(g_shell.envp);
	if (g_shell.var_list)
		env_clear(g_shell.var_list);
	if (g_shell.table_list)
		clear_table_list();
	exit(0);
}

void	ft_sigint(int sig)
{
	int i;

	i = 0;
	if (sig != SIGINT)
		return ;
	printf(RED"\nSigint\n\a"NC);
	if (g_shell.envp)
		env_clear(g_shell.envp);
	if (g_shell.var_list)
		env_clear(g_shell.var_list);
	if (g_shell.table_list)
		clear_table_list();
	exit(0);
}
