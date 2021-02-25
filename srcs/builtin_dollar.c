#include "../include/minishell.h"

char	*built_dollar(int i, char *node)
{
	t_env	*var_set;
	t_env	*var_env;
	char	*key;
	int		w;

	(void)i;
	key = get_key_env(node, &w) + 1;
	var_set = get_value_set(key);
	var_env = get_value_env(key);
	if ((!var_set->key) && (!var_env->key))
		return (0);
	node = (var_set->key) ? var_set->value : var_env->value;
	return (node);
}