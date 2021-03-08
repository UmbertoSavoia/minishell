/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:22:28 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:29:54 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_envsize(t_env *lst)
{
	int		ret;

	ret = 0;
	while (lst)
	{
		ret++;
		lst = lst->next;
	}
	return (ret);
}

char	**ft_env_to_arr(void)
{
	int		j;
	int		len_list;
	char	**ret;
	char	*swap;
	t_env	*tmp;

	j = 0;
	len_list = ft_envsize(g_shell.envp);
	ret = malloc(len_list * sizeof(char**) + 1);
	tmp = g_shell.envp;
	while (tmp)
	{
		swap = ft_strjoin(tmp->key, "=");
		ret[j] = ft_strjoin(swap, tmp->value);
		free(swap);
		tmp = tmp->next;
		j++;
	}
	ret[j] = 0;
	return (ret);
}

void	env_clear(t_env *head)
{
	t_env	*tmp;
	t_env	*cur;

	cur = head;
	while (cur)
	{
		tmp = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		cur = tmp;
	}
	cur = 0;
}

void	calc_size(t_list *tmp, t_list *end, int *j)
{
	while (tmp != end)
	{
		(*j)++;
		tmp = tmp->next;
	}
}
