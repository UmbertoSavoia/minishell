#include "../include/minishell.h"

int		built_set(void)
{
	t_env	*tmp;
	char	*t;

	tmp = g_shell.var_list;
	errno = 0;
	while (tmp)
	{
		t = !*tmp->value ? "\"\"" : tmp->value;
		printf("%s=%s\n", tmp->key, t);
		tmp = tmp->next;
	}
	return (1);
}
