#include "../include/minishell.h"

void	exec_commands(void)
{
	int		i;
	int		unused;
	t_env	*tmp;

	i = 0;
	unused = 0;
	while (g_shell.table_list[i])
	{
		tmp = get_value_env("?");
		free(tmp->value);
		tmp->value = ft_itoa(errno);
		if (find_redir(i) || find_builtin(i, &unused) || find_command(i))
			;
		i++;
	}
}

void	parse_exec(void)
{
	char	*input;
	char	*tmp;
	int		i;

	if (((i = get_next_line(0, &input))) < 0)
	{
		g_shell.exit_code = EBADF;
		return ;
	}
	if (i == 0)
		built_exit();
	if ((!(check_quote(input)) && (g_shell.exit_code = 22)) && ft_free(input))
		return ;
	g_shell.c_table = ft_split(input, ';');
	free(input);
	i = 0;
	while (g_shell.c_table[i])
	{
		tmp = ft_strtrim(g_shell.c_table[i], " ");
		free(g_shell.c_table[i]);
		g_shell.c_table[i++] = tmp;
	}
	i = 0;
	while (g_shell.c_table[i])
	{
		skip_quote(g_shell.c_table[i]);
		i++;
	}
	g_shell.table_list = ft_split_list(g_shell.c_table, ' ');
	free(g_shell.c_table);
	exec_commands();
}
