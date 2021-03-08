/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:05:06 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:26:16 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	refresh_pwd(void)
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
	errno = 0;
	if (!home)
	{
		ft_putendl_fd(RED"cd : HOME not set"NC, 1);
		errno = 1;
		return ;
	}
	chdir(home->value);
}

void	built_cd(int i)
{
	t_env	*home;
	t_list	*tmp;
	int		unused;

	unused = 0;
	errno = 0;
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
}
