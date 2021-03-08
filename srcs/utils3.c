/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:12:06 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:29:50 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*node_dup(t_env *node)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = ft_strdup(node->key);
	new->value = ft_strdup(node->value);
	return (new);
}

t_env	*get_value_set(char *key)
{
	t_env	*tmp;
	int		len_key;

	len_key = ft_strlen(key);
	if (!len_key)
		return (0);
	if (*key == '$')
	{
		key++;
		len_key -= 1;
	}
	if (key[len_key - 1] == '\'' || key[len_key - 1] == '\"')
		len_key--;
	tmp = g_shell.var_list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, len_key))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

char	**ft_list_to_arr(int i)
{
	int		j;
	int		len_list;
	char	**ret;
	t_list	*tmp;

	j = 0;
	len_list = ft_lstsize(g_shell.table_list[i]);
	ret = malloc(len_list * sizeof(char**) + 1);
	tmp = g_shell.table_list[i];
	while (tmp)
	{
		if (((char*)tmp->content)[0] == '|')
			break ;
		ret[j] = ft_strdup(tmp->content);
		tmp = tmp->next;
		j++;
	}
	ret[j] = 0;
	return (ret);
}

int		ft_free_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr[i]);
	free(arr);
	arr = 0;
	return (1);
}

void	skip_quote(char *str)
{
	char	c;
	int		i;

	c = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\\' && str[i + 1] == '\\')
			ft_memmove(&(str[i]), &(str[i + 1]), ft_strlen(&(str[i])));
		if (str[i] == '\"' && str[i + 1] == '\\' && str[i + 2] == '\\')
			ft_memmove(&(str[i + 1]), &(str[i + 2]), ft_strlen(&(str[i])));
		if (c == 0 &&
			((str[i] == '\'' && str[i + 1] != '$' && str[i + 1] != '\0')
				|| str[i] == '\"'))
		{
			c = str[i];
			ft_memmove(&(str[i]), &(str[i + 1]), ft_strlen(&(str[i])));
		}
		if (str[i] == c)
		{
			ft_memmove(&(str[i]), &(str[i + 1]), ft_strlen(&(str[i])));
			c = 0;
			continue ;
		}
	}
}
