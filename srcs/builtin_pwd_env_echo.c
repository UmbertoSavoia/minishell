#include "../include/minishell.h"

void	built_pwd(int i)
{
	char tmp[PATH_MAX];

	if (g_shell.table_list[i]->next != 0)
	{
		ft_putendl_fd(RED"pwd: too many arguments"NC, 1);
		errno = 1;
		return ;
	}
	getcwd(tmp, PATH_MAX);
	ft_putendl_fd(tmp, 1);
	errno = 0;
}

void	built_env(void)
{
	t_env *tmp;

	tmp = g_shell.envp;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	errno = 0;
}

void	echo_print(char *s)
{
	static char k;
	static char	v;
	char		ret;
	int			i;

	i = 0;
	v = 1;
	k = 0;
	ret = 0;
	while (s[i])
	{
		ret += echo_chaos_handler(&k, &v, &i, s);
		i++;
	}
	if (!ret)
		ft_putstr_fd(s, 1);
	ft_putstr_fd(" ", 1);
}

void	built_echo_option(t_list *tmp)
{
	tmp = tmp->next->next;
	while (tmp)
	{
		echo_print(tmp->content);
		tmp = tmp->next;
	}
	ft_putstr_fd("\b", 1);
}

void	built_echo(int i)
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
	errno = 0;
}
