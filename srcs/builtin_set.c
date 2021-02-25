#include "../include/minishell.h"

int		built_set(void)
{
	t_env	*tmp;
	char	*t;

	tmp = g_shell.var_list;
	while (tmp)
	{
		t = !*tmp->value ? "\"\"" : tmp->value;
		printf("%s=%s\n", tmp->key, t);
		tmp = tmp->next;
	}
	errno = 0;
	return (1);
}