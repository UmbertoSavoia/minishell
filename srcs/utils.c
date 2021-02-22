#include "../include/minishell.h"

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
	while (env[i] != '=')
	{
		ret[i] = env[i];
		i++;
	}
	ret[i] = 0;
	*len_value = ft_strlen(env) - i;
	return (ret);
}

void	env_clear(void)
{
	t_env	*tmp;
	t_env	*cur;

	cur = g_shell.envp;
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
