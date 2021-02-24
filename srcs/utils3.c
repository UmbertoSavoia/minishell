#include "../include/minishell.h"

int		print_export(void)
{
	t_env	*tmp;

	tmp = g_shell.var_list;
	while (tmp)
	{
		printf("declare -x %s \b", tmp->key);
		if(*(tmp->value))
			printf("=%s \b", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
	tmp = g_shell.envp;
	while (tmp)
	{
		printf("declare -x %s \b", tmp->key);
		if(*(tmp->value))
			printf("=%s \b", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
	return (1);
}

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
	tmp = g_shell.var_list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, len_key))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

void	add_env_full(int i)
{
	char	*tmp;
	int		w;
	int		j;

	j = 0;
	w = 0;
	tmp = get_key_env(g_shell.table_list[i]->next->content, &w);
	if (*(char*)(g_shell.table_list[i]->next->content + w + 1) == 0)
		return ;
	remove_t_env(&g_shell.envp, tmp, &ft_memcmp, &free);
	ft_push_front_env(&g_shell.envp,
			ft_create_node_env(g_shell.table_list[i]->next->content));
	remove_t_env(&g_shell.var_list, tmp, &ft_memcmp, &free);
}
