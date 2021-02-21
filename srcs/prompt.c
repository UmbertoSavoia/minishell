#include "../include/minishell.h"

void	print_prompt(void)
{
	printf(BGBLK" %s@minishell"NC, (get_value_env("USER"))->value);
	printf(BGBLUE BLACK""NC);
	printf(BGBLUE BLACK"%s"NC, (get_value_env("PWD"))->value);
	printf(BLUE""NC);
}
