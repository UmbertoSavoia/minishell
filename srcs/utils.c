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
