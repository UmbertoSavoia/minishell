#include "../include/minishell.h"

static	void	echo_print(int true_i, char *s)
{
	static char k;
	static char	v;
	char		j;
	char		ret;
	int			i[2];

	i[0] = 0;
	i[1] = 0;
	j = 0;
	if (!v)
		v = 1;
	ret = 0;
	while (s[i[0]])
	{
		if ((true_i != -1 && ((s[0] == '\"' && s[1] == '$') || s[0] == '$')) && j !=5 )
		{
			i[1] = 1;
			built_dollar(true_i, &s);
			i[0]--;
			j = 0;
		}
		else
			j = 5;
		ret += echo_chaos_handler(&k, &v, &i[0], s);
		i[0]++;
	}
	if (!ret && (!((ft_strlen(s) == 1) && (*s == '\'' || *s == '\"' )) || v == 1))
		ft_putstr_fd(s, 1);
	(i[1] == 1) ? ft_free(s) : 0;
	ft_putstr_fd(" ", 1);
}

static	void	built_echo_option(int i, t_list *tmp)
{
	tmp = tmp->next->next;
	while (tmp)
	{
		if ((((char*)tmp->content)[0] == '\"' && ((char*)tmp->content)[1] == '$')
			|| ((char*)tmp->content)[0] == '$')
			built_dollar(i, (char**)&(tmp->content));
		echo_print(-1, tmp->content);
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
			built_echo_option(i, tmp);
		else
		{
			tmp = tmp->next;
			while (tmp)
			{
				echo_print(i, tmp->content);
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
