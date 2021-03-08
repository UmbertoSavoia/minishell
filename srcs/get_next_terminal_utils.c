/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_terminal_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cromaldeusavoia <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:09:43 by cromalde          #+#    #+#             */
/*   Updated: 2021/03/08 13:28:50 by cromaldeusa      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_error(int error)
{
	(void)error;
	printf(RED"\n%s"NC, strerror(errno));
	exit(1);
}

int		ft_strrchr_mod(const char *s, const char *end, int c)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	while (s != end)
	{
		if (*s == (unsigned char)c)
			ret = i;
		if (*s == 0)
			break ;
		s++;
		i++;
	}
	return (ret);
}

int		ft_strchr_mod(const char *s, const char *end, int c)
{
	int		i;

	i = 0;
	if (*s == (unsigned char)c)
		s++;
	while (s != end)
	{
		if (*s == (unsigned char)c)
			return (i);
		if (*s == 0)
			break ;
		i++;
		s++;
	}
	return (0);
}

char	*escape_cursor_create(int pos, char *c)
{
	char	*ret;
	char	*temp;
	char	*num;
	int		len_num;

	num = ft_itoa(pos);
	len_num = ft_strlen(num);
	temp = ft_strjoin("\x1b[", num);
	ret = ft_strjoin(temp, c);
	free(temp);
	free(num);
	return (ret);
}
