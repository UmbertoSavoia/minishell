#include "../include/minishell.h"

void	built_pwd(int i)
{
	t_env *tmp;

	if (g_shell.table_list[i]->next != 0)
	{
		ft_putendl_fd(RED"pwd: too many arguments"NC, 1);
		errno = 1;
		return ;
	}
	tmp = get_value_env("PWD");
	ft_putendl_fd(tmp->value, 1);
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
}

void	echo_print(char *s)
{
	static char	v;
	int			i;

	i = 0;
	v = 1;
	while (s[i])
	{
		if (s[i] == '\"' && v != '\'')
			v = s[i];
		else if (s[i] == '\'' && v != '\"')
			v = s[i];
		if (s[i] != v)
			ft_putchar_fd(s[i], 1);
		i++;
	}
	ft_putstr_fd(" ", 1);
}

void	built_echo(i)
{
	t_list *tmp;

	tmp = g_shell.table_list[i];
	if (tmp->next)
	{
		if (!ft_memcmp(tmp->next->content, "-n", 3))
		{
			tmp = tmp->next->next;
			while (tmp)
			{
				echo_print(tmp->content);
				tmp = tmp->next;
			}
			ft_putstr_fd("\b", 1);
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
}
