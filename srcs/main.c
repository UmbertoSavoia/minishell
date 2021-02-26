#include "../include/minishell.h"

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_bzero(&g_shell, sizeof(t_shell));
	g_shell.envp_real = env;
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
	env_clear(g_shell.envp);
	env_clear(g_shell.var_list);
	if ((g_shell.exit_code > 0) && ft_free(g_shell.user))
		printf(RED"\n%s"NC, strerror(g_shell.exit_code));
	write(1, "\n", 1);
	return (g_shell.exit_code);
}
