#include "../include/minishell.h"

static	void	built_echo_option(int i, t_list *tmp, int *freeable)
{
	tmp = tmp->next->next;
	while (tmp)
	{
		built_dollar(i, (char**)&(tmp->content), freeable);
		ft_putstr_fd(((char*)tmp->content), 1);
		ft_putstr_fd(" ", 1);
		if (*freeable)
			free(tmp->content);
		tmp = tmp->next;
	}
	ft_putstr_fd("\b", 1);
}

void			built_echo(int i)
{
	t_list *tmp;
	int		freeable;

	freeable = 0;
	tmp = g_shell.table_list[i];
	if (tmp->next)
	{
		if (!ft_memcmp(tmp->next->content, "-n", 3))
			built_echo_option(i, tmp, &freeable);
		else
		{
			tmp = tmp->next;
			while (tmp)
			{
				built_dollar(i, (char**)&(tmp->content), &freeable);
				ft_putstr_fd(((char*)tmp->content), 1);
				ft_putstr_fd(" ", 1);
				if (freeable)
					free(tmp->content);
				tmp = tmp->next;
			}
			ft_putstr_fd("\b", 1);
			ft_putendl_fd("", 1);
		}
	}
	else
		printf("\n");
	errno = 0;
}
