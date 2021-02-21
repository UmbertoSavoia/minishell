#include "../include/minishell.h"

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
	g_shell.c_table = ft_split(input, ';');
	while (g_shell.c_table[i])
	{
		tmp = g_shell.c_table[i];
		g_shell.c_table[i] = ft_strtrim(g_shell.c_table[i], " ");
		free(tmp);
		i++;
	}
}
