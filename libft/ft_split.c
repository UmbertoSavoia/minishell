/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:38:41 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 14:59:01 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_word(char const *s, char c)
{
	size_t i;

	i = 0;
	while (s && *s)
	{
		if (*s != c)
		{
			++i;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (i);
}

static void		skip(char const **s, char v[], char c)
{
	while ((**s && **s != c) || (v[0] == -1 || v[1] == -1))
	{
		if ((**s == '\"') && (v[1] == 1))
			v[0] *= -1;
		else if ((**s == '\'') && (v[0] == 1))
			v[1] *= -1;
		++(*s);
	}
}

int				init(char v[], size_t *i, int b)
{
	v[0] = 1;
	v[1] = 1;
	if (b == 1)
		*i = 0;
	return (1);
}

char			**ft_split(char const *s, char c)
{
	char	v[2];
	char	**ret;
	char	*from;
	size_t	i;
	size_t	size;

	init(v, &i, 1);
	if (!(ret = (char**)malloc(sizeof(char*) * get_word(s, c) + 1)))
		return (0);
	while (s && *s)
	{
		if (init(v, &i, 0) && (*s != c))
		{
			from = (char*)s;
			skip(&s, v, c);
			size = s - from + 1;
			if (!(ret[i] = (char*)malloc(size)))
				return (0);
			ft_strlcpy(ret[i++], from, size);
		}
		else
			++s;
	}
	ret[i] = 0;
	return (ret);
}
