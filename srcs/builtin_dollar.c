/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:06:39 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:27:38 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		built_dollar_support(int *j, char **node, t_env *tmp)
{
	if ((tmp = get_value_set(((*node) + 1))))
	{
		if (!*j)
			free(*node);
		*node = ft_strdup(tmp->value);
		errno = 0;
		return (1);
	}
	else if ((tmp = get_value_env((*node) + 1)))
	{
		if (!*j)
			free(*node);
		*node = ft_strdup(tmp->value);
		errno = 0;
		return (1);
	}
	else
	{
		if (!*j)
			free(*node);
		*node = ft_strdup("");
		errno = 0;
		return (1);
	}
}

int		check_quote_no_expansion(char **node, int w, int *j)
{
	char *tmp;

	if ((*node)[0] == '\'' && (*node)[1] == '$' && (*node)[w - 1] == '\'')
	{
		if (!*j)
		{
			tmp = ft_strdup((*node) + 1);
			free(*node);
			*node = tmp;
		}
		else
			(*node)++;
		(*node)[w - 2] = 0;
		*j = 0;
		return (0);
	}
	return (1);
}

void	built_dollar(int i, char **node, int *j)
{
	t_list				*ptr;
	char				c;
	int					w;

	c = 0;
	w = ft_strlen(*node);
	ptr = g_shell.table_list[i];
	while (ptr)
	{
		if (!ft_strncmp(ptr->content, *node, ft_strlen(*node)))
		{
			(*j)++;
			break ;
		}
		ptr = ptr->next;
	}
	if (!(check_quote_no_expansion(node, w, j)))
		return ;
	if (!(*j = built_dollar_support(j, node, 0)))
		;
	return ;
}
