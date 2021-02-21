/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usavoia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:40:16 by usavoia           #+#    #+#             */
/*   Updated: 2021/01/11 14:57:02 by usavoia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t ret;
	size_t len;

	if (!dest && !src)
		return (0);
	ret = 0;
	while (src[ret])
		ret++;
	if (size)
	{
		len = (ret >= size) ? size - 1 : ret;
		while (len--)
			*dest++ = *src++;
		*dest = '\0';
	}
	return (ret);
}
