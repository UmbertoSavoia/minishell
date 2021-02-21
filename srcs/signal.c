#include "../include/minishell.h"

void	ft_sigquit(int sig)
{
	if (sig != SIGQUIT)
		return ;
	printf(RED"\rSigquit\n\a"NC);
	env_clear();
	exit(0);
}

void	ft_sigint(int sig)
{
	if (sig != SIGINT)
		return ;
	printf(RED"\rSigint\n\a"NC);
	env_clear();
	exit(0);
}
