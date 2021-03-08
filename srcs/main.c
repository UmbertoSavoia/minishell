/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:09:59 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:28:58 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_useless(int ac, char **av)
{
	(void)ac;
	(void)av;
}

int		main(int ac, char **av, char **env)
{
	ft_useless(ac, av);
	ft_bzero(&g_shell, sizeof(t_shell));
	init_env(env);
	init_hist();
	set_shlvl();
	while (!g_shell.exit_code)
	{
		if (g_shell.envp_real)
			ft_free_arr(g_shell.envp_real);
		g_shell.envp_real = ft_env_to_arr();
		g_shell.pid = 1;
		print_prompt();
		signal(SIGQUIT, ft_sigquit);
		signal(SIGINT, ft_sigint);
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
