/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:42:29 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 14:58:27 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t l2;

	l2 = 0;
	while (s2[l2])
		l2++;
	if (!l2)
		return ((char*)s1);
	while (len >= l2)
	{
		if (!ft_memcmp(s1, s2, l2))
			return ((char*)s1);
		s1++;
		len--;
	}
	return (0);
}
