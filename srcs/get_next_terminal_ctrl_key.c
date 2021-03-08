#include "../include/minishell.h"

void	ctrl_left(void)
{
	char	*escape;
	int		start;
	int		pos_space;

	if (g_shell.curs > g_shell.len_prompt)
	{
		start = g_shell.curs - g_shell.len_prompt - 1;
		pos_space = ft_strrchr_mod(g_shell.final_string,
			&g_shell.final_string[start], ' ');
		if (pos_space > 0)
		{
			escape = escape_cursor_create(start - pos_space, "D");
			write(1, escape, strlen(escape));
			g_shell.curs = g_shell.curs - (start - pos_space);
		}
		else if (pos_space == 0 && g_shell.curs > g_shell.len_prompt)
		{
			start = g_shell.curs - g_shell.len_prompt;
			escape = escape_cursor_create(start, "D");
			write(1, escape, strlen(escape));
			g_shell.curs = g_shell.len_prompt;
		}
	}
}

void	ctrl_right(void)
{
	char	*escape;
	int		start;
	int		pos_space;

	if ((g_shell.curs - g_shell.len_prompt) < g_shell.len_string)
	{
		start = g_shell.curs - g_shell.len_prompt;
		pos_space = ft_strchr_mod(&g_shell.final_string[start],
			&g_shell.final_string[g_shell.len_string], ' ');
		if (pos_space > 0 &&
			(g_shell.curs - g_shell.len_prompt) < g_shell.len_string)
		{
			escape = escape_cursor_create(pos_space, "C");
			write(1, escape, strlen(escape));
			g_shell.curs += pos_space;
		}
		else if (pos_space == 0)
		{
			start = g_shell.curs - g_shell.len_prompt;
			escape = escape_cursor_create(g_shell.len_string - start, "C");
			write(1, escape, strlen(escape));
			g_shell.curs = g_shell.len_string + g_shell.len_prompt;
		}
	}
}
