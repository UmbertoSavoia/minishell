/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:42:55 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 14:58:14 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *last;

	last = 0;
	while (1)
	{
		if (*s == (unsigned char)c)
			last = s;
		if (*s == 0)
			break ;
		s++;
	}
	return ((char*)last);
}
