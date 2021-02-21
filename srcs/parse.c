#include "../include/minishell.h"

void	parse(void)
{
	char	*input;

	if ((get_next_line(0, &input)) <= 0)
		g_shell.exit_code = EBADF;

}
