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

}

void	parse_exec(void)
{
	char	*input;
	char	*tmp;
	int		i;

	i = 0;
	if ((get_next_line(0, &input)) < 0)
	{
		g_shell.exit_code = EBADF;
		return ;
	}
	if (!(check_quote(input)))
	{
		free(input);
		g_shell.exit_code = 22;
	}
	g_shell.c_table = ft_split(input, ';');
	while (g_shell.c_table[i])
	{
		tmp = g_shell.c_table[i];
		g_shell.c_table[i] = ft_strtrim(g_shell.c_table[i], " ");
		free(tmp);
		i++;
	}
}
