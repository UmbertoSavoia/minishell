#include "../include/minishell.h"

void	refresh_pwd()
{
	char	tmp[PATH_MAX];
	t_env	*new_pwd;
	t_env	*old_pwd;

	if (!(old_pwd = get_value_env("OLDPWD")))
	{
		ft_push_front_env(&g_shell.envp, ft_create_node_env("OLDPWD=0"));
		old_pwd = get_value_env("OLDPWD");
	}
	if (!(new_pwd = get_value_env("PWD")))
	{
		ft_push_front_env(&g_shell.envp, ft_create_node_env("PWD=not set"));
		new_pwd = get_value_env("PWD");
	}
	free(old_pwd->value);
	old_pwd->value = ft_strdup(new_pwd->value);
	free(new_pwd->value);
	getcwd(tmp, PATH_MAX);
	new_pwd->value = ft_strdup(tmp);
}

void	cd_home(t_env *home)
{
	if (!home)
	{
		ft_putendl_fd(RED"cd : HOME not set"NC, 1);
		errno = 1;
		return ;
	}
	chdir(home->value);
	errno = 0;
}

void	built_cd(int i)
{
	t_env	*home;
	t_list	*tmp;
	int		unused;

	unused = 0;
	home = get_value_env("HOME");
	tmp = g_shell.table_list[i]->next;
	if ((!g_shell.table_list[i]->next))
		cd_home(home);
	else if (g_shell.table_list[i])
	{
		if (ft_strchr(((char*)tmp->content), '$'))
			built_dollar(i, (char**)&(tmp->content), &unused);
		if (chdir(tmp->content) < 0)
		{
			printf(RED"minishell: cd: %s: %s\n"NC,
				((char*)tmp->content), strerror(errno));
			return ;
		}
	}
	refresh_pwd();
	errno = 0;
}

void	built_exit_code(t_list *value)
{
	int i;

	i = 0;
	while (((char*)value->content)[i])
	{
		if (!ft_isdigit(((char*)value->content)[i]))
		{
			i = -1;
			break ;
		}
		i++;
	}
	if (i == -1)
	{
		printf(RED"minishell: exit: %s: numeric argument required"NC"\n",
		((char*)value->content));
		exit(255);
	}
	i = ft_atoi((char*)value->content);
	exit(i);
}

void	built_exit(i)
{
	t_list	*tmp;
	int		freeable;

	freeable = 0;
	tmp = g_shell.table_list[i];
	if (!tmp->next || i == -1)
	{
		if (g_shell.envp)
			env_clear(g_shell.envp);
		if (g_shell.table_list)
			clear_table_list();
		if (g_shell.var_list)
			env_clear(g_shell.var_list);
		free(g_shell.user);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	if (ft_strchr(((char*)tmp->next->content), '$'))
		built_dollar(i, (char**)&(tmp->next->content), &freeable);
	built_exit_code(tmp->next);
}
