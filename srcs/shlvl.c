
#include "../include/minishell.h"

void	set_shlvl(void)
{
	t_env	*tmp;
	int		num;

	tmp = get_value_env("SHLVL");
	num = ft_atoi(tmp->value) + 1;
	free(tmp->value);
	tmp->value = ft_itoa(num);
}
