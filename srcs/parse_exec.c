#include "../include/minishell.h"

void	exec_commands(void)
{
	int		i;
	int		unused;
	t_env	*tmp;

	i = 0;
	unused = 0;
	while (g_shell.table_list[i])
	{
		signal(SIGINT, ft_sigint_2);
		tmp = get_value_env("?");
		free(tmp->value);
		tmp->value = ft_itoa(errno);
		if ((list_search(g_shell.table_list[i], "|", &ft_memcmp)))
			built_pipe(i);
		else if (find_redir(i) || find_builtin(i, &unused) || find_command(i))
			;
		i++;
	}
}

void	trim_skip(void)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_shell.c_table[i])
	{
		tmp = ft_strtrim(g_shell.c_table[i], " ");
		free(g_shell.c_table[i]);
		g_shell.c_table[i] = tmp;
		i++;
	}
}

static char		*ft_sgomitata(char *input)
{
	int		i;
	char	*new;
	int		num;
	int		j;

	j = 0;
	i = 0;
	num = 0;
	while (input[i])
	{
		if (!ft_memcmp("<", &(input[i]), 1) || !ft_memcmp(">>", &(input[i]), 2) ||
		(!ft_memcmp(">", &(input[i]), 1) && ft_memcmp(">", &(input[i + 1]), 1)) ||
		!ft_memcmp("|", &(input[i]), 1))
			num++;
		i++;
	}
	new = malloc(i + (num * 2) + 1);
	i = 0;
	while (input[i])
	{
		if (!ft_memcmp("<", &(input[i]), 1) || !ft_memcmp(">>", &(input[i]), 2) ||
		(!ft_memcmp(">", &(input[i]), 1) && ft_memcmp(">", &(input[i + 1]), 1)) ||
		!ft_memcmp("|", &(input[i]), 1))
		{
			if (!ft_memcmp(">>", &(input[i]), 2))
			{
				new[j++] = ' ';
				new[j++] = input[i++];
				new[j++] = input[i++];
				new[j++] = ' ';
			}
			else
			{
				new[j++] = ' ';
				new[j++] = input[i++];
				new[j++] = ' ';
			}
		}
		else
			new[j++] = input[i++];
	}
	new[j] = 0;
	free(input);
	return (new);
}

void	parse_exec(void)
{
	char	*input;
	int		i;
	t_list	*tmp;

	if (((i = get_next_terminal(&input))) < 0)
	{
		g_shell.exit_code = EBADF;
		return ;
	}
	termios_reset_mode();
	if (i == 0)
		built_exit(-1);
	ft_histadd_front(&g_shell.history, ft_histnew(input));
	input = ft_sgomitata(input);
	if ((!(check_quote(input)) && (errno = 22)) && ft_free(input))
	{
		printf(RED"%s"NC"\n", strerror(errno));
		return ;
	}
	g_shell.c_table = ft_split(input, ';');
	free(input);
	trim_skip();
	g_shell.table_list = ft_split_list(g_shell.c_table, ' ');
	free(g_shell.c_table);
	i = 0;
	while (g_shell.table_list[i])
	{
		tmp = g_shell.table_list[i];
		while (tmp)
		{
			skip_quote(((char*)tmp->content));
			tmp = tmp->next;
		}
		i++;
	}
	exec_commands();
}
