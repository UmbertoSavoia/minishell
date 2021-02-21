/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:39:57 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 14:52:57 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;

	i = 0;
	while (*dest && i < size)
	{
		i++;
		dest++;
	}
	while (*src && i + 1 < size)
	{
		*dest++ = *src++;
		i++;
	}
	if (i < size)
		*dest = 0;
	while (*src++)
		i++;
	return (i);
}
