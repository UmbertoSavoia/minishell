/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:43:32 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 14:58:44 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char a, char const *set)
{
	while (*set)
		if (a == *set++)
			return (1);
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	char	*inizio;
	char	*fine;
	size_t	len;

	inizio = (char*)s1;
	fine = inizio + ft_strlen(s1);
	while (*inizio && isset(*inizio, set))
		++inizio;
	while (inizio < fine && isset(*(fine - 1), set))
		--fine;
	len = fine - inizio + 1;
	if (!(ret = malloc(len)))
		return (0);
	ft_strlcpy(ret, inizio, len);
	return (ret);
}
