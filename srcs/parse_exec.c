#include "../include/minishell.h"

int		check_quote(char *line)
{
	int		i;
	int		j;

	i = 2;
	j = 2;
	while (*line)
	{
		if (*line == '\"' && (j & 1) == PARI)
			i++;
		if (*line == '\'' && (i & 1) == PARI)
			j++;
		line++;
	}
	return (!(i & 1) && !(j & 1));
}

void	exec_commands(void)
{
	int i;

	i = 0;
	while (g_shell.table_list[i])
	{
		if (find_redir(i) || find_builtin(i))
			;
		i++;
	}
}

void	parse_exec(void)
{
	char	*input;
	char	*tmp;
	int		i;

	i = 0;
	if (((get_next_line(0, &input)) < 0) && (g_shell.exit_code = EBADF))
		return ;
	if (!(check_quote(input)) && (g_shell.exit_code = 22))
	{
		free(input);
		return ;
	}
	g_shell.c_table = ft_split(input, ';');
	free(input);
	while (g_shell.c_table[i])
	{
		tmp = ft_strtrim(g_shell.c_table[i], " ");
		free(g_shell.c_table[i]);
		g_shell.c_table[i++] = tmp;
	}
	g_shell.table_list = ft_split_list(g_shell.c_table, ' ');
	free(g_shell.c_table);
	exec_commands();
}
