/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:07:00 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:27:46 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		print_export(void)
{
	t_env	*tmp;

	tmp = g_shell.var_list;
	while (tmp)
	{
		printf("declare -x %s \b", tmp->key);
		if (*(tmp->value))
			printf("=%s \b", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
	tmp = g_shell.envp;
	while (tmp)
	{
		if (tmp->key[0] != '?')
		{
			printf("declare -x %s \b", tmp->key);
			if (*(tmp->value))
				printf("=%s \b", tmp->value);
			printf("\n");
		}
		tmp = tmp->next;
	}
	return (1);
}

void	add_env_full(int i)
{
	char	*tmp;
	int		w;

	w = 0;
	tmp = get_key_env(g_shell.table_list[i]->next->content, &w);
	if (*(char*)(g_shell.table_list[i]->next->content + w + 1) == 0)
		return ;
	remove_t_env(&g_shell.envp, tmp, &ft_memcmp, &free);
	ft_push_front_env(&g_shell.envp,
			ft_create_node_env(g_shell.table_list[i]->next->content));
	remove_t_env(&g_shell.var_list, tmp, &ft_memcmp, &free);
	free(tmp);
}

void	add_env_list(int i)
{
	char	*tmp;
	int		w;

	w = 0;
	tmp = get_key_env(g_shell.table_list[i]->next->content, &w);
	if (*(char*)(g_shell.table_list[i]->next->content + w + 1) == 0)
		return ;
	remove_t_env(&g_shell.envp, tmp, &ft_memcmp, &free);
	ft_push_front_env(&g_shell.envp, node_dup(get_value_set(tmp)));
	remove_t_env(&g_shell.var_list, tmp, &ft_memcmp, &free);
	free(tmp);
}

void	built_export(int i)
{
	t_list *tmp;

	errno = 0;
	tmp = g_shell.table_list[i]->next;
	if ((!tmp || ((char*)g_shell.table_list[i]->next->content)[0] == '$')
		&& print_export())
		return ;
	else if (!var_search(tmp, '=', &ft_strchr))
	{
		if (get_value_set((char*)tmp->content))
			add_env_list(i);
		else
			add_var_list(i, 0);
	}
	else if (var_search(tmp, '=', &ft_strchr))
		add_env_full(i);
}
