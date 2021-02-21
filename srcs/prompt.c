#include "../include/minishell.h"

void	print_prompt(void)
{
	/* printf(BGBLK" %s@minishell"NC, (get_value_env("USER"))->value);
	printf(BGBLUE BLACK""NC);
	printf(BGBLUE BLACK"%s"NC, (get_value_env("PWD"))->value);
	printf(BLUE" "NC); */
	ft_putstr_fd(BGBLK" ", 1);
	ft_putstr_fd((get_value_env("USER"))->value, 1);
	ft_putstr_fd("@minishell"NC, 1);
	ft_putstr_fd(BGBLUE BLACK""NC, 1);
	ft_putstr_fd(BGBLUE BLACK, 1);
	ft_putstr_fd((get_value_env("PWD"))->value, 1);
	ft_putstr_fd(NC, 1);
	ft_putstr_fd(BLUE" "NC, 1);
}
