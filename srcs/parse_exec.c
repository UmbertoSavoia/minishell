/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:10:05 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:29:03 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void			exec_commands(void)
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

void			trim_skip(void)
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

	i = 0;
	num = 0;
	while (input[i])
	{
		if (!ft_memcmp("<", &(input[i]), 1) ||
		!ft_memcmp(">>", &(input[i]), 2) || (!ft_memcmp(">", &(input[i]), 1) &&
		ft_memcmp(">", &(input[i + 1]), 1)) || !ft_memcmp("|", &(input[i]), 1))
			num++;
		i++;
	}
	new = ft_sgomitata_support(input, num, i, 0);
	free(input);
	return (new);
}

void			skip_cicle(void)
{
	t_list	*tmp;
	int		i;

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
}

void			parse_exec(void)
{
	char	*input;
	int		i;

	if (((i = get_next_terminal(&input))) < 0)
	{
		g_shell.exit_code = EBADF;
		return ;
	}
	termios_reset_mode();
	if (i == 0)
		built_exit(-1);
	g_shell.hist_size += ft_histadd_front(&g_shell.history, ft_histnew(input));
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
	skip_cicle();
	exec_commands();
}
