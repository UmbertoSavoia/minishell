#include "../include/minishell.h"

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_bzero(&g_shell, sizeof(t_shell));
	init_env(env);
	set_shlvl();
	while (!g_shell.exit_code)
	{
		signal(SIGQUIT, ft_sigquit);
		signal(SIGINT, ft_sigint);
		print_prompt();
		parse_exec();
		if (g_shell.table_list)
			clear_table_list();
		g_shell.table_list = 0;
	}
	env_clear();
	printf(RED"\n%s\n"NC, strerror(g_shell.exit_code));
	return (g_shell.exit_code);
}
