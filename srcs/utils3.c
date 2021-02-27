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
		ret[j] = ft_strdup(tmp->content);
		tmp = tmp->next;
		j++;
	}
	ret[j] = 0;
	return (ret);
}

void	ft_free_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr[i]);
	free(arr);
	arr = 0;
}
