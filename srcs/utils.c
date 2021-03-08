/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:11:53 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:29:41 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstremove_if_until(t_list **head, void *data,
	int (*cmp)(const void*, const void*, size_t), void (*del)(void*))
{
	t_list *it;

	it = *head;
	while (it && cmp(data, it->content, ft_strlen(data)))
	{
		*head = it->next;
		ft_lstdelone(it, del);
		it = *head;
	}
	if (!it)
		return ;
	*head = it->next;
	ft_lstdelone(it, del);
}

char	*get_key_env(const char *env, int *len_value)
{
	char	*ret;
	int		i;

	i = 0;
	while (env[i])
		if (env[i++] == '=')
			break ;
	if (!(ret = malloc(i + 1)))
		return (0);
	i = 0;
	while (env[i] && (env[i] != '='))
	{
		ret[i] = env[i];
		i++;
	}
	ret[i] = 0;
	*len_value = ft_strlen(env) - i;
	return (ret);
}

void	split_quote_handler(char *table, int *i)
{
	int x;

	x = 0;
	x = table[*i];
	*i += 1;
	while (table[*i] != x)
		*i += 1;
	x = 0;
}

t_list	*ft_split_get_token(char *table, char c)
{
	t_list	*ret;
	int		i;
	int		j;

	i = 0;
	j = -1;
	ret = 0;
	while (table[i])
	{
		if (table[i] != c && j == -1)
			j = i;
		if (table[i] == '\'' || table[i] == '\"')
			split_quote_handler(table, &i);
		else if (table[i] == c)
		{
			table[i] = 0;
			if (j != -1)
				ft_lstadd_back(&ret, ft_lstnew(&(table[j])));
			j = -1;
		}
		i++;
	}
	if (j != -1)
		ft_lstadd_back(&ret, ft_lstnew(&(table[j])));
	return (ret);
}

t_list	**ft_split_list(char **table, char c)
{
	int		i;
	t_list	**ret;

	i = 0;
	while (table[i])
		i++;
	if (!(ret = malloc(i * sizeof(t_list*) + 1)))
		return (0);
	i = 0;
	while (table[i])
	{
		ret[i] = ft_split_get_token(table[i], c);
		i++;
	}
	ret[i] = 0;
	return (ret);
}
