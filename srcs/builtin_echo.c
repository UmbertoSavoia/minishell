#include "../include/minishell.h"

static	void	echo_print(char *s)
{
	static char k;
	static char	v;
	char		ret;
	int			i;

	i = 0;
	if (!v)
		v = 1;
	ret = 0;
	while (s[i])
	{
		ret += echo_chaos_handler(&k, &v, &i, s);
		i++;
	}
	if (!ret && ((ft_strlen(s) != 1) || v == 1))
		ft_putstr_fd(s, 1);
	ft_putstr_fd(" ", 1);
}

static	void	built_echo_option(t_list *tmp)
{
	tmp = tmp->next->next;
	while (tmp)
	{
		echo_print(tmp->content);
		tmp = tmp->next;
	}
	ft_putstr_fd("\b", 1);
}

void			built_echo(int i)
{
	t_list *tmp;

	tmp = g_shell.table_list[i];
	if (tmp->next)
	{
		if (!ft_memcmp(tmp->next->content, "-n", 3))
		{
			built_echo_option(tmp);
		}
		else
		{
			tmp = tmp->next;
			while (tmp)
			{
				echo_print(tmp->content);
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
