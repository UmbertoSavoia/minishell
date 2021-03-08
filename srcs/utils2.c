/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:11:59 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:29:46 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	ft_free(void *data)
{
	free(data);
	data = 0;
	return (1);
}

char	list_search(t_list *head, char *str,
	int (*f)(const void*, const void*, size_t))
{
	while (head)
	{
		if (!((*f)(str, head->content, ft_strlen(str) + 1)))
			return (1);
		head = head->next;
	}
	return (0);
}

void	clear_table_list(void)
{
	int		i;

	i = 0;
	while (g_shell.table_list[i])
	{
		free(g_shell.table_list[i]->content);
		ft_lstclear(&g_shell.table_list[i], 0);
		i++;
	}
	free(g_shell.table_list);
}

int		check_quote(char *line)
{
	int		i;
	int		j;

	i = 2;
	j = 2;
	while (*line)
	{
		if (*line == '\"' && (j & 1) == PARI)
			i++;
		if (*line == '\'' && (i & 1) == PARI)
			j++;
		line++;
	}
	return (!(i & 1) && !(j & 1));
}
