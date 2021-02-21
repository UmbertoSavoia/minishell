#include "../include/minishell.h"

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	init_env(env);
	while (g_shell.envp)
	{
		printf("[key] = %s \n [value] = %s\n", g_shell.envp->key, "cc"/* g_shell.envp->value */);
		g_shell.envp = g_shell.envp->next;
	}
}
