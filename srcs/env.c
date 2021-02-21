#include "../include/minishell.h"

t_shell		g_shell;

t_env	*ft_create_node_env(char *env)
{
	char	*tmp;
	t_env	*new;

	if (!(new = malloc(sizeof(t_env))))
		return (0);
	if (!(tmp = ft_strchr(env, '=')))
		return (new);
	new->key = env; //ft_substr(env, 0, tmp - env);
	//new->value = env; //ft_substr(env, tmp - env + 1, ft_strlen(env) - ft_strlen(tmp) - 1);
	//ft_strlcpy(new->value, tmp + 1, ft_strlen(env) - ft_strlen(tmp));
	new->next = 0;
	return (new);
}

void	ft_push_front_env(t_env **head, t_env *new)
{
	/* if (!(*head))
	{
		*head = new;
		return ;
	} */
	new->next = *head;
	*head = new;
}

void	init_env(char **env)
{
	t_env	*head;

	while (*env)
	{
		ft_push_front_env(&head, ft_create_node_env(*env));
		(*env)++;
	}
	g_shell.envp = head;
}
