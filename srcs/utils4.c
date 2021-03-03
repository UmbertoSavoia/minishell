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
