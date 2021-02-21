#include "../include/minishell.h"

t_shell		g_shell;

t_env	*ft_create_node_env(const char *env)
{
	t_env	*new;
	int		len_value;

	if (!(new = malloc(sizeof(t_env))))
		return (0);
	new->key = get_key_env(env, &len_value);
	new->value = ft_substr(env, ft_strlen(new->key) + 1, len_value);
	new->next = 0;
	return (new);
}

void	ft_push_front_env(t_env **head, t_env *new)
{
	new->next = *head;
	*head = new;
}

void	init_env(char **env)
{
	t_env	*head;
	int		i;

	i = 0;
	head = 0;
	while (env[i])
	{
		ft_push_front_env(&head, ft_create_node_env(env[i]));
		i++;
	}
	g_shell.envp = head;
}
